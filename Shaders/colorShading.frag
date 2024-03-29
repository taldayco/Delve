#version 130
// Fragment shader operates on each pixel in a given polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// Below is the 4-component float vector that gets output to the screen
// for each pixel
out vec4 color;

// Global variable for time (per frame)
uniform sampler2D mySampler;

void main() {
    vec4 textureColor = texture(mySampler, fragmentUV);

    color = fragmentColor * textureColor;
}
