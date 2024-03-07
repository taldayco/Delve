#pragma once
#include "../rogue_engine/headers/GLSLProgram.h"
#include "../rogue_engine/headers/GLTexture.h"
#include "../rogue_engine/headers/Sprite.h"
#include "../rogue_engine/headers/Window.h"
#include "../rogue_engine/headers/rogue_engine.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>

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
  void calculateFPS();

  rogue_engine::Window _window;
  int _screenWidth;
  int _screenHeight;
  GameState _gameState;

  std::vector<rogue_engine::Sprite *> _sprites;
  rogue_engine::GLSLProgram _colorProgram;

  float _fps;
  float _maxFPS;
  float _frameTime;

  float _time;
};
