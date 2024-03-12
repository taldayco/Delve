#pragma once
#include "../rogue_engine/headers/Camera2D.h"
#include "../rogue_engine/headers/GLSLProgram.h"
#include "../rogue_engine/headers/GLTexture.h"
#include "../rogue_engine/headers/InputManager.h"
#include "../rogue_engine/headers/Sprite.h"
#include "../rogue_engine/headers/SpriteBatch.h"
#include "../rogue_engine/headers/Timing.h"
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

  rogue_engine::Window _window;
  int _screenWidth;
  int _screenHeight;
  GameState _gameState;

  rogue_engine::GLSLProgram _colorProgram;
  rogue_engine::Camera2D _camera;

  rogue_engine::SpriteBatch _spriteBatch;

  rogue_engine::InputManager _inputManager;
  rogue_engine::FpsLimiter _fpsLimiter;

  float _fps;
  float _maxFPS;
  float _time;
};
