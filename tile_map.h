#ifndef TILE_MAP_H
#define TILE_MAP_H

typedef struct TileMap {
    int *tiles;
    int pitch;
} TileMap;

int tile_map_get(TileMap tile_map, int x, int y);

#endif /* TILE_MAP_H */
