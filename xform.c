#include "xform.h"

Vector2 get_dir(XForm transform) {
    return (Vector2){cosf(transform.yaw), sinf(transform.yaw)};
}
