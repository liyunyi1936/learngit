#ifndef __FLASH_ONCHIP_USER_H

#define __FLASH_ONCHIP_USER_H
#include <stdint.h>


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
uint8_t flash_buffer_init(uint8_t *buffer, uint32_t buffer_len);

uint8_t buffer_sync(uint8_t *buffer, uint32_t buffer_len);
#endif
