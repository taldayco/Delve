#version 130

// Fragment shader operates on each pixel in a given polygon

in vec4 fragmentColor;

// Below is the 3 component float vector that gets output to the screen
// for each pixel
out vec4 color;

// Global variable for time (per frame)
uniform float time;

void main() {
    color = fragmentColor + vec4(1.0 * (cos(time) + 1.0) * 0.5,
                                1.0 * (cos(time + 2.0)+1.0) * 0.5,
                                1.0 * (sin(time + 1.0)+1.0) * 0.5,
                                0.0);
}

