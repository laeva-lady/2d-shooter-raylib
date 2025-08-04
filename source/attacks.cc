#include "../headers/attacks.hpp"

#include "../headers/bullets.hpp"
#include "../headers/game.hpp"
#include "../headers/player.hpp"

#include <print>
#include <raylib.h>

AttacksType next_enum(AttacksType current) {
  return static_cast<AttacksType>((static_cast<int>(current) + 1) %
                                  static_cast<int>(AttacksType::Next));
}

std::string Attacks::get_current_atk_t() {
  switch (currentAttack) {
  case AttacksType::Bullets:
    return "Bullets";
  case AttacksType::Wave:
    return "Wave";
  default:
    return "ERR: Invalid Attack Name";
  }
}

void Attacks::Update(Game &game) {
  if (IsKeyPressed(KEY_E)) {
    currentAttack = next_enum(currentAttack);
  }

  if (IsKeyDown(KEY_SPACE)) {
    switch (currentAttack) {
    case AttacksType::Bullets:
      if (game.mbullets->time_since_last_bullet >= 0.25) {
        std::println("[DEBUG] | Attacks :: Bullets");
        game.mbullets->SpawnBullet(*game.player, *game.cam);
        game.mbullets->time_since_last_bullet = 0.0f;
      }
      break;
    case AttacksType::Wave:
      std::println("[DEBUG] | Attacks :: Wave");

      game.waveAtk->Create(game.player->get_pos(), 500.0f, 300.0f, 50.f, BROWN);
      break;

    default:
      std::println("[ERR] | INVALID ATK NAME");
    }
  }
}
