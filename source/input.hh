

#ifndef INPUT_HH
#define INPUT_HH

#include "SDL/SDL.h"
#include "spacecraft.hh"
#include  "ai.hh"


/** Input takes care of keyboard input to control players. When necessary, it uses AI
  * for cpu players.
  *
  *	Controls:
  *
  *		Player #1: up arrow = throtte ; left arrow = rotate left; right arrow = rotate right
  *				 right control = fire ; right shift = use special
  *
  *		Player #2: e = throttle ; s = rotate left ; f = rotate right
  *				  q = fire ; 1 = use special
  */


class Input {

	public:

		/** Constructor
		  * @param ai the used AI object is given by the main program
		  */
                Input (AI *ai);
		
		/** game calls readInput during every cycle -- returns true if escape has been pressed
		  * ship1 or/and ship2 can be NULL
		  * @param humanControl1 false player 1 is AI controlled
		  * @param humanControl2 false player 2 is AI controlled
		  */
		 bool readInput (Spacecraft  *ship1, Spacecraft  *ship2, bool humanControl1, bool humanControl2);

	private:

		bool escapedown;

		/** player 1 controls */
		bool upup;
		bool leftup;
		bool rightup; 
 		bool rctrlup; 
		bool rshiftup;

		/** player 2 controls */
		bool eup;
		bool sup;
		bool fup;
		bool oneup;
		bool qup;

		AI *ai;

		SDL_Event keyevent;

};


#endif
