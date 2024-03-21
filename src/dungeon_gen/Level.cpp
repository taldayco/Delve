#include "Level.h"
#include "../../rogue_engine/headers/Errors.h"
#include <fstream>
#include <iostream>
#include <string>

Level::Level(const std::string &fileName) {
  // open a file input stream
  std::ifstream file;
  file.open(fileName);

  // error cheching
  if (file.fail()) {
    rogue_engine::fatalError("Failed to open" + fileName);
  }

  std::string tmp;
  // parse levelData
  while (std::getline(file, tmp)) {
    _levelData.push_back(tmp);
  }

  // print out levelData
  for (int i = 0; i < _levelData.size(); i++) {
    std::cout << _levelData[i] << std::endl;
  }
};

Level::~Level(){

};
