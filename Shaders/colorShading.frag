#version 130

// Fragment shader operates on each pixel in a given polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;

// Below is the 3 component float vector that gets output to the screen
// for each pixel
out vec4 color;

// Global variable for time (per frame)
uniform float time;

void main() {
    color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
                  fragmentColor.g * (cos(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5,
                  fragmentColor.b * (cos(fragmentPosition.x * 3.0 + time) + 1.0) * 0.5,
                  fragmentColor.a);

        }
