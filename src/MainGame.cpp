#include "../headers/MainGame.h" // Assuming this is the correct path for MainGame.h
#include <GL/glew.h>
#include <iostream>
#include <string>
#define GLEW_STATIC

// Check for fatal errors:
// if they exist: print the error
// and quit SDL.
void fatalError(std::string errorString) {
  std::cout << errorString << std::endl;
  std::cout << "Enter any key to quit...";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
}

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

// ensure the SDL systems we need are ready for use.
void MainGame::initSystems() {
  SDL_Init(SDL_INIT_EVERYTHING);
  // set openGL up
  _window =
      SDL_CreateWindow("Delve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

  // more errorchecking
  if (_window == nullptr) {
    fatalError("SDL Window Could Not Be Created");
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (glContext == nullptr) {
    fatalError("SDL_GL Context could not be created.");
  }
  GLenum error = glewInit();
  if (error != GLEW_OK) {
    fatalError("Coul Not Init Glew");
  }
}

// Declares what should happen in the game.
void MainGame::gameLoop() {
  while (_gameState != GameState::EXIT) {
    processInput();
    drawGame();
  }
};

// Monitors input in events in SDL,
void MainGame::processInput() {
  SDL_Event evnt;

  // while the user is making inputs:
  while (SDL_PollEvent(&evnt) == true) {
    // figure out what kind of event it is
    switch (evnt.type) {
    // if the event is SDL_QUIT,
    // return 0 from GameState
    case SDL_QUIT:
      _gameState = GameState::EXIT;

    // track the position of the mouse in SDL.
    case SDL_MOUSEMOTION:
      std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
      break;
    }
  };
};

void MainGame::drawGame() { glClearDepth(1.0); };
