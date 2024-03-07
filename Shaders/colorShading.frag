#version 130
// Fragment shader operates on each pixel in a given polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// Below is the 4-component float vector that gets output to the screen
// for each pixel
out vec4 color;

// Global variable for time (per frame)
uniform float time;
uniform sampler2D mySampler;

void main() {
  vec4 textureColor = texture(mySampler, fragmentUV);
  color = textureColor * fragmentColor;

//  make wakky colors using time and shaders ;P
//  color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
//               fragmentColor.g * (cos(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5,
//               fragmentColor.b * (cos(fragmentPosition.x * 3.0 + time) + 1.0) * 0.5,
//               fragmentColor.a);
}
