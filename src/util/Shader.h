#ifndef LOV_SHADER_H
#define LOV_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

typedef struct Shader {
    GLuint programID;

    void loadFiles();
    void useProgram();
    ~Shader();
} Shader;

#endif // LOV_SHADER_H
