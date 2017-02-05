#include "GlModel.h"

void GlModel::storeColorData(const void *colorData, int length) {
    this->colorData = colorData;
    this->colorDataLength = length;
}

void GlModel::storePositionData(const void *positionData, int length) {
    this->positionData = positionData;
    this->positionDataLength = length;
}

void GlModel::storeTextureData(const void *textureData, int length) {
    this->textureData = textureData;
    this->textureDataLength = length;
}

void GlModel::storeShader(Shader *shader) {
    this->shader = shader;
}

GlModel::GlModel() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(3, this->VBO);

    this->positionBufferHandle = this->VBO[0];
    this->colorBufferHandle = this->VBO[1];
    this->textureBufferHandle = this->VBO[2];
}

void GlModel::setup() {
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->positionDataLength, this->positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->colorDataLength, this->colorData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Vertices
    glEnableVertexAttribArray(1); // Color

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
}

void GlModel::render() {
    this->setup();

    this->shader->useProgram();

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, (this->positionDataLength / sizeof(GLfloat)) / 3);
    glDisable(GL_DEPTH_TEST);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

GlModel::~GlModel() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(3, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}