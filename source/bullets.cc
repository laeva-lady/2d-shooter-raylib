#include "../headers/bullets.hpp"
#include "../headers/camera.hpp"
#include "../headers/collisions.h"
#include <limits>
#include <print>
#include <raylib.h>
#include <raymath.h>

Bullet new_bullet(Vector2 pos, Vector2 velocity, float damage = 100,
                  float radius = 5, float speed = 500, int bounces_left = 3,
                  Color color = RED) {
  return {pos, velocity, damage, radius, speed, bounces_left, color};
}

void Bullets::SpawnBullet(Player &player, CameraM &cam) {
  float angle = player.get_angle(cam);
  Vector2 bullet_direction = {cos(angle), sin(angle)};

  bullets.push_back(new_bullet(player.get_pos(), bullet_direction));
}

void Bullets::Update(Player &player, const Map &map, CameraM &cam,
                     float deltaTime) {
  if (IsKeyDown(KEY_SPACE)) {
    SpawnBullet(player, cam);
  }

  for (int i = bullets.size() - 1; i >= 0; i--) {
    Vector2 old_pos = bullets[i]._pos;
    Vector2 movement =
        Vector2Scale(bullets[i]._velocity, bullets[i]._speed * deltaTime);

    float travel_dist = Vector2Length(movement);

    Ray ray = {{old_pos.x, old_pos.y, 0},
               {bullets[i]._velocity.x, bullets[i]._velocity.y, 0}};

    RayCollision closest_collision = {0};
    closest_collision.hit = false;
    closest_collision.distance = std::numeric_limits<float>::max();

    for (const auto &obstacle : map.get_obstacles()) {
      Rectangle expanded_rect = {obstacle.rect.x - bullets[i]._radius,
                                 obstacle.rect.y - bullets[i]._radius,
                                 obstacle.rect.width + bullets[i]._radius * 2,
                                 obstacle.rect.height + bullets[i]._radius * 2};

      RayCollision current_collision =
          get_ray_collision_rect(ray, expanded_rect);

      if (current_collision.hit &&
          current_collision.distance < closest_collision.distance) {
        closest_collision = current_collision;
      }
    }

    if (closest_collision.hit && closest_collision.distance <= travel_dist) {
      if (bullets[i]._bounces_left > 0) {
        bullets[i]._bounces_left--;

        // Position the bullet at the exact collision point
        bullets[i]._pos =
            Vector2Add(old_pos, Vector2Scale(bullets[i]._velocity,
                                             closest_collision.distance));

        // Reflect the velocity
        Vector2 normal = {closest_collision.normal.x,
                          closest_collision.normal.y};
        bullets[i]._velocity = Vector2Reflect(bullets[i]._velocity, normal);

        // Calculate remaining travel distance and apply it
        float remaining_dist = travel_dist - closest_collision.distance;
        bullets[i]._pos =
            Vector2Add(bullets[i]._pos,
                       Vector2Scale(bullets[i]._velocity, remaining_dist));

      } else {
        bullets.erase(bullets.begin() + i);
      }
    } else {
      // No collision, move the full distance
      bullets[i]._pos = Vector2Add(old_pos, movement);
    }
  }

  std::println("[DEBUG]\t\tBULLET");
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
