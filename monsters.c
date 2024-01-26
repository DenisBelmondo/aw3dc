#include <stdio.h>
#include "drawer.h"
#include "ent.h"
#include "monsters.h"
#include "res_man.h"

const Thinker THINKER_GUARD = {
    guard_think,
};

const Drawer DRAWER_GUARD = {
    guard_draw,
};

void guard_init(Ent *ent) {
    ent->thinker = THINKER_GUARD;
    ent->drawer = DRAWER_GUARD;
    ent->rad = 0.5F;
}

void guard_think(void *data, double delta) {
    (void)data;
    (void)delta;
}

void guard_draw(Camera3D cam, void *data, double delta) {
    Ent *self = (Ent *)data;

    (void)delta;

    DrawBillboard(cam, RES_MAN_TEX[RES_MAN_IMG_GUARD], (Vector3){self->xform.pos.x, 0, self->xform.pos.y}, 1, WHITE);
}
