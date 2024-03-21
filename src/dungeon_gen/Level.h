#pragma once
#include <string>
#include <vector>

class Level {
public:
  Level(const std::string &filename);
  ~Level();

private:
  // the level is a text file, so levelData is a vector of strings
  std::vector<std::string> _levelData;
};
