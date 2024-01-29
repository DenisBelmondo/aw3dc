#include <raylib.h>
#include <stdio.h>
#include "psprite.h"

void psprite_pistol_tick(struct PSprite *psprite, double delta) {
    (void)psprite;
    (void)delta;

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        puts("bang");
    }
}

void psprite_pistol_draw(struct PSprite *psprite, double delta) {
    (void)psprite;
    (void)delta;
}
