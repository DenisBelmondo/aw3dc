#ifndef WORLD_H
#define WORLD_H

#include "ent.h"
#include "psprite.h"
#include "tile_map.h"

typedef struct World {
    struct Ent *entities;
    TileMap *tile_map;
    PSprite psprite;
    size_t entities_count;
    size_t camera_followee_handle;
    Camera3D cam;
} World;

void world_init(World *world);
void world_tick(World *world, double delta);
void world_draw(World *world, double delta);
size_t world_spawn_ent(World *world, Ent ent);
void world_attach_camera(World *world, size_t ent_handle);
void world_shutdown(World *world);

#endif /* WORLD_H */
