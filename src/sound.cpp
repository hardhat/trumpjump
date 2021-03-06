#include "SDL.h"
#include <stdio.h>
#include "SDL_mixer.h"
#include <map>
#include "sound.h"

static std::map <int,Mix_Music *> songMap;
static std::map <int,Mix_Chunk *> sfxMap;
static Mix_Music *activeMusic=0;

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

#ifdef __APPLE__
const char *songName[]={
    "dubstep trump.ogg",
    //"data/menu.ogg",
};
#else
const char *songName[]={
    "data/dubstep trump.ogg",
    //"data/menu.ogg",
};
#endif

void Sound::playSong(int id)
{
	int repeatTimes=-1;

	// Loop the selected sound
	if(id<0 || (unsigned)id>=(sizeof(songName)/sizeof(const char *))) {
		printf("Requested id %d not a song.\n",id);
		return;
	}
        Mix_HaltMusic();
        activeMusic=NULL;
        if(songMap.find(id)!=songMap.end()) {
                Mix_Music *s=songMap.find(id)->second;
                if(activeMusic==s) return;
                Mix_PlayMusic(s, repeatTimes); // play looping.
                activeMusic=s;
        } else {
                Mix_Music *s=NULL;
		const char *path=songName[id];
                if(path) s=Mix_LoadMUS(path);
                if(s==NULL) {
                        return;
                }
                Mix_PlayMusic(s, repeatTimes); // play looping.
                songMap[id]=s;
                activeMusic=s;
        }

}

#ifdef __APPLE__
const char *sfxName[]={
	"jump.wav",
	"start.wav",
	"match.wav",
	"potato.wav",
	"meatloaf.wav",
	"chaching.wav",
	"rich.wav",
	"baby.wav",
};
#else
const char *sfxName[]={
    "data/jump.wav",
    "data/start.wav",
    "data/match.wav",
    "data/potato.wav",
    "data/meatloaf.wav",
    "data/chaching.wav",
    "data/rich.wav",
    "data/baby.wav",
};

#endif

void Sound::playSfx(int id)
{
	// Play once the selected sound effect.
	if(id<0 || (unsigned)id>=(sizeof(sfxName)/sizeof(const char *))) {
		printf("Requested id %d not a sound effect.\n",id);
		return;
	}
	int channel=id;
        if(sfxMap.find(id)!=sfxMap.end()) {
                Mix_Chunk *c=sfxMap.find(id)->second;
                Mix_PlayChannel(channel,c,0); // play on any channel
        } else {
                Mix_Chunk *c=NULL;
		const char *path=sfxName[id];
                if(path) c=Mix_LoadWAV(path);
                if(c==NULL) {
                        Mix_HaltChannel(channel);
                        return;
                }
                printf("Playing sfx %d\n",id);
                Mix_PlayChannel(channel, c, 0); // play on channel.
                sfxMap[id]=c;
        }
}
