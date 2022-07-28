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
 * \detail         :
 *
 * \param[in]      :float(user defined) *arr£º  sort array in reverse order
 * \param[in]      :uint32_t size£ºnumber of arrays
 * \param[in]      :float(user defined) target£ºvalue need to find 
 * \param[out]     :uint32_t num: the value to the left closest to the target value
 *
 * \retval         :uint8_t  status: -1 means get NULL array   
 *                                   -2  smaller than the minimun value
 *                                   1 means get VALID array
 */
int8_t dichotomous_search(DATA_TYPE *arr, uint32_t size, DATA_TYPE target, uint32_t *num) 
{
    
    uint32_t left      = 0;
    uint32_t right     = size - 1;
    uint32_t mid       = 0;
    uint8_t  status = 1;

    if(arr == NULL) {                //judge the array is NULL or not
        
        return -1;
    }
    if(arr[0] > arr[size - 1]) {      //array rank biggest ---> smallest
        
        if(target > arr[0] ) {
    
            return -2;
    
        }
        while (left <= right) {      //avoid the array has only 1 data
            
            mid = (left + right) / 2;

            if(target > arr[mid]) {
            
                right = mid - 1;
        
            }else if( target < arr[mid]) {

                left = mid + 1;
        
            }else{
        
                *num = mid;
                break;
            }
        }
        
    }else if(arr[0] < arr[size - 1]) {   //array rank smallest ---> biggest
        
        if(target < arr[0] ) {
    
            return -2;
    
        }
        while (left <= right) {             //avoid the array has only 1 data
            
            mid = (left + right) / 2;

            if(target < arr[mid]) {
            
                right = mid - 1;
        
            }else if( target > arr[mid]) {

                left = mid + 1;
        
            }else{
        
                *num = mid;
                break;
            }
        }
        
    
    }
    

    if (target != arr[mid])         //return left 
    {
        *num = left;
    }
    
    return status;
    
}



