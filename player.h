#ifndef PLAYER_H
#define PLAYER_H

#include "thinker.h"

extern const Thinker THINKER_PLAYER;

void player_tick(void *ent, double delta);

#endif /* PLAYER_H */
