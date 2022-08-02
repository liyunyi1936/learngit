/**
 * \file       :	
 * \brief      :	
 * \author     :	Danphy
 * \version    :	V1.0
 */
#include "flash_onchip_parameter.h"
#include "flash_onchip_user.h"
#include <string.h>

#define ARRAY_NUM(a)  sizeof(a)/sizeof(a[0])
#define PARAMETER_BUFFER_SIZE   (1*1024)
static uint8_t g_buffer[PARAMETER_BUFFER_SIZE] = {0};


uint8_t write_param_to_buffer(store_data_structure* data)
{
    uint8_t ret;
    
    memcpy(g_buffer, data, sizeof(store_data_structure));
    
    return ret;
}

uint8_t read_param_from_buffer(store_data_structure* data)
{
    uint8_t ret;
    memcpy(data, g_buffer, sizeof(store_data_structure));
    return ret;
}

void store_buffer()
{
    
    buffer_sync(g_buffer, PARAMETER_BUFFER_SIZE);
}
   


static void get_init_parameter_from_flash(store_data_structure* data)
{
    /***********************************************************************
     *  the flash is effective ,get the data from flash
     ***********************************************************************/
	heater *p_heater1;
	heater *p_heater2;
	pow_reboot *p_reboot;
	user_logic_data_st *data1;
	user_logic_data_st *data2;
	
	p_heater1 = gp_heater1;
	p_heater2 = gp_heater2;
	p_reboot = gp_reboot;
	
	data1 = p_heater1->user_logic_data;
	data2 = p_heater2->user_logic_data;
	
	data1->high_temp = data->temp_ctrl1_high_limit;
	data1->low_temp = data->temp_ctrl1_low_limit;
	set_heater1_ctrl_channel(data->temp_ctrl1_ref);
	
	data2->high_temp = data->temp_ctrl2_high_limit;
	data2->low_temp = data->temp_ctrl2_low_limit;
	set_heater2_ctrl_channel(data->temp_ctrl2_ref);
	
	p_reboot->last_reset_time = data->reboot_time;
	
    return ;
}
static uint32_t get_build_time_from_flash(store_data_structure* data)
{
    
    memcpy(data, g_buffer, sizeof(store_data_structure));
    
    return data->last_build_time;
    
}  

static void write_init_parameter_to_flash(store_data_structure* data)
{
    /********************************************************************
     * get the user parameter data to buffer , and then store the buffer;
     ********************************************************************/
    /***********************************************************************
     *  the flash is effective ,get the data from flash
     ***********************************************************************/
    heater *p_heater1;
	heater *p_heater2;
	user_logic_data_st *data1;
	user_logic_data_st *data2;
	
	p_heater1 	= gp_heater1;
	p_heater2 	= gp_heater2;
	
	data1 = p_heater1->user_logic_data;
	data2 = p_heater2->user_logic_data;
	
	data->temp_ctrl1_high_limit	= data1->high_temp;
	data->temp_ctrl1_low_limit 	= data1->low_temp;
	data->temp_ctrl1_ref 		= get_heater1_ctrl_channel();
	
	data->temp_ctrl2_high_limit	= data2->high_temp;
	data->temp_ctrl2_low_limit 	= data2->low_temp;
	data->temp_ctrl2_ref 		= get_heater2_ctrl_channel();
	
	
    data->last_build_time = get_timestamp();
    
    write_param_to_buffer(data);
    
    store_buffer();
    return;
}
    
uint8_t parameter_store_init(store_data_structure* data)
{
    uint8_t init_ret;
    /*************************************************************************
     * 1. call init the flash_buffer_init , check the return value to judge the flash is effective or not
     * 2. if it is effective, get the parameter to the system
     * 3. if it is not effective , we put all the data to the buffer and start to 
     *************************************************************************/
    init_ret = flash_buffer_init(g_buffer, PARAMETER_BUFFER_SIZE);
    

    if (init_ret && 
        get_build_time_from_flash(data) == get_timestamp()) {
        
        get_init_parameter_from_flash(data);    
        
    } else {
        
        write_init_parameter_to_flash(data);
    }
    
    
    return init_ret;

}
