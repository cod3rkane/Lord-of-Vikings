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

void GlModel::storeIndicesData(const void *indicesData, int length) {
    this->indicesData = indicesData;
    this->indicesDataLength = length;
}

GlModel::GlModel() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(3, this->VBO);

    this->positionBufferHandle = this->VBO[0];
    this->colorBufferHandle = this->VBO[1];
    this->textureBufferHandle = this->VBO[2];

    glGenBuffers(1, &this->EBO);
}

void GlModel::setup() {
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->positionDataLength, this->positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->colorDataLength, this->colorData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->textureBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->textureDataLength, this->textureData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesDataLength, this->indicesData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Vertices
    glEnableVertexAttribArray(1); // Color
    glEnableVertexAttribArray(2); // texture

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    glBindBuffer(GL_ARRAY_BUFFER, this->textureBufferHandle);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    glBindVertexArray(0);
}

void GlModel::textureImage(unsigned char *image, int width, int heigth, GLenum format) {
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, heigth, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GlModel::render() {
    this->setup();

    this->shader->useProgram();

    if (this->texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(this->shader->programID, "ourTexture"), 0);
    }

    glBindVertexArray(this->VAO);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, (this->positionDataLength / sizeof(GLfloat)) / 3);
    glDisable(GL_DEPTH_TEST);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GlModel::renderElements() {
    this->setup();

    this->shader->useProgram();

    if (this->texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(this->shader->programID, "ourTexture"), 0);
    }

    glBindVertexArray(this->VAO);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, (this->indicesDataLength / sizeof(GLuint)), GL_UNSIGNED_INT, 0);
    glDisable(GL_DEPTH_TEST);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

GlModel::~GlModel() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(3, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}