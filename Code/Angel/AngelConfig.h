// A set of compile flags to control large feature inclusion/exclusion


// Swap this to 1 to disable FMOD. Angel will fall back to using OpenAL
//  for audio, and will *only* be able to play Ogg Vorbis files. 
#define ANGEL_DISABLE_FMOD  0

// Swap this to 1 to disable DevIL. Angel will fall back to using libpng
//  for textures, and will *only* be able to display PNG images. 
//  
//  Note that this is set to 1 automatically when building for iOS. 
#define ANGEL_DISABLE_DEVIL 0
