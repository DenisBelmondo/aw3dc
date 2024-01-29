#ifndef MONSTERS_H
#define MONSTERS_H

#include <raylib.h>
#include "ent.h"
#include "thinker.h"

extern const Thinker THINKER_GUARD;

void guard_init(Ent*);
void guard_tick(Ent*, double);
void guard_draw(Camera3D, Ent*, double);

#endif /* MONSTERS_H */
