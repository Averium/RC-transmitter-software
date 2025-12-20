#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "i2c_wrapper.h"
#include "spi_wrapper.h"
#include "adc_wrapper.h"

#include "rc_channel.h"

#include "application_config.h"
#include "application_types.h"
#include "application_utils.h"


static const char* TAG = "MAIN";

//static I2C_Bus i2c_bus = NULL;

//static I2C_Device i2c_mux = NULL;
//static I2C_Device i2c_throttle_axis = NULL;
//static I2C_Device i2c_steering_axis = NULL;

static ADC_Unit adc_unit = NULL;

static SPI_Device transciever = NULL;


void app_main(void) {

    // adc 1
    ESP_ERROR_CHECK(adc_unit_config(&adc_unit));
    ESP_LOGI(TAG, "ADC initialized successfully");

    // channel 1
    ESP_ERROR_CHECK(adc_add_channel(adc_unit, ADC_CHANNEL_0));
    ESP_ERROR_CHECK(adc_add_channel(adc_unit, ADC_CHANNEL_1));
    ESP_ERROR_CHECK(adc_add_channel(adc_unit, ADC_CHANNEL_2));
    ESP_ERROR_CHECK(adc_add_channel(adc_unit, ADC_CHANNEL_3));

    // i2c bus
    //ESP_ERROR_CHECK(i2c_bus_init(&i2c_bus));
    //ESP_LOGI(TAG, "I2C bus initialized successfully");

    // multiplexer
    //ESP_ERROR_CHECK(i2c_device_init(&i2c_mux, i2c_bus, TCA9548A_I2C_ADDRESS, I2C_FREQUENCY_HZ));
    //ESP_LOGI(TAG, "I2C multiplexer initialized successfully");

    // throttle
    //ESP_ERROR_CHECK(i2c_device_init(&i2c_throttle_axis, i2c_bus, MT6701_I2C_ADDRESS, I2C_FREQUENCY_HZ));
    //ESP_LOGI(TAG, "I2C throttle initialized successfully");

    // steering
    //ESP_ERROR_CHECK(i2c_device_init(&i2c_steering_axis, i2c_bus, MT6701_I2C_ADDRESS, I2C_FREQUENCY_HZ));
    //ESP_LOGI(TAG, "I2C steering initialized successfully");

    //const uint8 request_command[] = { 0x03, };

    //uint8 throttle_data_buffer[] = { 0x00, 0x00 };
    //uint8 steering_data_buffer[] = { 0x00, 0x00 };
    
    //AnalogInput* throttle = AnalogInput_init(U16_LIMIT_UNCALIBRATED, U14_CONTROLLER_DEADZONE, 1.0f, false);
    //AnalogInput* steering = AnalogInput_init(U16_LIMIT_UNCALIBRATED, U14_CONTROLLER_DEADZONE, 1.0f, true);

    AnalogInput* adc_test = AnalogInput_init(
        (uint16_limit){ 0u, U12_MAX }, U12_CONTROLLER_DEADZONE, ADC_IIR_FILTER_COEFFICIENT, false
    );

    //uint16 throttle_memory = 0u;
    //uint16 steering_memory = 0u;

    // SPI
    spi_bus_init(SPI2_HOST);
    spi_device_init(&transciever, SPI2_HOST, SPI_CS_PIN_NUM, SPI_CLOCK_SPEED_HZ);
    
    while (true) {

        //select_serial_channel(i2c_mux, SERIAL_CHANNEL_1);
        //ESP_ERROR_CHECK(i2c_write(i2c_throttle_axis, request_command, 1, I2C_TIMEOUT_MS));
        //ESP_ERROR_CHECK(i2c_read(i2c_throttle_axis, throttle_data_buffer, 2, I2C_TIMEOUT_MS));

        //select_serial_channel(i2c_mux, SERIAL_CHANNEL_2);
        //ESP_ERROR_CHECK(i2c_write(i2c_steering_axis, request_command, 1, I2C_TIMEOUT_MS));
        //ESP_ERROR_CHECK(i2c_read(i2c_steering_axis, steering_data_buffer, 2, I2C_TIMEOUT_MS));

        //uint16 throttle_raw = raw_to_14_bit(throttle_data_buffer);
        //uint16 steering_raw = raw_to_14_bit(steering_data_buffer);

        int32 test_raw;
        adc_read(adc_unit, ADC_CHANNEL_3, &test_raw);

        //AnalogInput_update(throttle, throttle_raw);
        //AnalogInput_update(steering, steering_raw);
        AnalogInput_update(adc_test, (uint16)test_raw);

        //if (throttle_memory != throttle_raw)
        //    ESP_LOGI(TAG, "Throttle = %.2f", AnalogInput_get_value(throttle));

        //if (steering_memory != steering_raw)
        //    ESP_LOGI(TAG, "Steering = %.2f", AnalogInput_get_value(steering));

        ESP_LOGI(TAG, "ADC measurement: %.3f", AnalogInput_get_value(adc_test));

        //throttle_memory = throttle_raw;
        //steering_memory = steering_raw;

        vTaskDelay(pdMS_TO_TICKS(APPLICATION_REFRESH_PERIOD_MS));
    }

}
