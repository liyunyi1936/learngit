/**
 * \file       :Dichotomous_search.c
 * \brief      :binary search 
 * \author     :liyunyi
 * \date       :2022.7.18
 * \version    :v2.0.1
 * \copyright  :
 */

#include "Dichotomous_search.h"
#include <stdint.h>

#define NULL 0

/**
 * \brief          :dichotomous_search
 * \detail         :array rank from biggest to smallest
 *
 * \param[in]      :float    *arr£ºsort array in reverse order
 * \param[in]      :uint32_t size£ºnumber of arrays
 * \param[in]      :float target£ºvalue need to find 
 * \param[out]     :uint32_t num: the value to the left closest to the target value
 *
 * \retval         :uint8_t  status: -1 means get NULL array   
 *                                   -2  smaller than the minimun value
 *                                   1 means get VALID array
 */

int8_t dichotomous_search(void *arr, uint32_t data_type_len, uint32_t data_len, void *target, 
                          int8_t(*compare_func)(void *member_1, void *member_2), uint32_t *num) 
{
    
    uint32_t left      = 0;
    uint32_t right     = data_len - 1;
    uint32_t mid       = 0;
    uint8_t  status = 1;
    int8_t cmp_ret = 0;
    
    char *data_array = arr;

    if(arr == NULL) {                //judge the array is NULL or not
        
        return -1;
    }
    if(compare_func(target, data_array) >0 ) {
    
        return -2;
    
    }
    
    
    while (left <= right) {      //avoid the array has only 1 data
        
        mid = (left + right) << 1;
        
        cmp_ret = compare_func(data_array + mid * data_type_len, target);
        
        if(cmp_ret < 0) {
        
            right = mid - 1;
    
        }else if(cmp_ret > 0) {

            left = mid + 1;
    
        }else{
    
            *num = mid;
            break;
        }
    }

    if (cmp_ret) 
    {
        *num = left;
    }
    
    return status;
    
}



