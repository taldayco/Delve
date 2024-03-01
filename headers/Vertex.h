#pragma once
#include <GL/glew.h>

// you want your vertex struct to be a mulitple of 4 bytes
struct Vertex {
  struct Position {
    float x;
    float y;
  } position;

  struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
  } color;
};
