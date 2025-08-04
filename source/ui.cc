#include "../headers/ui.hpp"

void UI::Draw(Player *p) {
  std::string text = "年のゲーム";
  int font_size = 42;
  auto font = CJK::load_cjk_font(text, font_size, "assets/NotoSansMonoCJKjp-VF.ttf");

  DrawTextEx(font, text.c_str(), (Vector2){50, 50}, font_size, 0, LIGHTGRAY);

  auto pos = p->get_pos();
  DrawTextEx(GetFontDefault(),
             TextFormat("Player Position: [%.1f, %.1f]", pos.x, pos.y),
             {60, 100}, 20, 2, WHITE);
}
