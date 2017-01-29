#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/Shader.h"

int main() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "Lord of Vikings", NULL, NULL);

    if (!window) {
        std::cout << "Window error, :(" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    Shader myShader;
    myShader.loadFiles("shader.vert", "shader.frag");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
