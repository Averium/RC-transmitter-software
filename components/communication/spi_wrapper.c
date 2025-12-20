#include "spi_wrapper.h"
#include "application_utils.h"


esp_err_t spi_bus_init(spi_host_device_t host_id) {

    spi_bus_config_t spi_bus_config = {
        .miso_io_num = SPI_MISO_PIN_NUM,
        .mosi_io_num = SPI_MOSI_PIN_NUM,
        .sclk_io_num = SPI_SCLK_PIN_NUM,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = NRF24L01_TRANSFER_SIZE_BYTES,
    };

    return spi_bus_initialize(host_id, &spi_bus_config, SPI_DMA_CH_AUTO);
}

esp_err_t spi_device_init(SPI_Device* device, SPI_Host spi_host, uint8 chip_select_pin, uint32 clock_speed_hz) {
    
    spi_device_interface_config_t spi_device_config = {
        .clock_speed_hz = clock_speed_hz,
        .mode = 0,
        .spics_io_num = chip_select_pin,
        .queue_size = SPI_QUEUE_SIZE,
    };
    
    return spi_bus_add_device(spi_host, &spi_device_config, device);
}


esp_err_t spi_write(
    SPI_Device device,
    const uint8* tx_buffer,
    uint8 data_buffer_length
) {

    spi_transaction_t trans = {
        .length = data_buffer_length * BYTES_TO_BITS,
        .tx_buffer = tx_buffer,
        .rx_buffer = NULL,
    };

    return spi_device_transmit(device, &trans);

}


esp_err_t spi_read_write(
    SPI_Device device,
    const uint8* tx_buffer,
    uint8* rx_buffer,
    uint8 buffer_length
) {
    spi_transaction_t trans = {
        .length = buffer_length * BYTES_TO_BITS,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    };

    return spi_device_transmit(device, &trans);
}