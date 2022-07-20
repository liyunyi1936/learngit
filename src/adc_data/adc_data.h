#ifndef __ADC_DATA_H
#define __ADC_DATA_H
#include "adc_data.h"
#include "adc.h"

void mux_get_ADC_channel_data(uint8_t *chan);
float  process_ADC_data_with_filter(uint16_t *adc_val_array);
void  mux_channel_select(uint16_t chan);
uint32_t resist_val_cal(uint16_t resist_tag);


#define ADC_MUX_A0_SET()                 HAL_GPIO_WritePin(ADC_MUX_A0_GPIO_Port, ADC_MUX_A0_Pin, GPIO_PIN_SET)
#define ADC_MUX_A0_RESET()               HAL_GPIO_WritePin(ADC_MUX_A0_GPIO_Port, ADC_MUX_A0_Pin, GPIO_PIN_RESET)
#define ADC_MUX_A1_SET()                 HAL_GPIO_WritePin(ADC_MUX_A1_GPIO_Port, ADC_MUX_A1_Pin, GPIO_PIN_SET)
#define ADC_MUX_A1_RESET()               HAL_GPIO_WritePin(ADC_MUX_A1_GPIO_Port, ADC_MUX_A1_Pin, GPIO_PIN_RESET)
#define ADC_MUX_A2_SET()                 HAL_GPIO_WritePin(ADC_MUX_A2_GPIO_Port, ADC_MUX_A2_Pin, GPIO_PIN_SET)
#define ADC_MUX_A2_RESET()               HAL_GPIO_WritePin(ADC_MUX_A2_GPIO_Port, ADC_MUX_A2_Pin, GPIO_PIN_RESET)

#define ADC_MUX_A0_READ()                HAL_GPIO_ReadPin(ADC_MUX_A0_GPIO_Port, ADC_MUX_A0_Pin)
#define ADC_MUX_A1_READ()                HAL_GPIO_ReadPin(ADC_MUX_A1_GPIO_Port, ADC_MUX_A1_Pin)
#define ADC_MUX_A2_READ()                HAL_GPIO_ReadPin(ADC_MUX_A2_GPIO_Port, ADC_MUX_A2_Pin)

typedef enum _mux_channel
{
    MUX_CHANNEL_1 = 0,
    MUX_CHANNEL_2,
    MUX_CHANNEL_3,
    MUX_CHANNEL_4,
    MUX_CHANNEL_5,
    MUX_CHANNEL_6,
    MUX_CHANNEL_7,
    MUX_CHANNEL_8

}mux_channel_t;








#endif 


