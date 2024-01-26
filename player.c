#include "player.h"
#include "util.h"

static const float COL_MARGIN = 0.01;

const EntClass ENT_CLASS_PLAYER = {
    player_tick, // tick
};

void player_tick(Ent *ent, double delta) {
    (void)delta;

    float forward_axis = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    float strafe_axis = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float look_axis = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

    forward_axis /= 5.0F;
    strafe_axis /= 5.0F;
    look_axis /= 7.5F;

    Vector2 ent_dir = get_dir(ent->xform);
    Vector2 strafe_dir = perp2(ent_dir);

    ent->xform.yaw += look_axis;

    Vector2 pos_prev = ent->xform.pos;
    Vector2 pos_new = pos_prev;

    pos_new = Vector2Add(pos_new, Vector2Scale(ent_dir, forward_axis));
    pos_new = Vector2Add(pos_new, Vector2Scale(strafe_dir, strafe_axis));

    Vector2 move_vec = Vector2Subtract(pos_new, pos_prev);

    ent->xform.pos.x = pos_new.x;
    if (tile_map_get(*ent->tile_map, ent->xform.pos.x, ent->xform.pos.y)) {
        if (move_vec.x > 0) {
            ent->xform.pos.x = (int)ent->xform.pos.x - COL_MARGIN;
        } else if (move_vec.x < 0) {
            ent->xform.pos.x = (int)ent->xform.pos.x + 1 + COL_MARGIN;
        }
    }
    ent->xform.pos.y = pos_new.y;
    if (tile_map_get(*ent->tile_map, ent->xform.pos.x, ent->xform.pos.y)) {
        if (move_vec.y > 0) {
            ent->xform.pos.y = (int)ent->xform.pos.y - COL_MARGIN;
        } else if (move_vec.y < 0) {
            ent->xform.pos.y = (int)ent->xform.pos.y + 1 + COL_MARGIN;
        }
    }
}
