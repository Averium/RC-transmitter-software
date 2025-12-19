idf_component_register(
    SRCS
        "i2c_wrapper.c"
        "rc_channels.c"

    INCLUDE_DIRS
        "."

    REQUIRES
        utilities
        driver
)