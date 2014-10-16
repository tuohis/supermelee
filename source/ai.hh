#ifndef AI_HH
#define AI_HH

#include "SDL/SDL.h"
#include "spacevector.hh"
#include <stdlib.h>

class SpaceObject;
class Spacecraft;

/** The AI class is basically a wrapper of a cpu Spacecraft. 
 *  It monitors the movement of the human player and controls
 *  the cpu Spacecraft accordingly.
 */
class AI {

public:

  /** Moves the spacecraft.
   * @param craft spacecraft to be moved
   * @param enemy the enemy spacecraft
   */
  void act(Spacecraft* craft, Spacecraft* enemy);

private:

};


#endif
