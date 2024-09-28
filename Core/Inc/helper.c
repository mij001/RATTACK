#pragma once

#include "helper.h"

void delay_us(int time_us)
{
    uint16_t i = 0;
    while (time_us--)
    {
        i = 5;
        while (i--)
            ;
    }
}

void delay_ms(uint32_t time_ms)
{
    uint32_t last_tick = get_tick();
    while ((get_tick() - last_tick) < time_ms)
        ;
}

uint32_t get_encoder_val(uint32_t i)
{
    if (i)
    {
        return GL_encoder_values.left_enc;
    }
    else
    {
        return GL_encoder_values.right_enc;
    }
}

// max
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

// max 0
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

// min
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

// limit
inline uint32_t LIMIT32(uint32_t var, uint32_t min, uint32_t max)
{
    if (var < min)
    {
        return min;
    }
    if (var > max)
    {
        return max;
    }
    return var;
}
inline uint16_t LIMIT16(uint16_t var, uint16_t min, uint16_t max)
{
    if (var < min)
    {
        return min;
    }
    if (var > max)
    {
        return max;
    }
    return var;
}
inline float LIMIT_F(float var, float min, float max)
{
    if (var < min)
    {
        return min;
    }
    if (var > max)
    {
        return max;
    }
    return var;
}
