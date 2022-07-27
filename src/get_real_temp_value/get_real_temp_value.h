#ifndef __GET_REAL_TEMP_VALUE_H
#define __GET_REAL_TEMP_VALUE_H
#include "stdint.h"
uint8_t get_linear_value(float x1, float y1, float x2, float y2, float intput_x,float *output_y);
uint8_t search_and_get_value(float *resist_arr, uint16_t len, uint32_t resist_value, float init_temp, float per_range, float *temp);



#endif  



