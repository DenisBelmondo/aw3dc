#ifndef PSPRITE_H
#define PSPRITE_H

#include "ent.h"

typedef struct PSprite {
    Ent *owner;
    void (*tick)(struct PSprite*, double);
    void (*draw)(struct PSprite*, double);
} PSprite;

void psprite_pistol_tick(struct PSprite*, double);
void psprite_pistol_draw(struct PSprite*, double);

#endif /* PSPRITE_H */
