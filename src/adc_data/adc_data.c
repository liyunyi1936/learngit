#include "adc_data.h"
#include "Dichotomous_search.h"
#include "get_real_temp_value.h"
#include "ntc_table.h"

uint8_t channel = MUX_CHANNEL_1; 
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

#define ARRAY_NUM(a) (sizeof(a)/sizeof(a[0]))

extern float temp_val;
uint32_t resist[6];
float j_real_Temp_value[2];
float g_real_Temp_value[2];

 
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
            resist[0] = resist_val_cal(R67);
            search_and_get_value(j2_form_value, j2_form_value_num, resist[0], &j_real_Temp_value[0]);
            search_and_get_value(g2_form_value, g2_form_value_num, resist[0], &g_real_Temp_value[0]);
            *chan = MUX_CHANNEL_2; 
            break;

        case MUX_CHANNEL_2:
            resist[1] = resist_val_cal(R66);
            search_and_get_value(j2_form_value, j2_form_value_num, resist[1], &j_real_Temp_value[1]);
            search_and_get_value(g2_form_value, g2_form_value_num, resist[1], &g_real_Temp_value[1]);
            *chan = MUX_CHANNEL_3; 
            break;

        case MUX_CHANNEL_3:
            resist[2] = resist_val_cal(R65);
            *chan = MUX_CHANNEL_4;
            break;

        case MUX_CHANNEL_4:
            resist[3] = resist_val_cal(R64);
            *chan = MUX_CHANNEL_5;
            break;

        case MUX_CHANNEL_5:
            resist[4] = resist_val_cal(R63);
            *chan = MUX_CHANNEL_6;
            break;

        case MUX_CHANNEL_6:
            resist[5] = resist_val_cal(R69);
            *chan = MUX_CHANNEL_7;
            break;

        case MUX_CHANNEL_7:
            adc_cal = (adc_vol * (R71 + R72)) / R72;
            *chan = MUX_CHANNEL_1;
            break;

        case MUX_CHANNEL_8:
            break;

        default: 
            break;

    } 

    mux_channel_select(*chan);

}

/**
 * \brief : resist_val_cal
 * \param[in] : uint16_t resist_tag: names of resistors for different channels(such as: R69)
 * \retval : uint32_t resistance_value 
 */
static uint32_t resist_val_cal(uint16_t resist_tag)
{
    uint32_t resistance_value = 0;
    resistance_value = (uint32_t)((adc_vol / RATE_K * resist_tag * THOUSAND) / (VDD33 - (adc_vol / RATE_K)));
    return resistance_value;

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



 

