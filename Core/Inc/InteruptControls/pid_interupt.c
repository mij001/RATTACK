#include "pid_interupt.h"

// update encoders and use those values to set speed using a pid controller
void update_encoder_and_pid_speed_control(void)
{
    // set millisecond period of irq.s
    static uint32_t enc_pid_int_period_cmltv = 0;

    if (ENC_PID_INT_PERIOD <= enc_pid_int_period_cmltv)
    {
        update_encoder();
        pid_speed_control();
    }
    ++enc_pid_int_period_cmltv;
}

void update_encoder()
{
    /*
    TODO: Select appropriate timers in cubemx

    // left encoder input capture timer
    GL_encoder_values.left_enc = TIM2->CNT;
    TIM2->CNT = 0;

    // right encoder input capture timer
    GL_encoder_values.right_enc = TIM3->CNT;
    TIM3->CNT = 0;

    */
}

void pid_speed_control()
{
    static Pid_Calc_Values_t pid_calc_values = {0};
    uint32_t prev_motor_pwm[L_AND_R] = {0};

    static uint32_t osc_detect_time = 0;

    const Pid_Consts_t pid_consts = {
        .kp = SPEED_PID_KP,
        .ki = SPEED_PID_KI,
        .kd = SPEED_PID_KD,
    };

    for (uint32_t i = 0; i < L_AND_R; i++)
    {
        prev_motor_pwm[i] = GL_motor_pwm[i];

        // calculate primary values before pid calculation
        pid_calc_values.prev_error_t_minus_2[i] = pid_calc_values.prev_error_t_minus_1[i];
        pid_calc_values.prev_error_t_minus_1[i] = pid_calc_values.current_error[i];

        pid_calc_values.current_error[i] = GL_motor_pwm_target[i] - get_encoder_val(i);

        pid_calc_values.cmltv_error[i] += pid_calc_values.current_error[i];
        uint32_t cmltv_error_corrected = pid_calc_values.cmltv_error[i] * (pid_calc_values.current_error[i] < 100);

        uint32_t derrivitive_error = (pid_calc_values.current_error[i] - 2 * pid_calc_values.prev_error_t_minus_1[i] + pid_calc_values.prev_error_t_minus_2[i]);
        uint32_t derrivitive_error_corrected = derrivitive_error * (pid_calc_values.current_error[i] < 100);

        // pid value calculation
        GL_motor_pwm[i] = pid_consts.kp * pid_calc_values.current_error[i] +
                          pid_consts.ki * cmltv_error_corrected +
                          pid_consts.kd * derrivitive_error_corrected;

        GL_motor_pwm[i] = MAX_LIM(GL_motor_pwm[i], MOTOR_OUTPUT_MAX);
        GL_motor_pwm[i] = MIN_LIM(GL_motor_pwm[i], -MOTOR_OUTPUT_MAX);

#if OSC_SUPPRESSON_ENABLE

        // if previous speed not 0 and now its is start occilation detection
        if (prev_motor_pwm[i] != 0 && GL_motor_pwm_target[i] == 0)
        {
            osc_detect_time = get_tick();
        }

        // if detection period exceeds switch to suppression mode
        uint32_t exceed_time = get_tick() - osc_detect_time;
        if (GL_motor_pwm_target[i] == 0 && () OSC_SUPR_PERIOD < exceed_time)
        {
            GL_motor_pwm[i] = GL_motor_pwm[i] * OSC_SUPR_BRAKE_FACTOR;
        }
#endif
    }
}
