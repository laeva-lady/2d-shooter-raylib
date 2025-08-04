#include "../headers/bullets.hpp"
#include "../headers/camera.hpp"
#include "../headers/collisions.h"
#include <print>
#include <raylib.h>
#include <raymath.h>

void Bullets::SpawnBullet(Player &player, CameraM &cam) {
  float angle = player.get_angle(cam);
  Vector2 bullet_direction = {cos(angle), sin(angle)};
  Vector2 player_velocity = player.get_velocity();
  float bullet_speed = 10.0f; // Base bullet speed

  Vector2 initial_bullet_velocity =
      Vector2Add(Vector2Scale(bullet_direction, bullet_speed), player_velocity);
  Bullet nb = {player.get_pos(), initial_bullet_velocity, 100, 5.0f, 0.5};
  bullets.push_back(nb);
}

void Bullets::Update(Player &player, const Map &map, CameraM &cam) {
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    SpawnBullet(player, cam);
  }

  for (int i = bullets.size() - 1; i >= 0; i--) {
    bullets[i]._pos.x += bullets[i]._velocity.x * bullets[i]._speed;
    bullets[i]._pos.y += bullets[i]._velocity.y * bullets[i]._speed;

    // check for collisions with map obstacles
    for (const auto &obstacle : map.get_obstacles()) {
      if (is_circle_colliding_with_rect(bullets[i]._pos, bullets[i]._radius,
                                        obstacle.rect)) {
        bullets.erase(bullets.begin() + i);
        break;
      }
    }
  }

  for (auto b : bullets) {
    std::println("[DEBUG]\t\tBULLET.POS : {{ {:.2f}, {:.2f} }}", b._pos.x,
                 b._pos.y);
  }
}

void Bullets::Draw(CameraM &cam) {
  BeginMode2D(cam.get_cam());
  for (const auto &bullet : bullets) {
    DrawCircleV(bullet._pos, bullet._radius, MAROON);
  }
  EndMode2D();
}
