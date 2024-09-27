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
