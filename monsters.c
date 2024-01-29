#include "ent.h"
#include "monsters.h"
#include "res_man.h"

void guard_init(Ent *ent) {
    ent->tick = guard_tick;
    ent->draw = guard_draw;
    ent->rad = 0.5F;
}

void guard_tick(Ent *ent, double delta) {
    (void)ent;
    (void)delta;
}

void guard_draw(Camera3D cam, Ent *ent, double delta) {
    (void)delta;
    DrawBillboard(cam, RES_MAN_TEX[RES_MAN_IMG_GUARD], (Vector3){ent->xform.pos.x, 0, ent->xform.pos.y}, 1, WHITE);
}
