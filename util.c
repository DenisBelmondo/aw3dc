#include "util.h"

Vector2 perp2(Vector2 v) {
    return (Vector2){-v.y, v.x};
}
