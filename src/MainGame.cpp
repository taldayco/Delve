#include "../headers/MainGame.h" // Assuming this is the correct path for MainGame.h
#include "../headers/Errors.h"
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
  _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
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
  // instead of drawing and clearing on the same Window,
  // Prevents flickering by seperating each process into its own buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // sets default color when glClear is called
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  initShaders();
}

void MainGame::initShaders() {
  _colorProgram.compileShaders("../Shaders/colorShading.vert",
                               "../Shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.linkShaders();
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

void MainGame::drawGame() {
  // make sure the screen is clear before drawing
  glClearDepth(1.0);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _colorProgram.use();

  _sprite.draw();

  _colorProgram.unUse();

  // swap our buffer before drawing
  SDL_GL_SwapWindow(_window);
};
