cmake_minimum_required(VERSION 3.6)
project(Lov)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

find_package(glfw3 3.2 REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(/usr/local/include/SOIL)
link_directories(/usr/local/lib)

set(SOURCE_FILES
        src/main.cpp
        src/util/Shader.cpp
        src/util/Shader.h
        src/GlModel.cpp
        src/GlModel.h
        src/util/ProjectionMatrix.h
        src/legacy/Camera.cpp
        src/legacy/Camera.h
        src/legacy/Entity.cpp
        src/legacy/Entity.h
        )
add_executable(Lov ${SOURCE_FILES})

include_directories(${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(Lov ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} SOIL
        ${FREETYPE_LIBRARIES} ${GLUT_LIBRARY})

