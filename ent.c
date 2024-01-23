#include "ent.h"

Vector2 ent_get_dir(Ent ent) {
    return (Vector2){cosf(ent.yaw), sinf(ent.yaw)};
}
