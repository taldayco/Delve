#include "../header/Player.h"

// Constructor. Initializes position to 0.
Player::Player() {
  _x = 0;
  _y = 0;
  _z = 0;
}

// Initializes the player with properties
void Player::init(int level, int health, int attack, int defense,
                  int experience) {
  _level = level;
  _health = health;
  _attack = attack;
  _experience = experience;
}

// sets the position of the player
void Player::setPosition(int x, int y, int z) {
  _x = x;
  _y = y;
  _z = z;
}

// Gets the position of the player using reference variables
void Player::getPosition(int &x, int &y, int &z) {
  x = _x;
  y = _y;
  z = _z;
}
