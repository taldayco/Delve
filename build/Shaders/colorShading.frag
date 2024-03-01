#version 130
//fragment shader operaes on each pixel in a given polygon

//Below is the 3 component float vector that gets output to the screen
//for each pixel
out vec3 color;

void main() {
    //hardcode color to red
    color = vec3(1.0, 0.0, 0.0);
}
