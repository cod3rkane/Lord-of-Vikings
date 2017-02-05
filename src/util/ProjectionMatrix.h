#ifndef LOV_PROJECTIO_MATRIX_H
#define LOV_PROJECTIO_MATRIX_H

#include <GL/glew.h>

typedef struct ProjectionMatrix {
    float fov;
    float nearPlane;
    float farPlane;
    GLfloat aspectRatio;
} ProjectionMatrix;

#endif // LOV_PROJECTIO_MATRIX_H
