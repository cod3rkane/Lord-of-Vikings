#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "util/ProjectionMatrix.h"
#include "util/Shader.h"
#include "GlModel.h"
#include "legacy/Camera.h"
#include "legacy/Entity.h"
#include <SOIL.h>

ProjectionMatrix projectionMatrix = {.fov = 45.0f, .nearPlane = 0.1f, .farPlane = 100.0f};
GLFWmonitor* monitor;
const GLFWvidmode* mode;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(mode->width, mode->height, "Lord of Vikings", NULL, NULL);
    printf("Window width: %d window height: %d \n", mode->width, mode->height);

    if (!window) {
        std::cout << "Window error, :(" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, mode->width, mode->height);
    glMatrixMode(GL_MODELVIEW);

    // OpenGL Code

    projectionMatrix.aspectRatio = (GLfloat)mode->width / mode->height;

    Shader myShader;
    myShader.loadFiles("assets/shaders/shader.vert", "assets/shaders/shader.frag");

    GlModel glModel;
    glModel.storeShader(&myShader);

    const GLfloat vertex_buffer_data[] = {
            -1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0
    };

    const GLuint indices[] = {
            0, 2, 1,
            2, 3, 1
    };

    const GLfloat colorData[] = {
            0.2f, 0.3f, 1.0f,
            1.0f, 0.8f, 0.8f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f
    };

    const GLfloat textureData[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f
    };

    Entity entity(0, vec3(0, 0, 0), 0, 0, 0, 0.1f);

    glModel.storePositionData(vertex_buffer_data, sizeof(vertex_buffer_data));
    glModel.storeColorData(colorData, sizeof(colorData));
    glModel.storeTextureData(textureData, sizeof(textureData));
    glModel.storeIndicesData(indices, sizeof(indices));
    glModel.setViewMatrix(camera.GetViewMatrix());
    glModel.setProjectionMatrix(&projectionMatrix);
    glModel.setEntity(&entity);

    int imageW, imageH;
    unsigned char *wallTexture = SOIL_load_image("assets/images/ninja/idle.PNG", &imageW, &imageH, 0, SOIL_LOAD_RGBA);
    glModel.textureImage(wallTexture, imageW, imageH, GL_RGBA);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glModel.renderElements();
        entity.increasePosition(0.0f, 0.0f, 0.0f);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
