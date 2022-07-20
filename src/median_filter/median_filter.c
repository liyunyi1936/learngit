#include "median_filter.h"
#include <stdint.h>

#define FIND_MAX 1
#define FIND_MIN 0
/**
 * \brief : median_filter
 * \param[in] :uint16_t  buffer[]: input an array need to managed
 * \param[in] :uint16_t  buffer_limit:  the length of the biggest/ smallest array
 * \param[in] :uint16_t  *buf_member :  pointed at the biggest/ smallest array 
 * \param[in] :uint16_t  member: 
 *
 * \retval : none 
 */

void median_filter(uint16_t buffer[], uint16_t buffer_limit , uint16_t *buf_member, uint16_t member, uint8_t type) {

    uint16_t extreme;
    uint16_t i;
    
    uint16_t temp_index;

    if (*buf_member < buffer_limit) {       /* put five numbers in the present biggest array until add enough */
    
        buffer[(*buf_member)] = member;
        (*buf_member)++;
        return;
    }
    
    if(type == FIND_MAX) {

        extreme = 0xFFFF;
        for(i = 0; i < buffer_limit; i++ ) {
            
            if(extreme > buffer[i]) {                 //search for the smallest value
                
                extreme = buffer[i];
                temp_index = i;
                
            }
        }
        if (extreme < member) {
            
            buffer[temp_index] = member;
        }
    }
    else if(type == FIND_MIN) {
        
        extreme = 0;
        for(i = 0; i < buffer_limit; i++ ) {        //search for the biggest value
            
            if(extreme < buffer[i]) {
                
                extreme = buffer[i];
                temp_index = i;
            }
        }
        
        if (extreme > member) {

            buffer[temp_index] = member;
        }
        

    }

}





