#include <stdint.h>

#include "global_vars.h"

#define MAX_LIM(VAR, MAX_VAL) ((VAR > MAX_VAL) ? MAX_VAL : VAR);
#define MIN_LIM(VAR, MIN_VAL) ((MIN_VAL > VAR) ? MIN_VAL : VAR);


uint32_t get_encoder_val(uint32_t i)
{
    if (i)
    {
        return GL_encoder_values.left_enc;
    }
    else
    {
        return GL_encoder_values.right_enc;
    }
}

////////// TODO : STUB REPAIR
uint32_t get_tick(void){}
