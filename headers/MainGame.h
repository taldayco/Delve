#pragma once
#include "../headers/GLSLProgram.h"
#include "../headers/GLTexture.h"
#include "../headers/Sprite.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

enum class GameState { PLAY, EXIT };

class MainGame {
public:
  MainGame();
  ~MainGame();

  void run();

private:
  void initSystems();
  void initShaders();
  void gameLoop();
  void processInput();
  void drawGame();

  SDL_Window *_window;
  int _screenWidth;
  int _screenHeight;

  GameState _gameState;

  Sprite _sprite;

  GLSLProgram _colorProgram;

  GLTexture _playerTexture;

  float _time;
};
