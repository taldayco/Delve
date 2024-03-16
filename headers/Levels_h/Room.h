#pragma once
#include "../../rogue_engine/headers/Rect.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

class Room : public rogue_engine::Rect {
public:
  Room();
  Room(const Rect &other);

  void set(const Room &other);

  // Spatial logic methods
  int minWidth() const;
  int maxWidth() const;
  int minHeight() const;
  int maxHeight() const;
  bool setSize();
  bool forceSize(int w, int h);
  bool setSizeWithLimit(int w, int h);

  // Connection logic methods
  bool canConnect(const glm::ivec2 &p) const;
  bool canConnect(int direction) const;
  bool canConnect(const Room &other) const;
  bool addNeighbor(const Room &other);
  bool connect(const Room &room);
  void clearConnections();

  // Painter logic methods (for SDL2 and OpenGL)
  void paint(); // Implement this method for rendering with OpenGL

private:
  std::vector<Room *> neighbors;
  std::unordered_map<Room *, Door *> connected;
  int distance;
  int price = 1;
};
