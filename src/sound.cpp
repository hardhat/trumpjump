#include <SDL.h>
#include <SDL_mixer.h>

#include "sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::init()
{
	// load the music and sound effects.
	Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

}

void Sound::playSong(int id)
{
	// Loop the selected sound

} 

void Sound::playSfx(int id)
{
	// Play once the selected sound effect.

}
