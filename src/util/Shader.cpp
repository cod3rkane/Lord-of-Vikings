#include "Shader.h"

void Shader::loadFiles(const GLchar *vertexPath, const GLchar *fragmentPath) {
    std::ifstream shaderStream(vertexPath, std::ios::binary), fragmentStream(fragmentPath, std::ios::binary);
    std::stringstream vShaderString, fShaderString;

    vShaderString << shaderStream.rdbuf();
    fShaderString << fragmentStream.rdbuf();

    shaderStream.close();
    fragmentStream.close();

    std::string vertexCode = vShaderString.str();
    std::string fragmentCode = fShaderString.str();

    const GLchar *vCode = vertexCode.c_str();
    const GLchar *fCode = fragmentCode.c_str();

    // Compile Shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);

    // check erros
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infolog << std::endl;
    }

    // Compile Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);

    // check errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infolog << std::endl;
    }

    // Shader Program
    this->programID = glCreateProgram();
    if (this->programID == 0) {
        std::cout << "ERROR::SHADER::PROGRAMID::ON_CREATE_PROGRAMID" << std::endl;
    }

    glAttachShader(this->programID, vertex);
    glAttachShader(this->programID, fragment);
    glLinkProgram(this->programID);

    // check linking errors
    glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->programID, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAMID::LINKING_FAILED" << std::endl << infolog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::useProgram() {
    glUseProgram(this->programID);
}

Shader::~Shader() {
    glDeleteProgram(this->programID); // @todo return code dumped. fix later.
}
