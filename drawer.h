#ifndef DRAWER_H
#define DRAWER_H

#include <raylib.h>

typedef struct Drawer {
    void (*draw)(Camera3D, void*, double);
} Drawer;

#endif /* DRAWER_H */
