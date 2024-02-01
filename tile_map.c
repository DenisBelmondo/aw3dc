#include <stdbool.h>
#include "dda.h"
#include "tile_map.h"

int tile_map_get(TileMap tile_map, int x, int y) {
    return tile_map.tiles[y * tile_map.pitch + x];
}

bool tile_map_cast(TileMap tile_map, Vector2 origin, Vector2 dir, Vector2 *out_intersection, unsigned char *out_face) {
    DDAState dda_state = {0};

    dda(tile_map.tiles, sizeof(int), tile_map.pitch, origin.x, origin.y, dir.x, dir.y, &dda_state);
    *out_intersection = (Vector2){dda_state.intersection_x, dda_state.intersection_y};
    *out_face = dda_state.side;

    return dda_state.hit_something;
}

// int tile_map_cast(TileMap tile_map, Vector2 origin, Vector2 dir, Vector2 *out_intersection, int *out_face) {
//     //which box of the map we're in
//     int mapX = (int)origin.x;
//     int mapY = (int)origin.y;

//     //length of ray from current position to next x or y-side
//     float sideDistX;
//     float sideDistY;

//     //length of ray from one x or y-side to next x or y-side
//     float deltaDistX = (dir.x == 0) ? 1e30 : fabs(1 / dir.x);
//     float deltaDistY = (dir.y == 0) ? 1e30 : fabs(1 / dir.y);
//     float perpWallDist;

//     //what direction to step in x or y-direction (either +1 or -1)
//     int stepX;
//     int stepY;

//     bool hit = false; //was there a wall hit?
//     int side; //was a NS or a EW wall hit?

//     //calculate step and initial sideDist
//     if (dir.x < 0) {
//         stepX = -1;
//         sideDistX = (origin.x - mapX) * deltaDistX;
//     } else {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - origin.x) * deltaDistX;
//     }

//     if (dir.y < 0) {
//         stepY = -1;
//         sideDistY = (origin.y - mapY) * deltaDistY;
//     } else {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - origin.y) * deltaDistY;
//     }

//     //perform DDA
//     while (!hit) {
//         //jump to next map square, either in x-direction, or in y-direction
//         if (sideDistX < sideDistY) {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//             side = 0;
//         } else {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//             side = 1;
//         }
//         //Check if ray has hit a wall
//         if (tile_map.tiles[mapY * tile_map.pitch + mapX] > 0) {
//             hit = true;
//         }
//     }

//     if (hit) {
//         if (side == 0) {
//             perpWallDist = (sideDistX - deltaDistX);
//         } else {
//             perpWallDist = (sideDistY - deltaDistY);
//         }

//         out_intersection->x = origin.x + perpWallDist * dir.x;
//         out_intersection->y = origin.y + perpWallDist * dir.y;
//         *out_face = side;

//         return tile_map.tiles[mapY * tile_map.pitch + mapX];
//     }

//     return 0;
// }

// void tile_map_get_rect(TileMap tile_map, Rectangle rect, int max_num_out_tiles, int *out_tiles, int out_num_tiles) {
//     for (int y = rect.y; y < rect.y + rect.height; y++) {
//         for (int x = rect.x; x < rect.x + rect.width; x++) {
//             int result = tile_map_get(tile_map, x, y);
//         }
//     }
// }
