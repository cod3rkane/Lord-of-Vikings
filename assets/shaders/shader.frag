#version 330 core
uniform vec4 frameBufferColor;
out vec4 color;

void main() {
    color = frameBufferColor;
}
