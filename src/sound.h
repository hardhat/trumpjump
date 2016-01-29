#ifndef SOUND_H
#define SOUND_H

enum SoundEffects {
	SE_JUMP,
	SE_START,

	SE_MAX
};

class Sound
{
	Sound();
	~Sound();
	static void init();
	static void playSong(int id);
	static void playSfx(int id);
};

