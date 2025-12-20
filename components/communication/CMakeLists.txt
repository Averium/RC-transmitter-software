idf_component_register(
    SRCS
        "i2c_wrapper.c"
        "spi_wrapper.c"

    INCLUDE_DIRS
        "."

    REQUIRES
        utilities
        driver
)