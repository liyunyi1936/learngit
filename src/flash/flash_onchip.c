/**
 * \file       :	
 * \brief      :	
 * \author     :	Danphy
 * \version    :	V1.0
 */
 #include "flash_onchip.h"

static uint8_t flash_get_sector(uint32_t addr)
{
    if (addr < ADDR_FLASH_SECTOR_1) {
        return FLASH_SECTOR_0;
    } else if (addr < ADDR_FLASH_SECTOR_2) { 
        return FLASH_SECTOR_1;
    } else if (addr < ADDR_FLASH_SECTOR_3) { 
        return FLASH_SECTOR_2;
    } else if (addr < ADDR_FLASH_SECTOR_4) { 
        return FLASH_SECTOR_3;
    } else if (addr < ADDR_FLASH_SECTOR_5) { 
        return FLASH_SECTOR_4;
    } else if (addr < ADDR_FLASH_SECTOR_6) { 
        return FLASH_SECTOR_5;
    } else if (addr < ADDR_FLASH_SECTOR_7) { 
        return FLASH_SECTOR_6;
    } else if (addr < ADDR_FLASH_SECTOR_8) { 
        return FLASH_SECTOR_7;
    } else if (addr < ADDR_FLASH_SECTOR_9) { 
        return FLASH_SECTOR_8;
    } else if (addr < ADDR_FLASH_SECTOR_10) { 
        return FLASH_SECTOR_9;
    } else if (addr < ADDR_FLASH_SECTOR_11) { 
        return FLASH_SECTOR_10;
    } else if (addr < ADDR_FLASH_SECTOR_12) { 
        return FLASH_SECTOR_11;
    } else if (addr < ADDR_FLASH_SECTOR_13) { 
        return FLASH_SECTOR_12;
    } else if (addr < ADDR_FLASH_SECTOR_14) { 
        return FLASH_SECTOR_13;
    } else if (addr < ADDR_FLASH_SECTOR_15) { 
        return FLASH_SECTOR_14;
    } else if (addr < ADDR_FLASH_SECTOR_16) { 
        return FLASH_SECTOR_15;
    } else if (addr < ADDR_FLASH_SECTOR_17) { 
        return FLASH_SECTOR_16;
    } else if (addr < ADDR_FLASH_SECTOR_18) { 
        return FLASH_SECTOR_17;
    } else if (addr < ADDR_FLASH_SECTOR_19) { 
        return FLASH_SECTOR_18;
    } else if (addr < ADDR_FLASH_SECTOR_20) { 
        return FLASH_SECTOR_19;
    } else if (addr < ADDR_FLASH_SECTOR_21) { 
        return FLASH_SECTOR_20;
    } else if (addr < ADDR_FLASH_SECTOR_22) { 
        return FLASH_SECTOR_21;
    } else if (addr < ADDR_FLASH_SECTOR_23) { 
        return FLASH_SECTOR_22;
    }
    return FLASH_SECTOR_23;
}

static uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(uint32_t *)faddr; 
}

void flash_read(uint32_t read_addr,uint8_t *buff, uint32_t num)
{
    uint32_t i = 0;

	for(i = 0; i < num; i++)
	{
		buff[i] = *(uint8_t *)(read_addr + i);
        
	}

}

void flash_write(uint32_t write_addr, uint8_t *data, uint32_t num)
{
    FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus = HAL_OK;
    uint32_t SectorError = 0;
    uint32_t addrx = 0;
	uint32_t endaddr = 0;	

	if(write_addr < STM32_FLASH_BASE ) {
        return;	
    }
    
	HAL_FLASH_Unlock();             
	addrx = write_addr;				
	endaddr = write_addr + num;	
    
	if(addrx < SYS_STORAGE_ADDR) {
		while(addrx < endaddr)	
		{
  	        if(*(uint8_t *)(addrx) != 0XFF)
			{   
				FlashEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;       
				FlashEraseInit.Sector    = flash_get_sector(addrx);  
				FlashEraseInit.NbSectors = 1;                           
				FlashEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;   
				while(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError) != HAL_OK);
			} else {
                addrx++;
            }
			FLASH_WaitForLastOperation(FLASH_WAITETIME);                
		}
	}

	FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);            
	if(FlashStatus == HAL_OK)
	{
        while(write_addr < endaddr)
		{
		    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, write_addr, *data) != HAL_OK)
			{ 
				break;	
			}
			write_addr++;
			data++;
	    }  
	}
	HAL_FLASH_Lock();     

}


