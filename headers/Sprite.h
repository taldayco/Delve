#pragma once
#include "../headers/GLTexture.h"
#include <GL/glew.h>
#include <string>

// A 2d quad that can be rendered to the scree
class Sprite {
public:
  Sprite();
  ~Sprite();

  void init(float x, float y, float width, float height,
            std::string texturePath);

  void draw();

private:
  int _x;
  int _y;
  int _width;
  int _height;
  // vertex buffer object ID
  GLuint _vboID;
  GLTexture _texture;
};
