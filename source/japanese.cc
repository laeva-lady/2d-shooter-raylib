#include "../headers/japanese.hpp"

#include <cstring>
#include <stdlib.h>
#include <string>

static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount,
                                      int *codepointResultCount) {
  int codepointsClearCount = codepointCount;
  int *codepointsClear = (int *)RL_CALLOC(codepointCount, sizeof(int));
  memcpy(codepointsClear, codepoints, codepointCount * sizeof(int));

  // Remove duplicates
  for (int i = 0; i < codepointsClearCount; i++) {
    for (int j = i + 1; j < codepointsClearCount; j++) {
      if (codepointsClear[i] == codepointsClear[j]) {
        for (int k = j; k < codepointsClearCount; k++)
          codepointsClear[k] = codepointsClear[k + 1];

        codepointsClearCount--;
        j--;
      }
    }
  }

  // Resize array to number of resulting codepoints (lower or equal to input)
  RL_REALLOC(codepointsClear, codepointsClearCount * sizeof(int));

  *codepointResultCount = codepointsClearCount;
  return codepointsClear;
}

Font CJK::load_cjk_font(std::string text, std::string font_path) {
  // Get codepoints from text
  int codepointCount = 0;
  int *codepoints = LoadCodepoints(text.c_str(), &codepointCount);

  // Removed duplicate codepoints to generate smaller font atlas
  int codepointsNoDuplicatesCount = 0;
  int *codepointsNoDuplicates = CodepointRemoveDuplicates(
      codepoints, codepointCount, &codepointsNoDuplicatesCount);
  UnloadCodepoints(codepoints);

  // Load font containing all the provided codepoints
  Font font = LoadFontEx(font_path.c_str(), 36, codepointsNoDuplicates,
                         codepointsNoDuplicatesCount);

  // Unload codepoints, atlas has already been generated
  UnloadCodepoints(codepointsNoDuplicates);

  return font;
}
