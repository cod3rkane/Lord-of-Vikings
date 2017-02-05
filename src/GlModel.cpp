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

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, heigth, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GlModel::render() {
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->setup();

    this->shader->useProgram();

    if (this->texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(this->shader->programID, "ourTexture"), 0);
    }

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, (this->positionDataLength / sizeof(GLfloat)) / 3);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_DEPTH);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

void GlModel::renderElements() {
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->setup();

    this->shader->useProgram();

    if (this->texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(this->shader->programID, "ourTexture"), 0);
    }

    this->storeUniformMatrixLocation4fv(
            this->getUniformLocation("transform"),
            this->createTransformationMatrix(
                    this->entity->getPosition(),
                    this->entity->getRotX(),
                    this->entity->getRotY(),
                    this->entity->getRotZ(),
                    this->entity->getScale()
            )
    );

    this->storeUniformMatrixLocation4fv(
            this->getUniformLocation("view"),
            this->viewMatrix
    );

    this->storeUniformMatrixLocation4fv(
            this->getUniformLocation("projection"),
            glm::perspective(
                    this->projectionMatrix->fov,
                    this->projectionMatrix->aspectRatio,
                    this->projectionMatrix->nearPlane,
                    this->projectionMatrix->farPlane
            )
    );

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, (this->indicesDataLength / sizeof(GLuint)), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_DEPTH);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

GlModel::~GlModel() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(3, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void GlModel::setProjectionMatrix(ProjectionMatrix *projectionMatrix) {
    GlModel::projectionMatrix = projectionMatrix;
}

void GlModel::storeUniformMatrixLocation4fv(GLint location, glm::mat4 value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLint GlModel::getUniformLocation(const char *uniform) {
    return glGetUniformLocation(this->shader->programID, uniform);
}

const glm::mat4 &GlModel::getViewMatrix() const {
    return viewMatrix;
}

void GlModel::setViewMatrix(const glm::mat4 &viewMatrix) {
    GlModel::viewMatrix = viewMatrix;
}

void GlModel::setEntity(Entity *entity) {
    GlModel::entity = entity;
}

glm::mat4 GlModel::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale) {
    glm::mat4 matrix;
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
    return matrix;
}
