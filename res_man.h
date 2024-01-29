#ifndef RES_MAN_H
#define RES_MAN_H

#include <raylib.h>

typedef enum ResManImages {
    RES_MAN_IMG_WALL_0,
    RES_MAN_IMG_GUARD,
    RES_MAN_IMG_WALTHER,
    RES_MAN_NUM_IMG,
} ResManImages;

extern const char *RES_MAN_IMG_PATHS[];
extern Image RES_MAN_IMG[];
extern Texture RES_MAN_TEX[];

extern Model RES_MAN_WALL_MODEL;

int res_man_init(void);
int res_man_shutdown(void);

#endif /* RES_MAN_H */
