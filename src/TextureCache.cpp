#include "../headers/TextureCache.h"
#include "../headers/ImageLoader.h"
#include <iostream>

TextureCache::TextureCache() {}

TextureCache::~TextureCache() {}

GLTexture TextureCache::getTexture(std::string texturePath) {
  // lookup texture and see if its in the map
  auto mit = _textureMap.find(texturePath);

  // check if its not in the map
  if (mit == _textureMap.end()) {
    // load texture
    GLTexture newTexture = ImageLoader::loadPNG(texturePath);

    // insert it into the map
    _textureMap.insert(make_pair(texturePath, newTexture));

    std::cout << "Loaded Texture!\n";

    return newTexture;
  }

  std::cout << "Use Cached Texture!\n";
  return mit->second;
}
