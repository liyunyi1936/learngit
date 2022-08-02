#ifndef __FALSH_ONCHIP_PARAMETER_H

#define __FALSH_ONCHIP_PARAMETER_H

#include <stdint.h>


#define TEMP_CTRL_NUM		2

typedef struct _store_data_structure store_data_structure;



struct _store_data_structure {                  
    
	int16_t 	temp_ctrl1_high_limit;
	int16_t	temp_ctrl1_low_limit;
	int8_t 	temp_ctrl1_ref;
	
	int16_t 	temp_ctrl2_high_limit;
	int16_t 	temp_ctrl2_low_limit;
	int8_t 	temp_ctrl2_ref;
	
	uint32_t reboot_time;
    uint32_t last_build_time;
};

extern store_data_structure *gp_flash_store_data;

uint8_t parameter_store_init(store_data_structure* data);
void store_buffer(void);
uint8_t read_param_from_buffer(store_data_structure* data);
uint8_t write_param_to_buffer(store_data_structure* data);
#endif

