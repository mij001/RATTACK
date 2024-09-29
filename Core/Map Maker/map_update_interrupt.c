#include "map_update_interrupt.h"

void map_update()
{
    uint16_t wall_info = 0;
    uint16_t cell_mobility_relative = GL_current_cell_mobility;

    Position v = get_position();

    write_map_cell(v.x, v.y, extract_cell_mobility_absolute(cell_mobility_relative, v.angle) | CELL_ACCESSED_MASK);
}

uint8_t extract_cell_mobility_absolute(uint8_t relative_mob, uint16_t angle)
{
    /*  format 0b[0-0-0-0 <270_available>-<180_available>-<90_available>-<0_available>] */

    uint8_t back_mobile = 1;
    uint8_t left_mobile = (LEFT_MOBILE_MASK & relative_mob) >> 2;
    uint8_t forward_mobile = (RIGHT_MOBILE_MASK & relative_mob) >> 1;
    uint8_t right_mobile = (FORWARD_MOBILE_MASK & relative_mob);

    switch (angle)
    {
    case 0:
    {
        return (back_mobile << 2) | (left_mobile << 1) | (forward_mobile << 0) | (right_mobile << 3);
    }
    case 90:
    {
        return (back_mobile << 3) | (left_mobile << 2) | (forward_mobile << 1) | (right_mobile << 0);
    }
    case 180:
    {
        return (back_mobile << 0) | (left_mobile << 3) | (forward_mobile << 2) | (right_mobile << 1);
    }
    case 270:
    {
        return (back_mobile << 1) | (left_mobile << 0) | (forward_mobile << 3) | (right_mobile << 2);
    }
    }
}