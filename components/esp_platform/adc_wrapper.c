#include "adc_wrapper.h"


esp_err_t adc_unit_config(ADC_Unit* object) {

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    return adc_oneshot_new_unit(&init_config, object);

}


esp_err_t adc_add_channel(const ADC_Unit adc_handle, adc_channel_t channel) {

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    return adc_oneshot_config_channel(adc_handle, channel, &config);

}


esp_err_t adc_read(ADC_Unit adc_handle, adc_channel_t channel, int32* data_buffer) {
    return adc_oneshot_read(adc_handle, channel, (int*)(data_buffer));
}