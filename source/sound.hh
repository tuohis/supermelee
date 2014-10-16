#ifndef SOUND_HH
#define SOUND_HH

#include <string>
#include <iostream>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

/** Sound handles all sound output of the game. 
  * It plays the two music tracks and the laser gun 
  * sound effect.
  */


class Sound {

	public:

		/** Constructor */
		Sound();

		/** Destructor */
		~Sound();
	
		/** Plays certain music file (in Ogg Vorbis format)
		  * @param id = id of the file to be played
		  */
		void playMusic(int id);

		/** Stops music playback with fade out */
		void stopMusic();

		/** Plays the laser gun sound effect */
		void playEffect(int id);

	private:

		Mix_Music *music1;		/** Music track 1 */
		Mix_Music *music2;		/** Music track 2 */
		Mix_Chunk *eff1;		/** Laser gun sound effect */
		
		int audio_rate;			/** Frequency of audio playback */
		Uint16 audio_format; 	/** Format of the audio we're playing */
		int audio_channels;		/** 2 channels = stereo */
		int audio_buffers;		/** Size of the audio buffers in memory */

		int trackNumber;



};

#endif 

