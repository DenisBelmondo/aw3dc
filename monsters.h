#ifndef MONSTERS_H
#define MONSTERS_H

#include <raylib.h>
#include "ent.h"
#include "thinker.h"

extern const Thinker THINKER_GUARD;

void guard_init(Ent*);
void guard_think(void*, double);
void guard_draw(Camera3D, void*, double);

#endif /* MONSTERS_H */
