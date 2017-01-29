#include "Shader.h"

void Shader::loadFiles(const GLchar *vertexPath, const GLchar *fragmentPath) {
    std::cout << "Hello World!" << std::endl;

    std::ifstream shaderStream(vertexPath, std::ios::binary), fragmentStream(fragmentPath, std::ios::binary);
    std::stringstream vShaderString, fShaderString;

    vShaderString << shaderStream.rdbuf();
    fShaderString << fragmentStream.rdbuf();

    shaderStream.close();
    fragmentStream.close();

    std::string vertexCode, fragmentCode;

    vertexCode = vShaderString.str();
    fragmentCode = fShaderString.str();

    std::cout << vertexCode << std::endl;
}

void Shader::useProgram() {
    glUseProgram(this->programID);
}

Shader::~Shader() {
    glDeleteProgram(this->programID); // @todo return code dumped. fix later.
}
