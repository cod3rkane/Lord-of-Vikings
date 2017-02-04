cmake_minimum_required(VERSION 3.6)
project(Lov)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/util/Shader.cpp src/util/Shader.h)
add_executable(Lov ${SOURCE_FILES})

include_directories(/src/local/includes/SOIL)
link_directories(/src/local/lib)

include_directories(${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(Lov ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARY} SOIL)

