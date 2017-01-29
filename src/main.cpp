#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"

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

    Shader myShader;
    myShader.loadFiles("shader.vert", "shader.frag");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0f);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
