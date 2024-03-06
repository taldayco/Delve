#pragma once
#include <GL/glew.h>

struct Position {
  float x;
  float y;
};

struct Color {
  GLubyte r;
  GLubyte g;
  GLubyte b;
  GLubyte a;
};

// you want your vertex struct to be a mulitple of 4 bytes
struct Vertex {
  Position position;

  // 4 bytes for r g b a
  Color color;
};
