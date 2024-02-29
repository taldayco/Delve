#version 130

in vec2 vertexPosition;

void main() {
    gl_position.xy = vertexPosition;
}
