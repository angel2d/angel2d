#pragma once

#include "../Util/StringUtil.h"

const bool RegisterFont(String filename, int pointSize, String nickname);
const bool UnRegisterFont(String nickname);

//both of these functions return the 2d point representing the bottom-most, right-most point
// where you could safely start drawing and not overwrite them
Vector2 DrawGameText(String text, String nickname, int pixelX, int pixelY, float angle=0.0f);
Vector2 GetTextExtents(String text, String nickname);