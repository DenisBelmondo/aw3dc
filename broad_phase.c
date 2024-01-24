#include "broad_phase.h"

typedef struct BroadPhaseState {
    int size;
} BroadPhaseState;

int get_hash_code(int x, int y) {
    int hash = (x * 92837111) ^ (y * 689287499);
    return hash;
}

// int broad_phase_insert(Vector2 pos, float radius) {
//     int min_y = pos.y - radius;
//     int max_y = pos.y + radius;
//     int min_x = pos.x - radius;
//     int max_x = pos.x + radius;

//     for (int y = min_y; y < max_y; y++) {
//         for (int x = min_x; x < max_x; x++) {
//             int hash = get_hash_code(x, y);
//         }
//     }
// }

int broad_phase_insert_point(int x, int y) {
    int hash = get_hash_code(x, y);
    return hash;
}
