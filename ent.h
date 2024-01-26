#ifndef ENT_H
#define ENT_H

#include <raylib.h>
#include "drawer.h"
#include "thinker.h"
#include "tile_map.h"
#include "xform.h"

struct Ent;
typedef struct Ent Ent;

struct Ent {
    struct Ent *next;
    const TileMap *tile_map;
    Texture *texture;
    int frame;
    XForm xform;
    float rad;
    int broad_phase_handle;
    Thinker thinker;
    Drawer drawer;
};

#endif /* ENT_H */
