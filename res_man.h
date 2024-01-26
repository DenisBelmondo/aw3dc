#ifndef RES_MAN_H
#define RES_MAN_H

#include <raylib.h>

typedef enum ResManImages {
    RES_MAN_IMG_GUARD,
    RES_MAN_NUM_IMG,
} ResManImages;

extern const char *RES_MAN_IMG_PATHS[];
extern Image RES_MAN_IMG[];
extern Texture RES_MAN_TEX[];

int res_man_init(void);
int res_man_shutdown(void);

#endif /* RES_MAN_H */
