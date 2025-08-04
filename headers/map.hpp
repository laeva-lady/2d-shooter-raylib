#pragma once

#include "raylib.h"

#include <string>
#include <vector>

const int TILE_SIZE = 50;

struct Obstacle {
  Rectangle rect;
};

class Map {
private:
  const Vector2 offset = {-200, -200};
  Camera *camera;
  std::vector<Obstacle> obstacles;
  std::vector<Obstacle> LoadMap(const std::string &filename);

public:
  Map(std::string map_filepath);

  const std::vector<Obstacle> &get_obstacles() const { return obstacles; }

  void Draw(Camera2D camera);
};
