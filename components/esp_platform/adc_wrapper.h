#ifndef ADC_WRAPPER_H
#define ADC_WRAPPER_H

#include "esp_adc/adc_oneshot.h"
#include "application_types.h"


typedef struct adc_oneshot_config_channel_t ADC_Channel;
typedef adc_oneshot_unit_handle_t ADC_Unit;


esp_err_t adc_unit_config(ADC_Unit* object);

esp_err_t adc_add_channel(const ADC_Unit adc_handle, adc_channel_t channel);

esp_err_t adc_read(ADC_Unit adc_handle, adc_channel_t channel, int32* data_buffer);


#endif