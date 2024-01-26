#include "ent.h"
#include "player.h"
#include "util.h"

const float COL_MARGIN = 0.01;

const Thinker THINKER_PLAYER = {
    player_tick, // tick
};

void player_tick(void *data, double delta) {
    Ent *self = (Ent *)data;

    (void)delta;

    float forward_axis = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    float strafe_axis = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float look_axis = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

    forward_axis /= 5.0F;
    strafe_axis /= 5.0F;
    look_axis /= 7.5F;

    Vector2 ent_dir = get_dir(self->xform);
    Vector2 strafe_dir = perp2(ent_dir);

    self->xform.yaw += look_axis;

    Vector2 pos_prev = self->xform.pos;
    Vector2 pos_new = pos_prev;

    pos_new = Vector2Add(pos_new, Vector2Scale(ent_dir, forward_axis));
    pos_new = Vector2Add(pos_new, Vector2Scale(strafe_dir, strafe_axis));

    Vector2 move_vec = Vector2Subtract(pos_new, pos_prev);

    self->xform.pos.x = pos_new.x;
    if (tile_map_get(*self->tile_map, self->xform.pos.x, self->xform.pos.y)) {
        if (move_vec.x > 0) {
            self->xform.pos.x = (int)self->xform.pos.x - COL_MARGIN;
        } else if (move_vec.x < 0) {
            self->xform.pos.x = (int)self->xform.pos.x + 1 + COL_MARGIN;
        }
    }
    self->xform.pos.y = pos_new.y;
    if (tile_map_get(*self->tile_map, self->xform.pos.x, self->xform.pos.y)) {
        if (move_vec.y > 0) {
            self->xform.pos.y = (int)self->xform.pos.y - COL_MARGIN;
        } else if (move_vec.y < 0) {
            self->xform.pos.y = (int)self->xform.pos.y + 1 + COL_MARGIN;
        }
    }
}
