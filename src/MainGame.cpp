#include "../headers/MainGame.h"
#include "../rogue_engine/headers/ResourceManager.h"
#include "../rogue_engine/headers/rogue_engine.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

MainGame::MainGame()
    // init list
    : _screenWidth(1024), _screenHeight(768), _time(0),
      _gameState(GameState::PLAY), _maxFPS(60.0) {
  _camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {}

void MainGame::run() {
  initSystems();
  gameLoop();
}

// ensure the SDL systems we need are ready for use.
void MainGame::initSystems() {

  rogue_engine::init();

  _window.create("Game Engine", _screenWidth, _screenHeight, 0);

  initShaders();

  _spriteBatch.init();
  _fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
  _colorProgram.compileShaders("../Shaders/colorShading.vert",
                               "../Shaders/colorShading.frag");
  _colorProgram.addAttribute("vertexPosition");
  _colorProgram.addAttribute("vertexColor");
  _colorProgram.addAttribute("vertexUV");
  _colorProgram.linkShaders();
}

// Declares what should happen in the game.
void MainGame::gameLoop() {
  while (_gameState != GameState::EXIT) {

    _fpsLimiter.begin();

    processInput();
    _time += 0.01;

    _camera.update();

    drawGame();
    _fps = _fpsLimiter.end();

    // print once every ten frames
    static int frameCounter = 0;
    frameCounter++;
    if (frameCounter == 10) {
      std::cout << _fps << std::endl;
      frameCounter = 0;
    }
  }
};

// Monitors input in events in SDL,
void MainGame::processInput() {
  SDL_Event evnt;

  const float CAMERA_SPEED = 2.0f;
  const float SCALE_SPEED = 0.1f;

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
      // std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
      break;
    case SDL_KEYDOWN:
      _inputManager.pressKey(evnt.key.keysym.sym);
      break;
    case SDL_KEYUP:
      _inputManager.releaseKey(evnt.key.keysym.sym);
    }
  };
  if (_inputManager.isKeyPressed(SDLK_w)) {
    _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
  }
  if (_inputManager.isKeyPressed(SDLK_s)) {
    _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
  }
  if (_inputManager.isKeyPressed(SDLK_a)) {
    _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
  }
  if (_inputManager.isKeyPressed(SDLK_d)) {
    _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
  }
  if (_inputManager.isKeyPressed(SDLK_q)) {
    _camera.setScale(_camera.getScale() + SCALE_SPEED);
  }
  if (_inputManager.isKeyPressed(SDLK_e)) {
    _camera.setScale(_camera.getScale() - SCALE_SPEED);
  }
}

void MainGame::drawGame() {
  // make sure the screen is clear before drawing
  glClearDepth(1.0);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable shader
  _colorProgram.use();

  // use texture unit 0
  glActiveTexture(GL_TEXTURE0);
  // bind texture to texture unit 0
  GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
  // tell shader that texture is in texture unit 0
  glUniform1i(textureLocation, 0);

  // set the camera matrix
  GLint pLocation = _colorProgram.getUniformLocation("P");
  glm::mat4 cameraMatrix = _camera.getCameraMatrix();

  glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  _spriteBatch.begin();

  glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
  glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

  static rogue_engine::GLTexture texture =
      rogue_engine::ResourceManager::getTexture(
          "/home/matosade/Projects/Game_Dev/delve/assets/"
          "0x72_DungeonTilesetII_v1.6/frames/wizzard_m_idle_anim_f0.png");
  rogue_engine::Color color;
  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;

  for (int i = 0; i < 2; i++) {
    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
    _spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f,
                      color);
  }
  _spriteBatch.end();

  _spriteBatch.renderBatch();

  // unbind
  glBindTexture(GL_TEXTURE_2D, 0);
  _colorProgram.unUse();

  // swap our buffer before drawing
  _window.swapBuffer();
};
