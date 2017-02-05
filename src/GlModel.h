#ifndef LOV_GLMODEL_H
#define LOV_GLMODEL_H

#include <GL/glew.h>
#include "util/Shader.h"
#include <SOIL/SOIL.h>

typedef struct GlModel {
private:
    Shader *shader;
    const void *positionData;
    int positionDataLength;
    const void *colorData;
    int colorDataLength;
    const void *textureData;
    int textureDataLength;
    const void *indicesData;
    int indicesDataLength;
    GLuint positionBufferHandle;
    GLuint colorBufferHandle;
    GLuint textureBufferHandle;

    void setup();
public:
    GLuint VAO;
    GLuint VBO[3];
    GLuint EBO;
    GLuint texture;

    GlModel();
    void storePositionData(const void *positionData, int length);
    void storeColorData(const void *colorData, int length);
    void storeTextureData(const void *textureData, int length);
    void storeIndicesData(const void *indicesData, int length);
    void storeShader(Shader *shader);
    void textureImage(unsigned char *image, int width, int heigth, GLenum format);
    void render();
    void renderElements();
    ~GlModel();
} GlModel;

#endif // LOV_GLMODEL_H