#ifndef APPLICATION_TYPES_H
#define APPLICATION_TYPES_H


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

typedef signed char int8;
typedef signed long int32;

typedef float float32;


typedef enum {
    ERROR_OK,
    ERROR_INVALID_OBJECT_POINTER,
    ERROR_FAILED_ESP_CALL,
    ERROR_OUT_OF_RANGE_FUNCTION_ARGUMENT,
    ERROR_INVALID_FUNCTION_ARGUMENT,
    N_ERRORS,
} ApplicationErrorType;


typedef enum {
    SERIAL_CHANNEL_1,
    SERIAL_CHANNEL_2,
    SERIAL_CHANNEL_3,
    SERIAL_CHANNEL_4,
    SERIAL_CHANNEL_5,
    SERIAL_CHANNEL_6,
    N_SERIAL_CHANNELS,
} SerialChannel;


typedef struct {
    float32 min;
    float32 max;
} float32_limit;


typedef struct {
    uint32 min;
    uint32 max;
} uint32_limit;


typedef struct {
    uint16 min;
    uint16 max;
} uint16_limit;


#endif