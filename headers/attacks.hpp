#pragma once

#include <climits>
#include <raylib.h>

class Game;

#include <string>

const float BIG_number = (float)INT_MAX / 2;

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

  std::string get_current_atk_t();

  void Update(Game &game);
};
