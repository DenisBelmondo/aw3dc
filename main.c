#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "audio.h"
#include "ent.h"
#include "player.h"
#include "tile_map.h"

// engine
static const double TICK_RATE = 1.0 / 30.0;
static Model wall_model;
static Image wall_image;
static Texture wall_texture;
static Material wall_material;
static Image gun_image;
static Texture gun_texture;
static Image guard_image;
static Texture guard_texture;
static const Color COLOR_CEILING = {57, 57, 57, 255};
static const Color COLOR_FLOOR = {115, 115, 115, 255};

// game

static const EntClass ENT_CLASS_GUARD = {
    NULL,
};

// world
static TileMap tile_map = {
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

static Ent *head;

// render
static Camera3D cam = {
    {0},                // pos
    {1, 0, 0},          // target
    {0, 1, 0},          // up
    90.0F,              // fovy
    CAMERA_PERSPECTIVE, // projection
};

void tick(double delta) {
    for (Ent *ent = head; ent; ent = ent->next) {
        if (ent->cls && ent->cls->tick) {
            ent->cls->tick(ent, delta);
        }
    }
}

void shutdown(void) {
    Ent *ent = head;

    if (!ent) {
        return;
    }

    while (true) {
        Ent *next = ent->next;

        free(ent);

        if (!next) {
            break;
        }

        ent = ent->next;
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(640, 480, "Wolf3D");

    int err = 0;

    err = audio_init();

    if (err) {
        goto close_window;
    }

    err = play_midi_from_file("music/Jewel_Master_-_Now_You_Are_Gone.mid", true);

    if (err) {
        goto close_window;
    }

    wall_model = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    wall_image = LoadImage("0.png");
    ImageFlipVertical(&wall_image);
    wall_texture = LoadTextureFromImage(wall_image);
    wall_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall_texture;
    gun_image = LoadImage("walther.png");
    gun_texture = LoadTextureFromImage(gun_image);
    guard_image = LoadImage("pguard_s_1.png");
    guard_texture = LoadTextureFromImage(guard_image);

    //
    // world init
    //

    head = calloc(1, sizeof(Ent));
    head->cls = &ENT_CLASS_PLAYER;
    head->rad = 0.5F;
    head->xform.pos = (Vector2){5, 5};
    head->tile_map = &tile_map;

    Ent *guard = calloc(1, sizeof(Ent));
    guard->cls = &ENT_CLASS_GUARD;
    guard->rad = 0.5F;
    guard->xform.pos = (Vector2){4, 4};
    guard->tile_map = &tile_map;
    head->next = guard;

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
            tick(TICK_RATE);
            lag -= TICK_RATE;
        }

        ClearBackground(BLACK);

        Vector2 ent_dir = get_dir(head->xform);

        cam.position = (Vector3){head->xform.pos.x, 0, head->xform.pos.y};
        cam.target = Vector3Add(cam.position, (Vector3){ent_dir.x, 0, ent_dir.y});

        BeginDrawing();
            DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight() / 2, COLOR_CEILING);
            DrawRectangle(0, GetRenderHeight() / 2, GetRenderWidth(), GetRenderHeight() / 2, COLOR_FLOOR);
            BeginMode3D(cam);
                for (int y = 0; y < tile_map.pitch; y++) {
                    for (int x = 0; x < tile_map.pitch; x++) {
                        if (tile_map_get(tile_map, x, y)) {
                            // DrawCubeV((Vector3){x + 0.5F, 0, y + 0.5F}, (Vector3){1, 1, 1}, DARKBLUE);
                            DrawModel(wall_model, (Vector3){x + 0.5F, 0, y + 0.5F}, 1, WHITE);
                        }
                    }
                }

                for (Ent *ent = head; ent; ent = ent->next) {
                    if (ent->cls == &ENT_CLASS_GUARD) {
                        DrawBillboard(cam, guard_texture, (Vector3){ent->xform.pos.x, 0, ent->xform.pos.y}, 1, WHITE);
                    }
                }
            EndMode3D();
            float gun_texture_scale = (float)GetRenderHeight() / gun_image.height;
            static const int gun_frame_width = 64;
            static const int gun_frame_height = 64;
            static const int gun_frame_idx = 0;
            DrawTexturePro(gun_texture, (Rectangle){gun_frame_idx * gun_frame_width, 0, gun_frame_width, gun_frame_height}, (Rectangle){(float)GetRenderWidth() / 2 - gun_frame_width * gun_texture_scale / 2.0F, 0, GetRenderHeight(), GetRenderHeight()}, (Vector2){0}, 0, WHITE);
        EndDrawing();
    }

    UnloadMaterial(wall_material);
    UnloadTexture(wall_texture);
    UnloadImage(wall_image);
    UnloadTexture(guard_texture);
    UnloadImage(guard_image);
    UnloadTexture(gun_texture);
    UnloadImage(gun_image);

    audio_shutdown();

close_window:
    CloseWindow();
    shutdown();

    return 0;
}
