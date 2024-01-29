#include <stddef.h>
#include "res_man.h"

const char *RES_MAN_IMG_PATHS[] = {
    "0.png",
    "pguard_s_1.png",
};

Image RES_MAN_IMG[RES_MAN_NUM_IMG];
Texture RES_MAN_TEX[RES_MAN_NUM_IMG];
Shader RES_MAN_WALL_SHADER;
Model RES_MAN_WALL_MODEL;

int res_man_init(void) {
    for (size_t i = 0; i < RES_MAN_NUM_IMG; i++) {
        RES_MAN_IMG[i] = LoadImage(RES_MAN_IMG_PATHS[i]);
        RES_MAN_TEX[i] = LoadTextureFromImage(RES_MAN_IMG[i]);
    }

    Mesh wall_mesh = GenMeshCube(1, 1, 1);

    for (int i = 0; i < wall_mesh.vertexCount * 2; i++) {
        if (i & 1) {
            wall_mesh.texcoords[i] *= -1;
        }
    }

    UpdateMeshBuffer(wall_mesh, 1, wall_mesh.texcoords, wall_mesh.vertexCount * 2 * sizeof(float), 0);

    RES_MAN_WALL_SHADER = LoadShader("wall.vert", "wall.frag");
    RES_MAN_WALL_MODEL = LoadModelFromMesh(wall_mesh);
    RES_MAN_WALL_MODEL.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = RES_MAN_TEX[RES_MAN_IMG_WALL_0];
    RES_MAN_WALL_MODEL.materials[0].shader = RES_MAN_WALL_SHADER;

    return 0;
}

int res_man_shutdown(void) {
    UnloadModel(RES_MAN_WALL_MODEL);
    UnloadShader(RES_MAN_WALL_SHADER);

    for (size_t i = 0; i < RES_MAN_NUM_IMG; i++) {
        UnloadTexture(RES_MAN_TEX[i]);
        UnloadImage(RES_MAN_IMG[i]);
    }

    return 0;
}
