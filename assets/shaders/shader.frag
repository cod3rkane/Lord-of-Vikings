#version 330 core

in vec3 outColor;
in vec2 textureCoord;
uniform sampler2D ourTexture;

out vec4 color;

void main() {
    color = texture(ourTexture, vec2(textureCoord.x, 1.0f - textureCoord.y));
}
