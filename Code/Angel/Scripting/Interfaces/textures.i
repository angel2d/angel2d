%module angel
%{
#include "../../Infrastructure/Textures.h"
%}


void FlushTextureCache();
const int GetTextureReference(const String& name, bool optional = false);
const int GetTextureReference(const String& filename, GLint clampmode, GLint filtermode, bool optional = false);
const Vec2i GetTextureSize(const String& filename);
bool PurgeTexture(const String& filename);
