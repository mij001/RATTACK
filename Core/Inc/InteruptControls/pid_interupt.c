#include <stdint.h>

#include "config.h"
#include "global_vars.h"
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
    
}
