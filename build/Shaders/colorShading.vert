#version 130
//vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats.
in vec2 vertexPosition;

void main() {
    //set the x,y position on the screen
    gl_Position.xy = vertexPosition;
    //the z position is 0 (2D)
    gl_Position.z = 0.0;

    //indicate the coordinates are normalized
    gl_Position.w = 1.0;
}
