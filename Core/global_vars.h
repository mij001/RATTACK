#include <stdint.h>

#define LEFT 0
#define RIGHT 1
#define L_AND_R 2

uint32_t GL_motor_pwm[L_AND_R] = {0};
uint32_t GL_motor_pwm_target[L_AND_R] = {0};

typedef struct
{
    uint32_t left_enc;
    uint32_t right_enc;
} Encoder_Values_t;

Encoder_Values_t GL_encoder_values = {0};

uint16_t IR_DMA_read_buffer[6] = {0};

typedef struct
{
    uint16_t left_forward;
    uint16_t left_angled45;
    uint16_t left_sides;
    uint16_t right_forward;
    uint16_t right_angled45;
    uint16_t right_sides;
} IR_Readings_t;

IR_Readings_t GL_IR_readings = {0};

enum IR_Sensor
{
    LEFT_FORWARD,
    LEFT_ANGLED45,
    LEFT_SIDES,

    RIGHT_FORWARD,
    RIGHT_ANGLED45,
    RIGHT_SIDES,
    
    NONE,
};
