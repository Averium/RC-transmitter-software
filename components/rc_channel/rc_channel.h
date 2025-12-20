#ifndef RC_CHANNELS_H
#define RC_CHANNELS_H


#include <stdbool.h>

#include "i2c_wrapper.h"
#include "application_config.h"
#include "application_types.h"


typedef struct AnalogInput AnalogInput;


AnalogInput* AnalogInput_init(uint16_limit raw_limits, uint16 deadzone, float32 filter, bool centered);

void AnalogInput_update(AnalogInput* object, uint16 raw_value);

float32 AnalogInput_get_value(const AnalogInput* object);


inline uint16 raw_to_14_bit(const uint8 data[2]) {
    return ((uint16)(data[0]) << 6) | (data[1] & 0x3F);
}

esp_err_t select_serial_channel(I2C_Device i2c_mux, SerialChannel channel);

/* NOT WORKING */
// void scan_serial_channels(I2C_Device i2c_mux, I2C_Device* devices[N_CHANNELS], bool availability[N_CHANNELS]);


#endif