#ifndef ENT_H
#define ENT_H

#include <raylib.h>
#include "xform.h"

typedef struct Ent {
    void (*tick)(struct Ent*, double);
    void (*draw)(Camera3D cam, struct Ent*, double);
    const struct World *world;
    XForm xform;
    float rad;
} Ent;

#endif /* ENT_H */
