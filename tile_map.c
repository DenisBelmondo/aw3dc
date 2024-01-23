#include "tile_map.h"

int tile_map_get(TileMap tile_map, int x, int y) {
    return tile_map.tiles[y * tile_map.pitch + x];
}
