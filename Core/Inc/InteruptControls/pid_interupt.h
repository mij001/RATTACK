#include <stdint.h>

#include "config.h"
#include "global_vars.h"
#include "helper.h"

typedef struct
{
    float current_error[L_AND_R];

    float prev_error_t_minus_1[L_AND_R];
    float prev_error_t_minus_2[L_AND_R];

    float cmltv_error[L_AND_R];
} Pid_Calc_Values_t;

typedef struct
{
    float kp;
    float ki;
    float kd;
} Pid_Consts_t;

void update_encoder_and_pid_speed_control(void);
