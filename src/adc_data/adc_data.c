#include "adc_data.h"
#include "stdint.h"
#include "Dichotomous_search.h"
#include "get_real_temp_value.h"
#include "ntc_table.h"

uint8_t channel = MUX_CHANNEL_1; 
uint32_t resistance_value  = 0;
float temp_adc_value = 0;
float adc_vol ;
float adc_cal = 0;

#define RATE_K                        (float)1000.0        /* the rate between V with mV */
#define THOUSAND                      (float)1000.0
#define VDD33                         (float)3.3 
#define ADC_VREF                      (float)3.3           /* the adc reference voltage */
#define ADC_RANGE                     (float)4096.0        /* adc 12 bit range */

#define R63                           200
#define R64                           200
#define R65                           10
#define R66                           200
#define R67                           200
#define R69                           200
#define R71                           10
#define R72                           10


//extern float j2_form_value[];    /* known data from Excel blanks*/
//extern float g2_form_value[];
extern float temp_val;

uint32_t resist[6];
float j_real_Temp_value ;
float g_real_Temp_value;

 
/**
 * \brief : process adc data
 * \param[in] : *chan : the pointer pointe to what parameter input
 * \retval : none
 */
void mux_get_ADC_channel_data(uint8_t *chan)
{
    temp_adc_value             =  temp_val;
    temp_val = 0;
    adc_vol                    = (temp_adc_value* ADC_VREF * RATE_K) / ADC_RANGE;       /* the value of voltage */

    switch(*chan) {

        case MUX_CHANNEL_1:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R67 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[0] = resistance_value;
            break;

        case MUX_CHANNEL_2:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R66 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[1]  = resistance_value;
            break;

        case MUX_CHANNEL_3:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R65 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[2] = resistance_value;
            break;

        case MUX_CHANNEL_4:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R64 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[3] = resistance_value;
            break;

        case MUX_CHANNEL_5:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R63 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[4] = resistance_value;
            break;

        case MUX_CHANNEL_6:
            resistance_value = (uint32_t)((adc_vol / RATE_K * R69 * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
            resist[5] = resistance_value;
            break;

        case MUX_CHANNEL_7:
            adc_cal = (adc_vol * (R71 + R72)) / R72;
            break;

        case MUX_CHANNEL_8:
            break;

        default: 
            break;

    } 
    
     search_and_get_value(j2_form_value, 4400, resistance_value, &j_real_Temp_value);
     search_and_get_value(g2_form_value, 4400, resistance_value, &g_real_Temp_value);
        
    switch (*chan) {

        case MUX_CHANNEL_1:
            *chan = MUX_CHANNEL_2; 
            break;
        case MUX_CHANNEL_2:
            *chan = MUX_CHANNEL_3;
            break;
        case MUX_CHANNEL_3:
            *chan = MUX_CHANNEL_4;
            break;
        case MUX_CHANNEL_4:
            *chan = MUX_CHANNEL_5;
            break;
        case MUX_CHANNEL_5:
            *chan = MUX_CHANNEL_6;
            break;
        case MUX_CHANNEL_6:
            *chan = MUX_CHANNEL_7;
            break;
        case MUX_CHANNEL_7:
            *chan = MUX_CHANNEL_1;
            break;
        default:
            break;
            }
          
        mux_channel_select(*chan);

}


/**
 * \brief : Multiplexed channel selection
 * \param[in] : *chan : the pointer pointe to what parameter input
 * \retval : none
 */
void  mux_channel_select(uint16_t chan)
{
    mux_channel_t channel = chan;

    switch(channel) {

    case MUX_CHANNEL_1:

        ADC_MUX_A0_RESET();
        ADC_MUX_A1_RESET();
        ADC_MUX_A2_RESET();
        break;

    case MUX_CHANNEL_2:

        ADC_MUX_A0_SET();
        ADC_MUX_A1_RESET();
        ADC_MUX_A2_RESET();
        break;

    case MUX_CHANNEL_3:

        ADC_MUX_A0_RESET();
        ADC_MUX_A1_SET();
        ADC_MUX_A2_RESET();
        break;

    case MUX_CHANNEL_4:

        ADC_MUX_A0_SET();
        ADC_MUX_A1_SET();
        ADC_MUX_A2_RESET();
        break;

    case MUX_CHANNEL_5:

        ADC_MUX_A0_RESET();
        ADC_MUX_A1_RESET();
        ADC_MUX_A2_SET();
        break;

    case MUX_CHANNEL_6:

        ADC_MUX_A0_SET();
        ADC_MUX_A1_RESET();
        ADC_MUX_A2_SET();
        break;

    case MUX_CHANNEL_7:

        ADC_MUX_A0_RESET();
        ADC_MUX_A1_SET();
        ADC_MUX_A2_SET();
        break;

    case MUX_CHANNEL_8:

        ADC_MUX_A0_SET();
        ADC_MUX_A1_SET();
        ADC_MUX_A2_SET();
        break;

    default:
        break;
 
    }
}



 

