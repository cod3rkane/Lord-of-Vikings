#include <iostream>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <gdk/gdk.h>
// #include <GLFW/glfw3.h>
#include "util/ProjectionMatrix.h"
#include "util/Shader.h"
#include "GlModel.h"
#include "legacy/Camera.h"
#include "legacy/Entity.h"

int main(int argc, char* argv[]) {
    // Initialize GTK+
    gdk_init(&argc, &argv);
    return EXIT_SUCCESS;
}
