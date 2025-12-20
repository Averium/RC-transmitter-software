#include "rc_channel.h"
#include "application_utils.h"


struct AnalogInput {
    uint16 raw_value;
    uint16_limit raw_limits;

    uint16 deadzone;
    float32 filter;
    
    float32 mapped_value;

    bool centered;
};


typedef enum {
    LEFT,
    RIGHT,
} AnalogInputSide;


typedef struct {
    uint16 value;
    uint16_limit limit;
    AnalogInputSide side;
} DeadzoneReturnType;


static DeadzoneReturnType AnalogInput_deadzone(const AnalogInput* object, uint16 raw_value) {

    if (object->deadzone == 0) {
        return (DeadzoneReturnType) { raw_value, object->raw_limits, RIGHT };
    }

    uint16_limit shrinked_limit = shrink_uint16_limit(object->raw_limits, object->deadzone);
    uint16 saturated_value = saturate_uint16(raw_value, &shrinked_limit);

    return (DeadzoneReturnType) { saturated_value, shrinked_limit, RIGHT };

}


static DeadzoneReturnType AnalogInput_deadzone_center(const AnalogInput* object, uint16 raw_value) {

    uint16 center = ((object->raw_limits.min + object->raw_limits.max ) / 2u);

    if (object->deadzone == 0) {
        return (DeadzoneReturnType) { raw_value, object->raw_limits, raw_value < center ? LEFT : RIGHT };
    }

    uint16_limit shrinked_limit;
    AnalogInputSide side;

    if (raw_value < center) {
        shrinked_limit.min = object->raw_limits.min + object->deadzone;
        shrinked_limit.max = center - object->deadzone;
        side = LEFT;

    }
    else {
        shrinked_limit.min = center + object->deadzone; 
        shrinked_limit.max = object->raw_limits.max - object->deadzone;
        side = RIGHT;
    }

    uint16 saturated_value = saturate_uint16(raw_value, &shrinked_limit);

    return (DeadzoneReturnType){ saturated_value, shrinked_limit, side };

}


static uint16 AnalogInput_filter(const AnalogInput* object, uint16 raw_value) {

    // if (object->filter > 0.95f) { return raw_value; }
    return (uint16)(((float32)(raw_value)) * object->filter + ((float32)(object->raw_value)) * (1.0f - object->filter));
}


static void AnalogInput_calibrate(AnalogInput* object, uint16 raw_value) {
    if (object->raw_limits.max < object->raw_limits.min) {
        object->raw_limits.min = raw_value;
        object->raw_limits.max = raw_value;
        return;
    }
    if (raw_value < object->raw_limits.min) { object->raw_limits.min = raw_value; }
    if (raw_value > object->raw_limits.max) { object->raw_limits.max = raw_value; }
}


AnalogInput* AnalogInput_init(uint16_limit raw_limits, uint16 deadzone, float32 filter, bool centered) {

    const static float32_limit filter_limit = (float32_limit) { 0.0f, 1.0f };

    AnalogInput* object = malloc(sizeof(AnalogInput));

    if (!object) {
        return NULL;
    }

    object->raw_value = 0u;
    object->mapped_value = 0.0f;
    
    object->raw_limits = raw_limits;
    object->deadzone = deadzone;
    object->filter = saturate_float32(filter, &filter_limit);
    object->centered = centered;

    return object;
}


void AnalogInput_update(AnalogInput* object, uint16 raw_value) {

    raw_value = AnalogInput_filter(object, raw_value);

    AnalogInput_calibrate(object, raw_value);
    
    if (object->raw_limits.max == object->raw_limits.min) { return; }

    DeadzoneReturnType deadzone;
    float32_limit raw_limits;
    float32_limit map_limits;

    if (object->centered) {
        deadzone = AnalogInput_deadzone_center(object, raw_value);
        raw_limits = (float32_limit) { deadzone.limit.min, deadzone.limit.max };
        map_limits = (deadzone.side == LEFT ? (float32_limit){ -1.0f, 0.0f } : (float32_limit){ 0.0f, 1.0f });
    }

    else {
        deadzone = AnalogInput_deadzone(object, raw_value);
        raw_limits = (float32_limit) { deadzone.limit.min, deadzone.limit.max };
        map_limits = (float32_limit) { 0.0f, 1.0f };
    }

    float32 mapped_value = map_float32((float32)(deadzone.value), raw_limits, map_limits);

    object->raw_value = raw_value;
    object->mapped_value = mapped_value;

}


float32 AnalogInput_get_value(const AnalogInput* object) {
    return object->mapped_value;
}


esp_err_t select_serial_channel(I2C_Device i2c_mux, SerialChannel channel) {
    uint8 data = 1 << (uint8)(channel);
    return i2c_write(i2c_mux, &data, 1u, I2C_TIMEOUT_MS);
}

/*
void scan_serial_channels(I2C_Device i2c_mux, I2C_Device* devices[N_CHANNELS], bool availability[N_CHANNELS]) {

    // NOT WORKING
    uint8 probe_data[] = { 0x03, };
    uint8 raw_data[2] = { 0x00, 0x00 };

    for (int channel = CHANNEL_1; channel < N_CHANNELS; ++channel) {

        if ((*devices[channel]) == NULL) {
            availability[channel] = false;
            continue;
        }

        select_serial_channel(i2c_mux, channel + 1);

        esp_err_t check_1 = i2c_write((*devices[channel]), probe_data, 1, I2C_SCAN_TIMEOUT_MS);
        esp_err_t check_2 = i2c_read((*devices[channel]), raw_data, 1, I2C_SCAN_TIMEOUT_MS);
        availability[channel] = ((check_1 == ESP_OK) && (check_2 == ESP_OK));
    }   
}
*/