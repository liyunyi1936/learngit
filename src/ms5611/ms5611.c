#include "main.h"
#include "ms5611.h"
#include "i2c.h"
 
uint8_t TBuff[1];
uint8_t RBuff[3];
 
float cTemp,fTemp;
uint16_t C1,C2,C3,C4,C5,C6;
uint32_t D1,D2;

int32_t dT;
int32_t TEMP,k,T2;
int64_t OFF,SENS,OFF2,SENS2;
float pressure;

uint8_t HAL_IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data)
{
    return HAL_I2C_Mem_Read(&hi2c1, dev, reg, I2C_MEMADD_SIZE_8BIT, data, length, 200);
}
 
void MS5611_INIT(void)
{
    //		0x1E(30)	Reset command
    TBuff[0]= MS5611_CMD_RES;
    HAL_I2C_Master_Transmit(&hi2c1,MS5611_WriteAddr,TBuff,1,100);

    HAL_Delay(10);

    // Read 12 bytes of calibration data
    // Read pressure sensitivity
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C1_REG_H,2,RBuff);
    C1 = RBuff[0] * 256 + RBuff[1];

    // Read pressure offset
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C2_REG_H,2,RBuff);
    C2 = RBuff[0] * 256 + RBuff[1];

    // Read temperature coefficient of pressure sensitivity
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C3_REG_H,2,RBuff);
    C3 = RBuff[0] * 256 + RBuff[1];

    // Read temperature coefficient of pressure offset
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C4_REG_H,2,RBuff);
    C4 = RBuff[0] * 256 + RBuff[1];

    // Read reference temperature
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C5_REG_H,2,RBuff);
    C5 = RBuff[0] * 256 + RBuff[1];

    // Read temperature coefficient of the temperature
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_C6_REG_H,2,RBuff);
    C6 = RBuff[0] * 256 + RBuff[1];
}
 
void GetPressandTemp(void)
{
    
    TBuff[0]= MS5611_CMD_RES;
    HAL_I2C_Master_Transmit(&hi2c1, MS5611_WriteAddr,TBuff,1,100);

    HAL_Delay(17);


    TBuff[0]= MS5611_D1_OSR_4096;
    HAL_I2C_Master_Transmit(&hi2c1, MS5611_WriteAddr,TBuff,1,100);

    HAL_Delay(17);

    // Read digital pressure value
    // Read data back from 0x00(0), 3 bytes
    // D1 MSB2, D1 MSB1, D1 LSB
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_data_REG_H, 3,RBuff);
    D1 = RBuff[0] * 65536 + RBuff[1] * 256 + RBuff[2];

    TBuff[0]= MS5611_D2_OSR_4096;
    HAL_I2C_Master_Transmit(&hi2c1, MS5611_WriteAddr, TBuff,1,100);

    HAL_Delay(17);

    // Read digital temperature value
    // Read data back from 0x00(0), 3 bytes
    // D2 MSB2, D2 MSB1, D2 LSB
    HAL_IIC_ReadMultByteFromSlave(MS5611_ReadAddr, MS5611_data_REG_H,3,RBuff);
    D2 = RBuff[0] * 65536 + RBuff[1] * 256 + RBuff[2];
    
}
 

void MS5611_Calculate_Val(void)
{
    dT = D2 - C5 * 256;
    TEMP = 2000 + (float)dT *((float)C6) / 8388608;                     //8388608 = 2^23
    OFF =(int64_t)C2 * 65536 +  (int64_t)((double)C4 * dT / 128  );
    SENS =(int64_t)C1 * 32768 + (int64_t)((double)C3 * dT/ 256  );
    T2 = 0;
    OFF2 = 0;
    SENS2 = 0;
 
    if (TEMP > 2000) {
        
        T2 = 0;
        OFF2 = 0;
        SENS2 = 0;
        
    }else if (TEMP < 2000 ) {
        
        k = (float)dT;
        T2 = (k * k)/2147483648;    /* (2^31) */
        OFF2 = (int64_t)(5 * ((float)(TEMP - 2000) * (TEMP - 2000)) / 2);
        SENS2 = (int64_t)(5 * ((float)(TEMP - 2000) * (TEMP - 2000)) / 4);
        
        if(TEMP < -1500) {
            
            OFF2 = OFF2 + 7 * ((float)(TEMP + 1500) * (TEMP + 1500));
            SENS2 = SENS2 + 11 * ((float)(TEMP + 1500) * (TEMP +1500)) / 2;
            
        }
    }
    TEMP = TEMP - T2;
    OFF = OFF - OFF2;
    SENS = SENS - SENS2;
    pressure = (float)((((double)(D1 * SENS) / 2097152) - OFF) / 32768.0);    //Temperature compensated pressure (10...1200mbar with  0.01mbar resolution)
    cTemp = (float)(TEMP / 100.0);
    fTemp = cTemp * 1.8f + 32;
}


