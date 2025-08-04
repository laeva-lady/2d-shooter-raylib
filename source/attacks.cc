#include "../headers/attacks.hpp"

AttacksType next_enum(AttacksType current) {
  return static_cast<AttacksType>((static_cast<int>(current) + 1) %
                                  static_cast<int>(AttacksType::Next));
}
