#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <raymath.h>

typedef struct TileMap {
    int *tiles;
    int pitch;
} TileMap;

int tile_map_get(TileMap tile_map, int x, int y);
int tile_map_cast(TileMap tile_map, Vector2 origin, Vector2 dir, Vector2 *out_intersection, int *out_face);

#endif /* TILE_MAP_H */
