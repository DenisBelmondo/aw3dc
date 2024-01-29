#include <raylib.h>
#include <stdio.h>
#include "psprite.h"
#include "res_man.h"

void psprite_pistol_tick(struct PSprite *psprite, double delta) {
    (void)psprite;
    (void)delta;

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        puts("bang");
    }
}

void psprite_pistol_draw(struct PSprite *psprite, double delta) {
    static const int gun_frame_width = 64;
    static const int gun_frame_height = 64;
    static const int gun_frame_idx = 0;

    float gun_texture_scale = (float)GetRenderHeight() / RES_MAN_IMG[RES_MAN_IMG_WALTHER].height;

    (void)psprite;
    (void)delta;

    DrawTexturePro(
        RES_MAN_TEX[RES_MAN_IMG_WALTHER],
        (Rectangle){gun_frame_idx * gun_frame_width, 0, gun_frame_width, gun_frame_height},
        (Rectangle){(float)GetRenderWidth() / 2 - gun_frame_width * gun_texture_scale / 2.0F,
        0,
        GetRenderHeight(),
        GetRenderHeight()},
        (Vector2){0},
        0,
        WHITE);
}
