#include "Dichotomous_search.h"
#include "get_real_temp_value.h"
#define DATA_TYPE float
/**
 * \brief          :get_linear_value
 * \detail         :Given two coordinates, find the y value of the third point 
 *
 * \retval         :output_y
*/
 
uint8_t get_linear_value(float x1, float y1, float x2, float y2, float intput_x,float *output_y)
{

    *output_y = ((x1 - intput_x) / (x1 - x2) * (y2 - y1)) + y1;
    
    return *output_y;
}

static int8_t float_compare_func(void* m1, void* m2)
{
    int8_t ret = 0;
    DATA_TYPE* a = m1;
    DATA_TYPE* b = m2;


    if (*a == *b) {


        ret = 0;
    }
    else if (*a > *b) {  


        ret = 1;            /*"compare_func"  big to small :ret  = + 1   small to big: -1*/
    }
    else {

        ret = -1;
    }

    return ret;


}


/**
 * \brief          :search_and_get_value
 * \detail         :use Dichotomous search method to find the closest array subscript and calculate the temperature corresponding to the NTC resistance value 
 * \param[in]      :float *arr:   resistance array
 * \param[in]      :uint16_t len: the length of resistance array
 * \param[in]      :float resist_value: resistance values obtained by ADC sampling conversion
 * \param[in]      :float init_temp: the minimum of a finite range of temperature values
* \param[in]       :float per_range: every two temperature intervals
 * \param[out]     :float *temp:    pointed to real temperature result
 *
 * \retval         :uint8_t  status: 0 means error execution or function not executed
                                     1 means The function has completed execution
                                     2 means temperature data over the normal range 
*/

uint8_t search_and_get_value(float *resist_arr, uint16_t len, float resist_value, float init_temp, float per_range, float *temp) 
{
    uint32_t num = 0; 
    int8_t status = 0;
    float temp1,temp2;
    float min_temp, max_temp;
       
    status = dichotomous_search(resist_arr, sizeof(DATA_TYPE), len, &resist_value, float_compare_func, &num);
    
    min_temp = init_temp;
    max_temp = init_temp + (len - 1) * per_range;
    if(num > (len -1)) {
        
        *temp = max_temp;
        status = 2;

    }else if(status <= 0) {
        
        *temp = min_temp;
        status = 2;
        
    }

    if (status == 1) {
         
        temp1 = init_temp + num * per_range;                /* from -70¡æ to 150¡æ, get a value per 0.05, totally 4401 temperature values */   
        temp2 = init_temp + (num + 1) * per_range ;
        get_linear_value(resist_arr[num], temp1, resist_arr[num+1], temp2, resist_value, temp);
        
    }

    return status;

}





