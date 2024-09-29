#include "linear_motion.h"

void slow_speed_linear_motion_pid(void)
{
    int16_t ir_difference = get_ir_difference();

    // max ir difference is capped for it to be deterministic
    ir_difference = MAX_LIM_F(ir_difference, MAX_IR_DIFFERENCE);
    ir_difference = MIN_LIM_F(ir_difference, -MAX_IR_DIFFERENCE);
    float ir_ratio = ir_difference / MAX_IR_DIFFERENCE;

    // usually 2 speeds are same in linear motion but for to make sure
    float slow_speed = (float)(GL_searching_speed.left_speed + GL_searching_speed.right_speed) / 2;

    float correction = slow_speed * SEARCHING_LINEAR_KP * ir_ratio;

    Speed corrected_speed = {
        .left_speed = GL_searching_speed.left_speed + correction,
        .right_speed = GL_searching_speed.right_speed - correction,
    };

    set_motor_pwm(corrected_speed.left_speed, corrected_speed.right_speed);
}

void fast_speed_linear_motion_pid(void)
{
    /*
        idea is to get needed encoder values to get to the linear distance and use an
        acceleration and deaccelearation curve vased on remaining encoder values and
        accumilated encoder values to get to the destination linear possition faster,
        WHIILE also maintaining the midline of the path using the ir difference.
     */

    uint32_t n_distance_to_go = ENCODER_TICKS_PER_GRID_CELL * n_cells_to_go;

    int16_t ir_difference = get_ir_difference();
    GL_accumilated_encoder_values[LEFT] += GL_encoder_values.left_enc;
    GL_accumilated_encoder_values[RIGHT] += GL_encoder_values.right_enc;

    float remaining_distance_to_go[] = {
        n_distance_to_go - GL_accumilated_encoder_values[LEFT],
        n_distance_to_go - GL_accumilated_encoder_values[RIGHT],
    };

    /*
        displacement from midpoint considering midpoint = 0, when limited acts as a
        acceleration constant speed and dwacceleration
     */
    float displacement_from_midpoint[] = {
        LIMIT_F(n_distance_to_go * .5 - GL_accumilated_encoder_values[LEFT], -FAST_SPEED_CORRECTION_MAX, FAST_SPEED_CORRECTION_MAX),
        LIMIT_F(n_distance_to_go * .5 - GL_accumilated_encoder_values[RIGHT], -FAST_SPEED_CORRECTION_MAX, FAST_SPEED_CORRECTION_MAX),
    };

    Speed fast_speed_correction_delta = {
        .left_speed = FAST_LINEAR_KP * displacement_from_midpoint[LEFT],
        .right_speed = FAST_LINEAR_KP * displacement_from_midpoint[RIGHT],
    };

    /*
       by multiplying this with done and remaining distance velocity curve can be smotthed out
    */
    float accumilated_encoder_values_ratio[] = {
        ((float)GL_accumilated_encoder_values[LEFT]) / ((float)n_distance_to_go),
        ((float)GL_accumilated_encoder_values[RIGHT]) / ((float)n_distance_to_go),
    };
    float remaining_distance_to_go_ratio[] = {
        ((float)remaining_distance_to_go[LEFT]) / ((float)n_distance_to_go),
        ((float)remaining_distance_to_go[RIGHT]) / ((float)n_distance_to_go),
    };

    float fast_speed_acc_kp_scaled_left = ((float)GL_accumilated_encoder_values[LEFT]) * FAST_LINEAR_ACCEL_KP;
    float fast_speed_acc_kp_scaled_right = ((float)remaining_distance_to_go[RIGHT]) * FAST_LINEAR_DEACCEL_KP;
    float fast_speed_deacc_kp_scaled_left = ((float)GL_accumilated_encoder_values[LEFT]) * FAST_LINEAR_ACCEL_KP;
    float fast_speed_deacc_kp_scaled_right = ((float)remaining_distance_to_go[RIGHT]) * FAST_LINEAR_DEACCEL_KP;

    fast_speed_acc_kp_scaled_left = MAX_LIM_F(fast_speed_acc_kp_scaled_left, 1.0);
    fast_speed_acc_kp_scaled_right = MAX_LIM_F(fast_speed_acc_kp_scaled_right, 1.0);
    fast_speed_deacc_kp_scaled_left = MAX_LIM_F(fast_speed_deacc_kp_scaled_left, 1.0);
    fast_speed_deacc_kp_scaled_right = MAX_LIM_F(fast_speed_deacc_kp_scaled_right, 1.0);

    fast_speed_correction_delta.left_speed *= fast_speed_acc_kp_scaled_left * fast_speed_deacc_kp_scaled_left;
    fast_speed_correction_delta.right_speed *= fast_speed_acc_kp_scaled_right * fast_speed_deacc_kp_scaled_right;

    /*
        add correcttion to the base velocity to get the corrected velocity
    */
    Speed fast_speed_corrected = {
        .left_speed = fast_speed_correction_delta.left_speed + FAST_SPEED,
        .right_speed = fast_speed_correction_delta.right_speed + FAST_SPEED,
    };

/*
    correction using ir can also be applied on top of encoder correction for good measure
*/
#if FAST_SPEED_IR_CORRECTION

    int16_t ir_difference = get_ir_difference();

    // max ir difference is capped for it to be deterministic
    ir_difference = LIMIT_F(ir_difference, -MAX_IR_DIFFERENCE, MAX_IR_DIFFERENCE);

    float fast_speed_ir_kp=0;

    fast_speed_corrected.left_speed += ir_difference * fast_speed_ir_kp;
    fast_speed_corrected.right_speed -= ir_difference * fast_speed_ir_kp;

// FIXME: need to define fast_speed_ir_kp
// FIXME: need to add dynamin scaling of fast_speed_ir_kp in oder to make it harder to wiggle at higher speeds
#endif

    set_motor_pwm(fast_speed_corrected.left_speed, fast_speed_corrected.right_speed);
}
