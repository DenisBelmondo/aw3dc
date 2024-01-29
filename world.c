#include <stdlib.h>
#include "res_man.h"
#include "world.h"

const Color COLOR_CEILING = {57, 57, 57, 255};
const Color COLOR_FLOOR = {115, 115, 115, 255};

void world_init(World *world) {
    *world = (World){0};

    world->cam = (Camera3D){
        {0},                // pos
        {1, 0, 0},          // target
        {0, 1, 0},          // up
        90.0F,              // fovy
        CAMERA_PERSPECTIVE, // projection
    };

    world->entities = malloc(sizeof(Ent) * 127);
}

void world_tick(World *world, double delta) {
    for (size_t i = 0; i < world->entities_count; i++) {
        if (world->entities[i].tick) {
            world->entities[i].tick(&world->entities[i], delta);
        }
    }

    if (world->psprite.tick) {
        world->psprite.tick(&world->psprite, delta);
    }
}

void world_draw(World *world, double delta) {
    Ent ent = world->entities[world->camera_followee_handle];
    Vector2 ent_pos = ent.xform.pos;
    Vector2 ent_dir = get_dir(ent.xform);

    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight() / 2, COLOR_CEILING);
    DrawRectangle(0, GetRenderHeight() / 2, GetRenderWidth(), GetRenderHeight() / 2, COLOR_FLOOR);

    BeginMode3D(world->cam);

    world->cam.position = (Vector3){ent_pos.x, 0, ent_pos.y};
    world->cam.target = Vector3Add(world->cam.position, (Vector3){ent_dir.x, 0, ent_dir.y});

    for (int y = 0; y < world->tile_map->pitch; y++) {
        for (int x = 0; x < world->tile_map->pitch; x++) {
            if (tile_map_get(*world->tile_map, x, y)) {
                // DrawCubeV((Vector3){x + 0.5F, 0, y + 0.5F}, (Vector3){1, 1, 1}, DARKBLUE);
                DrawModel(RES_MAN_WALL_MODEL, (Vector3){x + 0.5F, 0, y + 0.5F}, 1, WHITE);
            }
        }
    }

    for (size_t i = 0; i < world->entities_count; i++) {
        if (world->entities[i].draw) {
            world->entities[i].draw(world->cam, &world->entities[i], delta);
        }
    }

    EndMode3D();

    if (world->psprite.draw) {
        world->psprite.draw(&world->psprite, delta);
    }
}

void world_shutdown(World *world) {
    free(world->entities);
}

size_t world_spawn_ent(World *world, Ent ent) {
    size_t handle = world->entities_count;

    ent.world = world;
    world->entities[handle] = ent;
    world->entities_count += 1;

    return handle;
}

void world_attach_camera(World *world, size_t ent_handle) {
    world->camera_followee_handle = ent_handle;
}
