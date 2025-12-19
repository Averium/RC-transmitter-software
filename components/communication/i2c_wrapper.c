#include "i2c_wrapper.h"
#include "application_config.h"



esp_err_t i2c_bus_init(I2C_Bus* object) {

    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = -1, // Auto select
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    return i2c_new_master_bus(&i2c_mst_config, object);
}


esp_err_t i2c_device_init(I2C_Device* object, I2C_Bus bus_handle, uint16 address, uint32 scl_speed_hz) {

    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = address,
        .scl_speed_hz = scl_speed_hz,
    };

    return i2c_master_bus_add_device(bus_handle, &device_config, object);
}
