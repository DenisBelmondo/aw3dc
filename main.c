#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "audio.h"
#include "ent.h"
#include "tile_map.h"
#include "util.h"

void player_tick(Ent*, double);

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
static const EntClass ENT_CLASS_PLAYER = {
    player_tick, // tick
};

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
        1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1,
        1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
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

void player_tick(Ent *ent, double delta) {
    (void)delta;

    float forward_axis = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    float strafe_axis = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float look_axis = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

    forward_axis /= 5.0F;
    strafe_axis /= 5.0F;
    look_axis /= 7.5F;

    Vector2 ent_dir = ent_get_dir(*ent);
    Vector2 strafe_dir = perp2(ent_dir);

    ent->yaw += look_axis;

    Vector2 pos_prev = ent->pos;
    Vector2 pos_new = ent->pos;

    pos_new = Vector2Add(pos_new, Vector2Scale(ent_dir, forward_axis));
    pos_new = Vector2Add(pos_new, Vector2Scale(strafe_dir, strafe_axis));

    int tile = tile_map_get(*ent->tile_map, pos_new.x, pos_prev.y);

    if (tile) {
        pos_new.x = pos_prev.x;
    }

    tile = tile_map_get(*ent->tile_map, pos_prev.x, pos_new.y);

    if (tile) {
        pos_new.y = pos_prev.y;
    }

    ent->pos = pos_new;
}

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

    err = play_midi_from_file("LOTW_Dungeon1.mid", true);

    if (err) {
        goto close_window;
    }

    wall_model = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    wall_image = LoadImage("0.png");
    ImageFlipVertical(&wall_image);
    wall_texture = LoadTextureFromImage(wall_image);
    wall_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall_texture;
    gun_image = LoadImage("valta-0.png");
    gun_texture = LoadTextureFromImage(gun_image);
    guard_image = LoadImage("pguard_s_1.png");
    guard_texture = LoadTextureFromImage(guard_image);

    //
    // world init
    //

    head = calloc(1, sizeof(Ent));
    head->cls = &ENT_CLASS_PLAYER;
    head->rad = 0.5F;
    head->pos = (Vector2){5, 5};
    head->tile_map = &tile_map;

    Ent *guard = calloc(1, sizeof(Ent));
    guard->cls = &ENT_CLASS_GUARD;
    guard->rad = 0.5F;
    guard->pos = (Vector2){4, 4};
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

        Vector2 ent_dir = ent_get_dir(*head);

        cam.position = (Vector3){head->pos.x, 0, head->pos.y};
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
                        DrawBillboard(cam, guard_texture, (Vector3){ent->pos.x, 0, ent->pos.y}, 1, WHITE);
                    }
                }
            EndMode3D();
            float gun_texture_scale = (float)GetRenderHeight() / gun_image.height;
            DrawTexturePro(gun_texture, (Rectangle){0, 0, 64, 64}, (Rectangle){(float)GetRenderWidth() / 2 - gun_image.width * gun_texture_scale / 2.0F, 0, GetRenderHeight(), GetRenderHeight()}, (Vector2){0}, 0, WHITE);
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
