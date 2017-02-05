#ifndef LOV_GLMODEL_H
#define LOV_GLMODEL_H

#include <GL/glew.h>
#include "util/Shader.h"
#include <vector>
#include <glm/ext.hpp>

typedef struct GlModel {
private:
    Shader *shader;
    const void *positionData;
    int positionDataLength;
    const void *colorData;
    int colorDataLength;
    const void *textureData;
    int textureDataLength;
    GLuint positionBufferHandle;
    GLuint colorBufferHandle;
    GLuint textureBufferHandle;

    void setup();
public:
    GLuint VAO;
    GLuint VBO[3];

    GLuint EBO;
    GlModel();
    void storePositionData(const void *positionData, int length);
    void storeColorData(const void *colorData, int length);
    void storeTextureData(const void *textureData, int length);
    void storeShader(Shader *shader);
    void render();
    ~GlModel();
} GlModel;

#endif // LOV_GLMODEL_H