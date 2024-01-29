#ifndef PLAYER_H
#define PLAYER_H

#include "ent.h"
#include "thinker.h"

extern const Thinker THINKER_PLAYER;

void player_tick(Ent *ent, double delta);

#endif /* PLAYER_H */
