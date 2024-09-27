#pragma once
#include <stdint.h>

#include "global_vars.h"

inline uint32_t MAX_LIM32(uint32_t var, uint32_t max)
{
    return var > max ? max : var;
}
inline uint16_t MAX_LIM16(uint16_t var, uint16_t max)
{
    return var > max ? max : var;
}
inline float MAX_LIM_F(float var, float max)
{
    return var > max ? max : var;
}

inline uint32_t MAX_0LIM32(uint32_t var, uint32_t max)
{
    return var > max ? 0 : var;
}
inline uint16_t MAX_0LIM16(uint16_t var, uint16_t max)
{
    return var > max ? 0 : var;
}
inline float MAX_0LIM_F(float var, float max)
{
    return var > max ? 0 : var;
}

inline uint32_t MIN_LIM32(uint32_t var, uint32_t min)
{
    return var < min ? min : var;
}
inline uint16_t MIN_LIM16(uint16_t var, uint16_t min)
{
    return var < min ? min : var;
}
inline float MIN_LIM_F(float var, float min)
{
    return var < min ? min : var;
}

uint32_t get_encoder_val(uint32_t i);

////////// TODO : STUB REPAIR
uint32_t get_tick(void) {}
void set_motor_pwm(uint32_t left_pwm, uint32_t right_pwm);
void ADC_IR_DMA_read_to_buffer();
