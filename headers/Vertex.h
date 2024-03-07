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

struct UV {
  float u;
  float v;
};

// you want your vertex struct to be a mulitple of 4 bytes
struct Vertex {
  Position position;

  // 4 bytes for r g b a
  Color color;

  // uv texture coordinates
  UV uv;

  void setPosition(float x, float y) {
    position.x = x;
    position.y = y;
  }

  void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  };

  void setUV(float u, float v) {
    uv.u = u;
    uv.v = v;
  }
};
