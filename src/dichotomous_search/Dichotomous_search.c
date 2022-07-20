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
   /* null pointer constant. */

/**
 * \brief          :dichotomous_search
 * \detail         :search an array sort from largest to smallest with this method
 *
 * \param[in]      :float    *arr£ºsort array in reverse order
 * \param[in]      :uint32_t size£ºnumber of arrays
 * \param[in]      :uint32_t target£ºvalue need to find 
 * \param[out]     :uint32_t num: the value to the left closest to the target value
 *
 * \retval         :uint8_t  status: 0 means get NULL array
                                            1 means get VALID array
 */

uint8_t dichotomous_search(float *arr, uint32_t size, uint32_t target, uint32_t *num) 
{
    
    uint32_t left      = 0;
    uint32_t right     = size - 1;
    uint32_t mid       = 0;
    uint8_t  status = 1;

    if(arr == NULL) {                //judge the array is NULL or not
        
        return 0;
    }
    while (left < right ) {
        
        mid = (left + right) / 2;
        
        if(target > arr[mid]) {
            
            right = mid	- 1;
        
        }else if( target < arr[mid]) {
    
            left = mid + 1;
        
        }else if(target == arr[mid]) {
        
            *num = mid;
            break;
        }
    }
    
    if (target != arr[mid]) {
        
        *num = left;
    }

    return status;
    
}



