#pragma once

#include <stdint.h>
#include "config.h"

#define LEFT 0
#define RIGHT 1
#define L_AND_R 2

#define LEFT_BIT_POSITION 2
#define FWD_BIT_POSITION 1
#define RIGHT_BIT_POSITION 0

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

typedef struct
{
    float left_speed;
    float right_speed;
} Speed;

Speed GL_searching_speed = {
    .left_speed = SEARCHING_SPEED,
    .left_speed = SEARCHING_SPEED,
};

Speed GL_fast_speed = {
    .left_speed = FAST_SPEED,
    .left_speed = FAST_SPEED,
};

uint32_t GL_accumilated_encoder_values[L_AND_R] = {0};
uint32_t n_cells_to_go = 0;

#define POS90 ROTATE_90_IN_PLACE_ENCODER_INCREMENTS
#define NEG90 -ROTATE_90_IN_PLACE_ENCODER_INCREMENTS
#define POS180 ROTATE_180_IN_PLACE_ENCODER_INCREMENTS
#define NEG180 -ROTATE_180_IN_PLACE_ENCODER_INCREMENTS

uint8_t GL_rotation_done = 1;

enum motion
{
    M_STOP,
    M_SLOW_LINEAR,
    M_SLOW_LINEAR,
    M_FAST_LINEAR,
    M_SLOW_ROTATIONAL,
    M_FAST_ROTATIONAL,
    M_WAIT_FOR_INPUT,
};

uint16_t GL_current_motion = M_WAIT_FOR_INPUT;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t angle;
} Position;

Position GL_mouse_position = {0}; /* at (0,0) facing +x direction. cw (+)ve, counter-cw (-)ve */

#define LR_SIDES 0
#define FRONT_SIDE 1
#define LFR_SIDES 2

/* cell is 0b[0-0-0-<recorded> <270_available>-<180_available>-<90_available>-<0_available>]*/
uint8_t GL_map[NUM_OF_CELLS_WIDTH][NUM_OF_CELLS_WIDTH] = {0};
uint16_t GL_map_lock = 0;

uint8_t GL_current_cell_mobility = 0;

#define LEFT_MOBILE_MASK 0b00000100
#define RIGHT_MOBILE_MASK 0b00000010
#define FORWARD_MOBILE_MASK 0b00000001
#define CELL_ACCESSED_MASK 0b00010000