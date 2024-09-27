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