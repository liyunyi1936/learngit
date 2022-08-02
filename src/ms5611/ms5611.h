#ifndef __MS5611_H
#define __MS5611_H

#include "main.h"
 
 
#define MS5611_WriteAddr         0xEE
#define MS5611_ReadAddr          0xEF
 
#define MS5611_CMD_RES           0x1E
 
#define MS5611_D1_OSR_256		    0x40
#define MS5611_D1_OSR_512           0x42
#define MS5611_D1_OSR_1024			0x44
#define MS5611_D1_OSR_2048			0x46
#define MS5611_D1_OSR_4096			0x48


#define MS5611_D2_OSR_256			0x50
#define MS5611_D2_OSR_512			0x52
#define MS5611_D2_OSR_1024			0x54
#define MS5611_D2_OSR_2048			0x56
#define MS5611_D2_OSR_4096			0x58

#define MS5611_ADC_READ				0x00
#define MS5611_PROM_READ			0xA0
#define MS5611_PROM_CRC				0xAE
 
#define MS5611_C1_REG_H          0xA2
#define MS5611_C2_REG_H          0xA4
#define MS5611_C3_REG_H          0xA6
#define MS5611_C4_REG_H          0xA8
#define MS5611_C5_REG_H          0xAA
#define MS5611_C6_REG_H          0xAC
#define MS5611_data_REG_H        0x00
 
 
extern uint16_t C1,C2,C3,C4,C5,C6;
extern uint32_t D1,D2;
extern float cTemp,fTemp,pressure;
 
void MS5611_INIT(void);
void MS5611_Calculate_Val(void);
void GetPressandTemp(void);
uint8_t HAL_IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);


#endif /*__MS5611_H*/
