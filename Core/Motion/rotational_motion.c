#include "rotational_motion.h"

void slow_speed_rotational_motion_pid(int32_t angle)
{
    static int32_t accumilated_encoder_value[2] = {0, 0};

    switch (angle)
    {
    case 90:
        angle = POS90 * ROTATE_COMPENSATION;
        break;
    case -90:
        angle = NEG90 * ROTATE_COMPENSATION;
        break;
    case 180:
        angle = POS90 * ROTATE_COMPENSATION;
        break;
    case -180:
        angle = NEG90 * ROTATE_COMPENSATION;
        break;
    }

    // get the accumilated encoder values
    accumilated_encoder_value[LEFT] += GL_encoder_values.left_enc * 2;
    accumilated_encoder_value[RIGHT] -= GL_encoder_values.right_enc * 2;

    // porpotional control
    Speed rot_speed = {
        .left_speed = LIMIT_F(ROTATIONAL_KP * (angle - accumilated_encoder_value[LEFT]), -MAX_ROTATIONAL_SPEED, MAX_ROTATIONAL_SPEED),
        .right_speed = LIMIT_F(ROTATIONAL_KP * (angle - accumilated_encoder_value[RIGHT]), -MAX_ROTATIONAL_SPEED, MAX_ROTATIONAL_SPEED),
    };

    // check if the rotated angle is within the acceptable range
    if ((-MINIMUM_ACCEPTABLE_ANGLE < (angle - accumilated_encoder_value[LEFT])) && (((angle - accumilated_encoder_value[LEFT]) < MINIMUM_ACCEPTABLE_ANGLE) &&
                                                                                    (-MINIMUM_ACCEPTABLE_ANGLE < (angle - accumilated_encoder_value[RIGHT])) && ((angle - accumilated_encoder_value[LEFT]) < MINIMUM_ACCEPTABLE_ANGLE)))
    {
        // reset accumilation
        accumilated_encoder_value[LEFT] = 0;
        accumilated_encoder_value[RIGHT] = 0;

        GL_rotation_done = 1;
        return;
    }

    set_motor_pwm(rot_speed.left_speed, -rot_speed.right_speed);
}

void fast_speed_rotational_motion_pid(int32_t angle)
{
    // cumilate encoder values
    static int32_t accumilated_encoder_value[L_AND_R] = {
        0,
        0,
    };
    accumilated_encoder_value[LEFT] += GL_encoder_values.left_enc;
    accumilated_encoder_value[RIGHT] += GL_encoder_values.right_enc;

    float error_left = 0, error_right = 0;
    if (angle == 90)
    {
        error_left = ((float)FAST_ROTATIONAL_SMALL_TAN_VELOCITY - (float)accumilated_encoder_value[LEFT]);
        error_right = ((float)FAST_ROTATIONAL_LARGE_TAN_VELOCITY - (float)accumilated_encoder_value[RIGHT]);
    }
    else if (angle == -90)
    {
        error_left = ((float)FAST_ROTATIONAL_LARGE_TAN_VELOCITY - (float)accumilated_encoder_value[LEFT]);
        error_right = ((float)FAST_ROTATIONAL_SMALL_TAN_VELOCITY - (float)accumilated_encoder_value[RIGHT]);
    }

    // check if error is within acceptable range
    if  (error_left < FAST_MINIMUM_ACCEPTABLE_ANGLE && error_left > -FAST_MINIMUM_ACCEPTABLE_ANGLE &&
        (error_right) < FAST_MINIMUM_ACCEPTABLE_ANGLE && (error_right) > -FAST_MINIMUM_ACCEPTABLE_ANGLE)
    {
        accumilated_encoder_value[LEFT] = 0;
        accumilated_encoder_value[RIGHT] = 0;
        set_motion(M_STOP);
        return;
    }

    // generate speed values according to rotational data
    Speed turn_speed = {
        .left_speed = FAST_ROTATIONAL_KP * error_left,
        .right_speed = FAST_ROTATIONAL_KP * error_right,
    };

    /*
        multiplied with the turn radui ratio in order to make the increments porpotional to radi
        otherwise they would never reach desired value atathe same time
    */
    if (angle == 90)
    {
        turn_speed.right_speed *= FAST_ROTATIONAL_RADI_RATIO;
    }
    else if (angle == -90)
    {
        turn_speed.left_speed *= FAST_ROTATIONAL_RADI_RATIO;
    }

    turn_speed.right_speed = MAX_LIM_F(turn_speed.right_speed, FAST_ROTATIONAL_MAX_SPEED);
    turn_speed.left_speed = MAX_LIM_F(turn_speed.left_speed, FAST_ROTATIONAL_MAX_SPEED);
    set_motor_pwm(turn_speed.left_speed, turn_speed.right_speed);
}
