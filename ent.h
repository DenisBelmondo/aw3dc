#ifndef ENT_H
#define ENT_H

#include <raylib.h>
#include "tile_map.h"
#include "xform.h"

struct Ent;
typedef struct Ent Ent;

typedef struct EntClass {
    void (*tick)(Ent*, double);
} EntClass;

struct Ent {
    struct Ent *next;
    const EntClass *cls;
    const TileMap *tile_map;
    Texture *texture;
    int frame;
    XForm xform;
    float rad;
    int broad_phase_handle;
};

#endif /* ENT_H */
