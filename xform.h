#ifndef XFORM_H
#define XFORM_H

#include <raymath.h>

typedef struct XForm {
    Vector2 pos;
    float yaw;
} XForm;

Vector2 get_dir(XForm transform);

#endif /* XFORM_H */
