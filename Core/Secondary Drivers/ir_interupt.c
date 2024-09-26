#include "ir_interupt.h"

void ir_read()
{
    IR_calc_sensor_values(NONE);

    IR_calc_sensor_values(LEFT_FORWARD);
    IR_calc_sensor_values(LEFT_ANGLED45);
    IR_calc_sensor_values(LEFT_SIDES);
    
    IR_calc_sensor_values(RIGHT_FORWARD);
    IR_calc_sensor_values(RIGHT_ANGLED45);
    IR_calc_sensor_values(RIGHT_SIDES);

    IR_led_on(NONE);
}

void IR_calc_sensor_values(int sensor)
{
    switch (sensor)
    {
    case LEFT_FORWARD:
    {
        IR_led_on(LEFT_FORWARD);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.left_forward = MAX_0LIM16(IR_DMA_read_buffer[LEFT_FORWARD] - GL_IR_readings.left_forward, IR_MAX);
        break;
    }
    case LEFT_ANGLED45:
    {
        IR_led_on(LEFT_ANGLED45);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.left_angled45 = MAX_0LIM16(IR_DMA_read_buffer[LEFT_ANGLED45] - GL_IR_readings.left_angled45, IR_MAX);
        break;
    }
    case LEFT_SIDES:
    {
        IR_led_on(LEFT_SIDES);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.left_sides = MAX_0LIM16(IR_DMA_read_buffer[LEFT_SIDES] - GL_IR_readings.left_sides, IR_MAX);
        break;
    }
    case RIGHT_FORWARD:
    {
        IR_led_on(RIGHT_FORWARD);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.right_forward = MAX_0LIM16(IR_DMA_read_buffer[RIGHT_FORWARD] - GL_IR_readings.right_forward, IR_MAX);
        break;
    }
    case RIGHT_ANGLED45:
    {
        IR_led_on(RIGHT_ANGLED45);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.right_angled45 = MAX_0LIM16(IR_DMA_read_buffer[RIGHT_ANGLED45] - GL_IR_readings.right_angled45, IR_MAX);
        break;
    }
    case RIGHT_SIDES:
    {
        IR_led_on(RIGHT_SIDES);
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.right_sides = MAX_0LIM16(IR_DMA_read_buffer[RIGHT_SIDES] - GL_IR_readings.right_sides, IR_MAX);
        break;
    }
    default:
    {
        ADC_IR_DMA_read_to_buffer();
        GL_IR_readings.left_forward = IR_DMA_read_buffer[LEFT_FORWARD];
        GL_IR_readings.left_angled45 = IR_DMA_read_buffer[LEFT_ANGLED45];
        GL_IR_readings.left_sides = IR_DMA_read_buffer[LEFT_SIDES];

        GL_IR_readings.right_forward = IR_DMA_read_buffer[RIGHT_FORWARD];
        GL_IR_readings.right_angled45 = IR_DMA_read_buffer[RIGHT_ANGLED45];
        GL_IR_readings.right_sides = IR_DMA_read_buffer[RIGHT_SIDES];
        break;
    }
    }
}

// TODO: gpio on ir sensors
void IR_led_on(int sensor)
{
    switch (sensor)
    {
    case LEFT_FORWARD:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    case LEFT_ANGLED45:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    case LEFT_SIDES:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    case RIGHT_FORWARD:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    case RIGHT_ANGLED45:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    case RIGHT_SIDES:
    {
        //////////////////////
        delay_us(IR_ON_DELAY_US);
        break;
    }
    default:
    {////////////////////
        break;
    }
    }
}