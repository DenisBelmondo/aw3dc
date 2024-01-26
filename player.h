#ifndef PLAYER_H
#define PLAYER_H

#include "ent.h"

extern const EntClass ENT_CLASS_PLAYER;

void player_tick(Ent *ent, double delta);

#endif /* PLAYER_H */
