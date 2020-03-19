#define DISPLAY_MODE DISPLAY_MODE_INDEX

#define FOLDER_NAME "BumbleBotsRePair"

#define SOUND_FREQ 22050

// Double buffer size used for playing music, so it plays more smoothly.
#define SOUND_BUFFERSIZE 4096

// Reduce number of channels. Only two should be needed, one for FX, another for music.
// Note FX has a dedicated channel, so one channel suffices.
#define SOUND_CHANNELS 1
