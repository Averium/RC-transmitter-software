#ifndef I2C_WRAPPER_H
#define I2C_WRAPPER_H


#include "driver/i2c_master.h"
#include "application_types.h"


typedef i2c_master_bus_handle_t I2C_Bus;
typedef i2c_master_dev_handle_t I2C_Device;


esp_err_t i2c_bus_init(I2C_Bus* object);
esp_err_t i2c_device_init(I2C_Device* object, I2C_Bus bus_handle, uint16 address, uint32 scl_speed_hz);


inline esp_err_t i2c_write(
    I2C_Device handle,
    const uint8* data_buffer,
    uint8 data_buffer_length,
    int32 timeout_ms
) {
    return i2c_master_transmit(handle, data_buffer, (size_t)(data_buffer_length), timeout_ms);
}


inline esp_err_t i2c_read(
    I2C_Device handle,
    uint8* data_buffer,
    uint8 data_buffer_length,
    int32 timeout_ms
) {
    return i2c_master_receive(handle, data_buffer, (size_t)(data_buffer_length), timeout_ms);
}


#endif