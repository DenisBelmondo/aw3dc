#include <stddef.h>
#include "res_man.h"

const char *RES_MAN_IMG_PATHS[] = {
    "pguard_s_1.png",
};

Image RES_MAN_IMG[RES_MAN_NUM_IMG];
Texture RES_MAN_TEX[RES_MAN_NUM_IMG];

int res_man_init(void) {
    for (size_t i = 0; i < RES_MAN_NUM_IMG; i++) {
        RES_MAN_IMG[i] = LoadImage(RES_MAN_IMG_PATHS[i]);
        RES_MAN_TEX[i] = LoadTextureFromImage(RES_MAN_IMG[i]);
    }

    return 0;
}

int res_man_shutdown(void) {
    for (size_t i = 0; i < RES_MAN_NUM_IMG; i++) {
        UnloadTexture(RES_MAN_TEX[i]);
        UnloadImage(RES_MAN_IMG[i]);
    }

    return 0;
}
