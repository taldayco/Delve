#include "../headers/MainGame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

MainGame::MainGame() {
  _window = nullptr;
  _screenWidth = 1024;
  _screenHeight = 768;
  _gameState = GameState::PLAY;
}

MainGame::~MainGame() {}

void MainGame::run() {
  initSystems();
  gameLoop();
}

void MainGame::initSystems() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  _window =
      SDL_CreateWindow("Delve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}

void MainGame::gameLoop() {
  while (_gameState != GameState::EXIT) {
    processInput();
  }
};
void MainGame::processInput() {
  SDL_Event evnt;

  while (SDL_PollEvent(&evnt) == true) {
    switch (evnt.type) {
    case SDL_QUIT:
      _gameState = GameState::EXIT;

    case SDL_MOUSEMOTION:
      std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
      break;
    }
  };
};
