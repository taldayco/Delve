#version 130
//fragment shader operaes on each pixel in a given polygon

in vec4 fragmentColor;

//Below is the 3 component float vector that gets output to the screen
//for each pixel
out vec4 color;

void main() {
    //hardcode color to red
    color = fragmentColor;
}
