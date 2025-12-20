#ifndef SPI_WRAPPER_H
#define SPI_WRAPPER_H


#include "application_types.h"
#include "application_config.h"
#include "driver/spi_master.h"


typedef spi_host_device_t SPI_Host;
typedef spi_device_handle_t SPI_Device;

esp_err_t spi_bus_init(spi_host_device_t host_id);

esp_err_t spi_device_init(SPI_Device* object, SPI_Host spi_host, uint8 chip_select_pin, uint32 clock_speed_hz);

esp_err_t spi_write(
    SPI_Device device_handle,
    const uint8* data_buffer,
    uint8 data_buffer_length
);

esp_err_t spi_read_write(
    SPI_Device device,
    const uint8* tx_buffer,
    uint8* rx_buffer,
    uint8 buffer_length
);


#endif