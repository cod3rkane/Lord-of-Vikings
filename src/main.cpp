#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"
#include "GlModel.h"
#include <SOIL/SOIL.h>

int main() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(1280, 720, "Lord of Vikings", NULL, NULL);

    if (!window) {
        std::cout << "Window error, :(" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 1280, 720);
    glMatrixMode(GL_MODELVIEW);

    // OpenGL Code

    Shader myShader;
    myShader.loadFiles("assets/shaders/shader.vert", "assets/shaders/shader.frag");

    GlModel glModel;
    glModel.storeShader(&myShader);

    const GLfloat vertex_buffer_data[] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
    };

    const GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    const GLfloat colorData[] = {
            0.2f, 0.3f, 1.0f,
            1.0f, 0.8f, 0.8f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f
    };

    const GLfloat textureData[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
    };


    glModel.storePositionData(vertex_buffer_data, sizeof(vertex_buffer_data));
    glModel.storeColorData(colorData, sizeof(colorData));
    glModel.storeTextureData(textureData, sizeof(textureData));
    glModel.storeIndicesData(indices, sizeof(indices));

    int imageW, imageH;
    unsigned char *wallTexture = SOIL_load_image("assets/images/ninja/idle.PNG", &imageW, &imageH, 0, SOIL_LOAD_RGBA);
    glModel.textureImage(wallTexture, imageW, imageH, GL_RGBA);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glModel.renderElements();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
