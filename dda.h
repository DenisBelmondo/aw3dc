#ifndef DDA_H
#define DDA_H

#include <stddef.h>

typedef struct DDAState {
    /** length of ray from current position to next x or y-side (x coordinate) */
    float side_dist_x;
    /** length of ray from current position to next x or y-side (y coordinate) */
    float side_dist_y;
    /* length of ray from one x or y-side to next x or y-side (x coordinate) */
    float delta_dist_x;
    /* length of ray from one x or y-side to next x or y-side (y coordinate) */
    float delta_dist_y;
    /** the length of the perpendicular of the point of intersection */
    float perp_wall_dist;
    /** the point of intersection (x coordinate) */
    float intersection_x;
    /** the point of intersection (y coordinate) */
    float intersection_y;
    /** which box of the map we're in (x coordinate) */
    int map_x;
    /** which box of the map we're in (y coordinate) */
    int map_y;
    /** what direction to step in x or y-direction (either +1 or -1) (x coordinate) */
    int step_x;
    /** what direction to step in x or y-direction (either +1 or -1) (y coordinate) */
    int step_y;
    /** did the ray hit something? */
    unsigned char hit_something;
    /** 0 = East/West cell boundary intersection, 1 = North/South */
    unsigned char side;
} DDAState;

int dda(
    void *grid_1d,
    size_t grid_cell_size_in_bytes,
    size_t grid_row_width,
    float origin_x,
    float origin_y,
    float dir_x,
    float dir_y,
    DDAState *out_dda_state);

#endif /* DDA_H */
