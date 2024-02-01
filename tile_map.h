#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <raylib.h>
#include <raymath.h>

typedef struct TileMap {
    int *tiles;
    int pitch;
} TileMap;

int tile_map_get(TileMap tile_map, int x, int y);
// void tile_map_get_rect(TileMap tile_map, Rectangle rect, int *out_tiles, int out_num_tiles);
bool tile_map_cast(TileMap tile_map, Vector2 origin, Vector2 dir, Vector2 *out_intersection, unsigned char *out_face);

#endif /* TILE_MAP_H */
