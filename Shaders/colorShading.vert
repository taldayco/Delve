#version 130
//vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats.
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main() {
    //set the x,y position on the screen
    gl_Position.xy = vertexPosition;
    //the z position is 0 (2D)
    gl_Position.z = 0.0;

    //indicate the coordinates are normalized
    gl_Position.w = 1.0;

    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;

    fragmentUV = vertexUV;

    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
