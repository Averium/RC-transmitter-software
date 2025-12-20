idf_component_register(
    SRCS
        "adc_wrapper.c"

    INCLUDE_DIRS
        "."

    REQUIRES
        utilities
        esp_adc
)