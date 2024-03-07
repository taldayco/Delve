#include "../headers/ImageLoader.h"
#include "../headers/Errors.h"
#include "../headers/IOManager.h"
#include "../headers/picoPNG.h"
#include <vector>

GLTexture ImageLoader::loadPNG(std::string filePath) {
  // create Texture and initialize values to 0
  GLTexture texture = {};

  // input data to decodePNG, which we load from a file
  std::vector<unsigned char> in;
  // Output of data from decodePNG, which is pixel data for the texture
  std::vector<unsigned char> out;

  unsigned long width, height;

  // read in the image file contents to buffer
  if (IOManager::readFileToBuffer(filePath, in) == false) {
    fatalError("Failed to load PNG to buffer!");
  }

  // decode .png to an array of pixels
  int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
  if (errorCode != 0) {
    fatalError("decodePNG failed with error: " + std::to_string(errorCode));
  }
  // gen openGL texture object
  glGenTextures(1, &(texture.id));

  glBindTexture(GL_TEXTURE_2D, texture.id);
  // upload pixels to the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, &(out[0]));

  // some texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);

  // unbind texture
  glBindTexture(GL_TEXTURE, 0);

  texture.width = width;
  texture.height = height;

  return texture;
};
