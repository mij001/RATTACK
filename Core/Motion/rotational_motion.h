#pragma once

#include <stdint.h>

#include "config.h"
#include "global_vars.h"
#include "helper.h"
#include "ir_secondary.h"

void slow_speed_rotational_motion_pid(int32_t angle);
void fast_speed_rotational_motion_pid(int32_t angle);
