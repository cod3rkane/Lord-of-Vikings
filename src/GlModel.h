#ifndef LOV_GLMODEL_H
#define LOV_GLMODEL_H

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/ext.hpp>
#include "util/Shader.h"
#include "util/ProjectionMatrix.h"
#include "legacy/Entity.h"

typedef struct GlModel {
private:
    Shader *shader;
    ProjectionMatrix *projectionMatrix;
    Entity *entity;
    glm::mat4 viewMatrix;
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
    void storeUniformMatrixLocation4fv(GLint location, glm::mat4 value);
    void storeShader(Shader *shader);
    void textureImage(unsigned char *image, int width, int heigth, GLenum format);
    GLint getUniformLocation(const char *uniform);
    void render();
    void renderElements();
    void setProjectionMatrix(ProjectionMatrix *projectionMatrix);
    const glm::mat4 &getViewMatrix() const;
    void setViewMatrix(const glm::mat4 &viewMatrix);
    void setEntity(Entity *entity);
    glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);

    ~GlModel();
} GlModel;

#endif // LOV_GLMODEL_H
