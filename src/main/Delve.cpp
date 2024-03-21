#include "Delve.h"
#include "../../rogue_engine/headers/ResourceManager.h"
#include "../../rogue_engine/headers/rogue_engine.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <glm/geometric.hpp>
#include <iostream>

Delve::Delve()
    // init list
    : _screenWidth(1024), _screenHeight(768), _time(0),
      _gameState(GameState::PLAY), _maxFPS(60.0) {
  _camera.init(_screenWidth, _screenHeight);
}

Delve::~Delve() {}

void Delve::run() {
  initSystems();
  gameLoop();
}

// ensure the SDL systems we need are ready for use.
void Delve::initSystems() {
  // initialize game engine
  rogue_engine::init();

  // create SDL window
  _window.create("Game Engine", _screenWidth, _screenHeight, 0);

  initShaders();
  _levels.push_back(new Level("../src/dungeon_gen/textLevel.txt"));

  _spriteBatch.init();
  _fpsLimiter.init(_maxFPS);
}

void Delve::initShaders() {
  // stitch shaders and their attribues together
  _glslProgram.compileShaders("../Shaders/colorShading.vert",
                              "../Shaders/colorShading.frag");
  _glslProgram.addAttribute("vertexPosition");
  _glslProgram.addAttribute("vertexColor");
  _glslProgram.addAttribute("vertexUV");
  _glslProgram.linkShaders();
}

// declares what should happen while the game runs
void Delve::gameLoop() {
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
    if (frameCounter == 10000) {
      std::cout << _fps << std::endl;
      frameCounter = 0;
    }
  }
};

// Monitors input in events in SDL,
void Delve::processInput() {
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
      break;
    // track the position of the mouse in SDL.
    case SDL_MOUSEMOTION:
      _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
      break;
    case SDL_KEYDOWN:
      _inputManager.pressKey(evnt.key.keysym.sym);
      break;
    case SDL_KEYUP:
      _inputManager.releaseKey(evnt.key.keysym.sym);
      break;
    case SDL_MOUSEBUTTONDOWN:
      _inputManager.pressKey(evnt.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      _inputManager.pressKey(evnt.button.button);
      break;
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
  if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
    glm::vec2 mouseCoords = _inputManager.getMouseCoords();
    mouseCoords = _camera.convertScreenToWorld(mouseCoords);

    glm::vec2 playerPosition(0.0f);
    glm::vec2 direction = mouseCoords - playerPosition;
    direction = glm::normalize(direction);
  }
}

void Delve::drawGame() {
  // set clear depth
  glClearDepth(1.0);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // enable shader processing class
  _glslProgram.use();

  // use texture unit 0
  glActiveTexture(GL_TEXTURE0);
  // bind texture to texture unit 0
  GLint textureLocation = _glslProgram.getUniformLocation("mySampler");
  // tell shader that texture is in texture unit 0
  glUniform1i(textureLocation, 0);

  // get the location of the player and center cameraMatrix there
  GLint playerLocation = _glslProgram.getUniformLocation("P");
  glm::mat4 cameraMatrix = _camera.getCameraMatrix();

  glUniformMatrix4fv(playerLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  // start putting the _spriteBatch together
  _spriteBatch.begin();

  // sprite attributes
  glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
  glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
  // sprite textures
  static rogue_engine::GLTexture texture =
      rogue_engine::ResourceManager::getTexture(
          "/home/matosade/Projects/Game_Dev/delve/assets/"
          "0x72_DungeonTilesetII_v1.6/frames/wizzard_m_idle_anim_f0.png");

  // initialize a color for the sprite
  rogue_engine::Color color;

  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;

  // draw sprites
  _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

  // zip up the batch and chuck it at the GPU
  _spriteBatch.end();
  _spriteBatch.renderBatch();

  // clean up
  glBindTexture(GL_TEXTURE_2D, 0);
  _glslProgram.unUse();

  // swap bugger before drawing again
  _window.swapBuffer();
};
