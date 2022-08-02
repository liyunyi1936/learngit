/**
 * \file       :	
 * \brief      :	
 * \author     :	Danphy
 * \version    :	V1.0
 */
 #include "flash_onchip.h"
#include "flash_onchip_user.h"


#define SECTOR_MAIN_ADDRESS     0x08100000
#define SECTOR_BACKUP_ADDRESS   0x08104000



/**
 * \brief     use this fuction to calculate the sbg_crc
 * \detail    
 *
 * \param[in] uint8_t *buffer : pointer point to the frame 
 * \param[in] uint8_t *len :the frame length
 *
 * \retval uint16_t crc calculate value.
 */
static uint16_t get_crc(const void *pFrame, uint16_t bufferSize)
{
	const uint8_t *pBuffer = (const uint8_t*)pFrame;
	uint16_t poly = 0x8408;
	uint16_t crc = 0;
	uint8_t carry;
	uint8_t i_bits;
	uint16_t j;

	for (j=0 ; j < bufferSize ; j++)
	{
		crc = crc ^ pBuffer[j] ;
		for (i_bits=0 ; i_bits < 8 ; i_bits++)
		{
			carry = crc & 1 ;
			crc = crc / 2 ;
			if (carry)
			{
				crc = crc ^ poly;
			}
		}
	}

	return crc;
}

static uint8_t buffer_crc_check(uint8_t *buffer, uint32_t buffer_len)
{
    
    uint8_t ret = 0;
    uint16_t crc_ret = 0;
    uint16_t buffer_crc = 0;
    
    if (buffer_len <= 2) {
    
        return 0;
    }
    
    crc_ret = get_crc(buffer, buffer_len - 2);
    buffer_crc = *(buffer + buffer_len - 2) | (*(buffer + buffer_len - 1) << 8);
    
    if ( crc_ret == buffer_crc) {
    
        ret = 1;
    }
    
    return ret;
    
    
}

static void add_crc_to_buffer_tail(uint8_t *buffer, uint32_t buffer_len)
{
    uint16_t crc_ret = 0;
    
    if (buffer_len <= 2) {
    
        return ;
    }
    crc_ret = get_crc(buffer, buffer_len - 2);
    *(buffer + buffer_len - 2) =  crc_ret & 0xFF;
    *(buffer + buffer_len - 1) = crc_ret >> 8;
    
    return;
}

uint8_t buffer_sync(uint8_t *buffer, uint32_t buffer_len)
{
    add_crc_to_buffer_tail(buffer, buffer_len);
    flash_write(SECTOR_MAIN_ADDRESS, buffer, buffer_len);      /* write the main sector first and then  write the backup */
    flash_write(SECTOR_BACKUP_ADDRESS, buffer, buffer_len);      /* write the main sector first and then  write the backup */
    return 1;
}

/**
 * \brief   put the uint_8 data to float in little idian
 * \detail 
 *
 * \param [in] uint8_t *p : the point of frame data buff
 * \param [in] uint32_t input_data : u32 output data
 * \param [in] uint8_t len : p space 
 *
 * \retval   0 : failure to get the flash data
 * \retval   1 : success to get the flash data
 */
uint8_t flash_buffer_init(uint8_t *buffer, uint32_t buffer_len)
{
    uint8_t ret = 0;
    
    flash_read(SECTOR_MAIN_ADDRESS, buffer, buffer_len);
    
    if (buffer_crc_check(buffer, buffer_len)) {
    
        ret = 1;
        return ret;
    }
    
    flash_read(SECTOR_BACKUP_ADDRESS, buffer, buffer_len);
    
    if (buffer_crc_check(buffer, buffer_len)) {
    
        ret = 1;
        return ret;
    }
    
    return ret;                                                        /* get flash failure */
    
}








