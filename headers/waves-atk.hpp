#pragma once

#include "../headers/attacks.hpp"
#include "camera.hpp"
#include "raylib.h"
#include <vector>

struct WaveATK {
  Vector2 position; // Center of the wave
  float radius;     // Current radius
  float max_radius;  // The radius at which the wave disappears
  float speed;      // How fast the radius expands
  float wave_size;  // Size of the wave
  Color color;      // Wave color
};

class WaveATKs {
  std::vector<WaveATK> waves;

  float time_since_last_spawn = 0;
  float firing_rate = 0.50;

public:
  WaveATKs() {}

  void Create(Vector2 position, float maxRadius, float speed, float wave_size, Color color) {
    if (time_since_last_spawn >= firing_rate) {
      waves.push_back({position, 0.0f, maxRadius, speed, wave_size, color});
      time_since_last_spawn = 0;
    }
  }

  void Update() {
    time_since_last_spawn += GetFrameTime();
    if (time_since_last_spawn > BIG_number)
      time_since_last_spawn = 0;

    for (auto it = waves.begin(); it != waves.end();) {
      it->radius += it->speed * GetFrameTime();
      if (it->radius >= it->max_radius) {
        it = waves.erase(it);
      } else {
        ++it;
      }
    }
  }

  void Draw(CameraM &cam) {
    BeginMode2D(cam.get_cam());
    for (const auto &wave : waves) {
      float alpha = 1.0f - (wave.radius / wave.max_radius);
      DrawRing(wave.position, wave.radius - wave.wave_size, wave.radius, 0, 360, 0,
               Fade(wave.color, alpha));
    }
    EndMode2D();
  }
};
