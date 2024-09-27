#pragma once

#include <stdint.h>

#include "config.h"
#include "global_vars.h"
#include "helper.h"

int16_t get_ir_difference(void);
uint16_t front_wall_detect(void);
uint8_t get_cell_mobility();