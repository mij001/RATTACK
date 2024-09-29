#pragma once

#include "ir_secondary.h"

int16_t get_ir_difference(void)
{
    uint16_t left45_ir_norm = GL_IR_readings.left_angled45 - IR_LEFT45_MEAN;
    uint16_t right45_ir_norm = GL_IR_readings.right_angled45 - IR_RIGHT45_MEAN;

    // if any offset is unusually low ignore it
    int16_t ir_difference = left45_ir_norm - right45_ir_norm;
    if (left45_ir_norm < IR_LEFT45_IGNORE)
    {
        ir_difference = -right45_ir_norm;
    }
    if (right45_ir_norm < IR_RIGHT45_IGNORE)
    {
        ir_difference = left45_ir_norm;
    }
    if ((left45_ir_norm < IR_LEFT45_IGNORE) && (right45_ir_norm < IR_RIGHT45_IGNORE))
    {
        ir_difference = 0;
    }

    return ir_difference;
}

uint16_t front_wall_detect(void)
{
    uint16_t left_fwd_ir_norm = GL_IR_readings.left_forward - IR_LEFT_FWD_MEAN;
    uint16_t right_fwd_ir_norm = GL_IR_readings.right_forward - IR_RIGHT_FWD_MEAN;

    uint16_t lt = ((left_fwd_ir_norm > IR_LEFT_FWD_DETECT_THRESH) &&
                   ((left_fwd_ir_norm + right_fwd_ir_norm) > IR_FWD_DETECT_THRESH));
    uint16_t rt = ((right_fwd_ir_norm > IR_RIGHT_FWD_DETECT_THRESH) &&
                   ((left_fwd_ir_norm + right_fwd_ir_norm) > IR_FWD_DETECT_THRESH));

    return lt || rt;
}

uint8_t get_cell_mobility_relative(uint8_t sides)
{
    /* returns ob 0000 0 <no_left_wall=1> <no_farward_wall=1> <no_right_wall=1> */

    uint16_t left45_ir_norm = GL_IR_readings.left_angled45 - IR_LEFT45_MEAN;
    uint16_t right45_ir_norm = GL_IR_readings.right_angled45 - IR_RIGHT45_MEAN;

    uint8_t mobility = 0;

    if (left45_ir_norm < MOBILITY_LEFT45_DETECT_THRESH)
    {
        mobility |= (0x1 << LEFT_BIT_POSITION);
    }
    if (right45_ir_norm < MOBILITY_RIGHT45_DETECT_THRESH)
    {
        mobility |= (0x1 << RIGHT_BIT_POSITION);
    }

    if (sides == LR_SIDES)
    {
        return mobility;
    }

    uint16_t lt = ((GL_IR_readings.left_forward > MOBILITY_FWD_DETECT_THRESH) &&
                   ((GL_IR_readings.left_forward + GL_IR_readings.right_forward) > MOBILITY_FWD_DETECT_THRESH));
    uint16_t rt = ((GL_IR_readings.right_forward > MOBILITY_FWD_DETECT_THRESH) &&
                   ((GL_IR_readings.left_forward + GL_IR_readings.right_forward) > MOBILITY_FWD_DETECT_THRESH));

    if (lt || rt)
    {
        if (sides == FRONT_SIDE)
        {
            return (uint8_t)(0x1 << FWD_BIT_POSITION);
        }

        mobility |= (0x1 << FWD_BIT_POSITION);
    }
    if (sides == FRONT_SIDE)
    {
        return (uint8_t)(0x0);
    }
    return mobility;
}
