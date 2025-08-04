#include "../headers/map.hpp"

#include <fstream>

Map::Map(std::string map_filepath) { obstacles = LoadMap(map_filepath); }

void Map::Draw(Camera2D camera) {
  BeginMode2D(camera);
  for (const auto &obs : obstacles) {
    DrawRectangleRec(obs.rect, DARKGRAY);
  }
  EndMode2D();
}

std::vector<Obstacle> Map::LoadMap(const std::string &filename) {
  std::vector<Obstacle> obstacles;
  std::ifstream file(filename);
  std::string line;
  int row = 0;

  while (std::getline(file, line)) {
    for (int col = 0; col < line.length(); ++col) {
      if (line[col] == 'x') {
        Obstacle obs;
        obs.rect = {col * TILE_SIZE + offset.x, // x in world space
                    row * TILE_SIZE + offset.y, // y in world space
                    TILE_SIZE, TILE_SIZE};
        obstacles.push_back(obs);
      }
    }
    row++;
  }

  return obstacles;
}