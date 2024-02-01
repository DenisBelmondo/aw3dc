#include <math.h>
#include "dda.h"

int dda(
    void *grid_1d,
    size_t grid_cell_size_in_bytes,
    size_t grid_row_width,
    float origin_x,
    float origin_y,
    float dir_x,
    float dir_y,
    DDAState *out_dda_state)
{
    DDAState initial_dda_state = {0};

    *out_dda_state = initial_dda_state;

    out_dda_state->map_x = (int)origin_x;
    out_dda_state->map_y = (int)origin_y;

    out_dda_state->delta_dist_x = (dir_x == 0) ? 1e30 : fabs(1 / dir_x);
    out_dda_state->delta_dist_y = (dir_y == 0) ? 1e30 : fabs(1 / dir_y);

    //calculate step and initial sideDist
    if (dir_x < 0) {
        out_dda_state->step_x = -1;
        out_dda_state->side_dist_x = (origin_x - out_dda_state->map_x) * out_dda_state->delta_dist_x;
    } else {
        out_dda_state->step_x = 1;
        out_dda_state->side_dist_x = (out_dda_state->map_x + 1.0 - origin_x) * out_dda_state->delta_dist_x;
    }

    if (dir_y < 0) {
        out_dda_state->step_y = -1;
        out_dda_state->side_dist_y = (origin_y - out_dda_state->map_y) * out_dda_state->delta_dist_y;
    } else {
        out_dda_state->step_y = 1;
        out_dda_state->side_dist_y = (out_dda_state->map_y + 1.0 - origin_y) * out_dda_state->delta_dist_y;
    }

    // perform DDA
    while (!out_dda_state->hit_something) {
        // jump to next map square, either in x-direction, or in y-direction
        if (out_dda_state->side_dist_x < out_dda_state->side_dist_y) {
            out_dda_state->side_dist_x += out_dda_state->delta_dist_x;
            out_dda_state->map_x += out_dda_state->step_x;
            out_dda_state->side = 0;
        } else {
            out_dda_state->side_dist_y += out_dda_state->delta_dist_y;
            out_dda_state->map_y += out_dda_state->step_y;
            out_dda_state->side = 1;
        }

        // Check if ray has hit a wall
        if (((unsigned char *)grid_1d)[(out_dda_state->map_y * grid_row_width + out_dda_state->map_x) * grid_cell_size_in_bytes] > 0) {
            out_dda_state->hit_something = 1;
        }
    }

    if (out_dda_state->hit_something) {
        if (out_dda_state->side == 0) {
            out_dda_state->perp_wall_dist = (out_dda_state->side_dist_x - out_dda_state->delta_dist_x);
        } else {
            out_dda_state->perp_wall_dist = (out_dda_state->side_dist_y - out_dda_state->delta_dist_y);
        }

        out_dda_state->intersection_x = origin_x + out_dda_state->perp_wall_dist * dir_x;
        out_dda_state->intersection_y = origin_y + out_dda_state->perp_wall_dist * dir_y;

        return 0;
    }

    return 0;
}
