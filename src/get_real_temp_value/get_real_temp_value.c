#include "stdint.h"
#include "Dichotomous_search.h"
#include "get_real_temp_value.h"

#define ARRAY_NUM(a) (sizeof(a)/sizeof(a[0]))
    
/**
 * \brief          :get_real_temp_value
 * \detail         :Use a linear relationship to find the real temperature value 
 *                  
 * \param[in]      :uint16_t num :the subscript to the left closest to the target value
 * \param[in]      :uint32_t value    : resistance  value
 * \param[in]      :float *resist_arr  : put the resistance array
 * \param[out]     :float *real_Temp   : the pointer of the temperature value finally found
 *
 * \retval         :uint8_t  status: 0 means ERROR(searching array is bigger than target array)
                                     1 means RIGHT operation
 */
static uint8_t get_real_temp_value(uint16_t subs, uint32_t value, float *resist_arr, float *real_Temp) 
{
    
    if (subs >= 4400) {     /* from -70¡æ to 150¡æ, get a value per 0.05, totally 4400 temperature values */   
        
        return 0;            /*avoid entering an array larger than the range*/ 
        
    }
    
    *real_Temp = -70 + subs * 0.05f + ((resist_arr[subs] - value) / (resist_arr[subs] - resist_arr[subs + 1]) * 0.05f);  //
    
    return 1;
    
}


/**
 * \brief          :search_and_get_value
 * \detail         :use Dichotomous search method to find the closest array subscript and calculate the temperature corresponding to the NTC resistance value 
 * \param[in]      :float *arr:   resistance array
 * \param[in]      :uint16_t len: the length of resistance array
 * \param[in]      :uint32_t target_value: resistance values obtained by ADC sampling conversion
 * \param[out]     :float *temp:  pointed to real temperature result
 *
 * \retval         :uint8_t  status: 0 means 
                                     1 means 
*/
    
       
uint8_t search_and_get_value(float *arr, uint16_t len, uint32_t target_value, float *temp) 
{
    uint32_t num = 0; 
    uint8_t status = 0;
       
    status = dichotomous_search(arr, len, target_value, &num);
    
    if (status == 1) {
        
        status = get_real_temp_value(num, target_value, arr, temp);
    }

    
    return status;
    
   
}
