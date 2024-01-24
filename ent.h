#ifndef ENT_H
#define ENT_H

#include <raymath.h>
#include "tile_map.h"

struct Ent;
typedef struct Ent Ent;

typedef struct EntClass {
    void (*tick)(Ent*, double);
} EntClass;

struct Ent {
    struct Ent *next;
    const EntClass *cls;
    const TileMap *tile_map;
    Vector2 pos;
    float yaw;
    float rad;
    int broad_phase_handle;
};

Vector2 ent_get_dir(Ent ent);

#endif /* ENT_H */
