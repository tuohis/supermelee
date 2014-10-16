#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "sound.hh"
#include <string>
#include <iostream>

 ///  g++ -g -Wall -o game *.cc -lSDL -lSDLmain -lSDL_image -lGL -lSDL_mixer
///svn update
using namespace std;

void musicFinished();

#define MENU_MUSIC 1
#define GAME_MUSIC 2



Sound::Sound()
{

	this->audio_rate = 22050;			/** Frequency of audio playback */
	this->audio_format = AUDIO_S16SYS; 	/** Format of the audio we're playing */
	this->audio_channels = 2;			/** 2 channels = stereo */
	this->audio_buffers = 1024;		/** Size of the audio buffers in memory */
	this->trackNumber = 0;


	/** Initialize SDL_mixer with our chosen audio settings */
	if( Mix_OpenAudio(this->audio_rate, this->audio_format, this->audio_channels, this->audio_buffers) == -1)
	  std::cout << "Can't setup audio" << std::endl;
	
	/** Load music tracks into memory */
	this->music1 =Mix_LoadMUS("sound/menutrack.ogg");
	this->music2 =Mix_LoadMUS("sound/gamemusic.ogg");
	this->eff1 = Mix_LoadWAV("sound/laser.wav");
	if( this->music1 == NULL || this->music2 == NULL || this->eff1 == NULL)
	  std::cout << "Can't load audio files " << std::endl;
}


Sound::~Sound()
{
	/** Free all allocated memory and close SDL_mixer */
	Mix_FreeMusic(this->music1);
	Mix_FreeMusic(this->music2);
	Mix_FreeChunk(this->eff1);
	Mix_CloseAudio();
}

void Sound::playMusic(int id)
{

	/** See if music is playing already */
	if (Mix_PlayingMusic() != 0)
	{
		/**  Fade out previous music */
		Mix_FadeOutMusic(1000);
	}
	
	/** Play the chosen music */
	switch (id) {
		case MENU_MUSIC:
			Mix_PlayMusic(this->music1, -1);
			this->trackNumber = id;
			break;
		case GAME_MUSIC:
			Mix_PlayMusic(this->music2, -1);
			this->trackNumber = id;
			break;
		default:
			break;
	}

}

void Sound::stopMusic()
{
	if (Mix_PlayingMusic() != 0)
		{
		/** Stop music playback with fade out */
		Mix_FadeOutMusic(1000);
		}
}

void Sound::playEffect(int id)
{
	Mix_PlayChannel(2, eff1, 0);
}

