#ifndef SOUND_H
#define SOUND_H

enum SoundEffects {
	SFX_JUMP,
	SFX_START,
	SFX_MATCH,

	SFX_MAX
};

class Sound
{
public:
	Sound();
	~Sound();
	static void init();
	static void playSong(int id);
	static void playSfx(int id);
};

#endif
