#pragma once

#include "bullets.hpp"
#include "player.hpp"
#include <print>
#include <raylib.h>

enum class AttacksType {
  Bullets,
  Wave,
  Next,
};

AttacksType next_enum(AttacksType current);

class Attacks {
  AttacksType currentAttack;

public:
  Attacks() { currentAttack = AttacksType::Bullets; }

  std::string get_current_atk_t() {
    switch (currentAttack) {
    case AttacksType::Bullets:
      return "Bullets";
    case AttacksType::Wave:
      return "Wave";
    default:
      return "ERR: Invalid Attack Name";
    }
  }

  void Update(Bullets &bts, Player &p, CameraM &c) {
    if (IsKeyPressed(KEY_E)) {
      currentAttack = next_enum(currentAttack);
    }

    if (IsKeyDown(KEY_SPACE)) {
      switch (currentAttack) {
      case AttacksType::Bullets:
        if (IsKeyDown(KEY_SPACE) && bts.time_since_last_bullet >= 0.25) {
          std::println("[DEBUG] | Attacks :: Bullets");
          bts.SpawnBullet(p, c);
          bts.time_since_last_bullet = 0.0f;
        }
        break;
      case AttacksType::Wave:
        if (IsKeyDown(KEY_SPACE)) {
          std::println("[DEBUG] | Attacks :: Wave");
        }
        break;
      default:
          std::println("[ERR] | INVALID ATK NAME");
      }
    }
  }
};
