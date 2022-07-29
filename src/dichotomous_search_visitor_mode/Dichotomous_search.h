#ifndef __DICHOTOMOUS_SEARCH_H
#define __DICHOTOMOUS_SEARCH_H

#include <stdint.h>
int8_t dichotomous_search(void *arr, uint32_t data_type_len, uint32_t data_len, void *target, 
                          int8_t(*compare_func)(void *member_1, void *member_2), uint32_t *num) ;

#endif  

