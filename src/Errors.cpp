#include "../headers/Errors.h"
#include <SDL/SDL.h>
#include <iostream>

// prints error and exits game
void fatalError(std::string errorString) {
  std::cout << errorString << std::endl;
  std::cout << "Enter any key to quit...";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
}
