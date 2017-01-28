#include "Shader.h"

void Shader::loadFiles() {
    std::cout << "Hello World!" << std::endl;
}

void Shader::useProgram() {
    glUseProgram(this->programID);
}

Shader::~Shader() {
}
