#pragma once
#include "../headers/GLTexture.h"
#include <string>

// loads images into GLTextures
class ImageLoader {
public:
  static GLTexture loadPNG(std::string filePath);
};
