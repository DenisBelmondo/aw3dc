#include <raylib.h>
#include <stddef.h>
#include "audio.h"
#include "ent.h"
#include "monsters.h"
#include "player.h"
#include "res_man.h"
#include "tile_map.h"
#include "world.h"

// engine
const double TICK_RATE = 1.0 / 30.0;

// game

// world
TileMap tile_map = {
    (int[]){
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    },
    20, // pitch
};

World world;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1152, 720, "Wolf3D");

    int err = 0;

    err = res_man_init();

    if (err) {
        goto close_window;
    }

    err = audio_init();

    if (err) {
        goto close_window;
    }

    play_midi_from_file("music/MAJMIN.wlf", true);

    world_init(&world);

    world.tile_map = &tile_map;

    //
    // world init
    //

    Ent player;
    player.tick = player_tick;
    player.draw = NULL;
    player.rad = 0.5F;
    player.xform.yaw = 0;
    player.xform.pos = (Vector2){5, 5};

    size_t player_handle = world_spawn_ent(&world, player);
    world_attach_camera(&world, player_handle);

    Ent guard;

    guard.tick = guard_tick;
    guard.draw = guard_draw;
    guard.xform.yaw = 0;
    guard.xform.pos = (Vector2){4, 4};
    world_spawn_ent(&world, guard);

    PSprite pistol;

    pistol.tick = psprite_pistol_tick;
    pistol.draw = psprite_pistol_draw;
    world.psprite = pistol;

    //
    // game loop
    //

    double previous = GetTime();
    double lag = 0.0;

    while (!WindowShouldClose()) {
        double current = GetTime();
        double elapsed = current - previous;

        previous = current;
        lag += elapsed;

        while (lag >= TICK_RATE) {
            world_tick(&world, TICK_RATE);
            lag -= TICK_RATE;
        }

        ClearBackground(BLACK);

        BeginDrawing();
            world_draw(&world, elapsed);
        EndDrawing();
    }

    audio_shutdown();

close_window:
    CloseWindow();
    world_shutdown(&world);

    return 0;
}
