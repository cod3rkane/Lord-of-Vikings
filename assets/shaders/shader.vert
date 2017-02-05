#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureData;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 outColor;
out vec2 textureCoord;

void main() {
    gl_Position = projection * view * transform * vec4(vertexPosition, 1.0f);
    outColor = color;
    textureCoord = vec2(textureData.x, 1.0f - textureData.y);
}
