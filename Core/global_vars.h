#include <stdint.h>

#define LEFT 0
#define RIGHT 1
#define L_AND_R 2

uint32_t GL_motor_pwm[L_AND_R]={0};
uint32_t GL_motor_pwm_target[L_AND_R]={0};

typedef struct
{
    uint32_t left_enc;
    uint32_t right_enc;
} GL_encoder_values_t;

GL_encoder_values_t GL_encoder_values = {0};

