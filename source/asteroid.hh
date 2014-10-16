#ifndef ASTEROID_HH
#define ASTEROID_HH

#include "spacevector.hh"
#include "spaceobject.hh"

/** Class Asteroid is derived from SpaceObject and represents, surprisingly, 
	* an asteroid. Asteroids have no way to affect their movement status. For 
	* added visuality they rotate around themselves with random, yet constant speed. */
class Asteroid : public SpaceObject {
public:
	/** Constructor.
		* @param id Asteroid's ID number.
		* @param location Asteroid's location in space.
		* @param game Pointer to the Game object. */
	Asteroid(int id, SpaceVector const &location, Game *game);
	/** Moves the asteroid in space. */
	void move(double timestep);

private:
	/** Asteroids rotate steadily. */
	double rotation_speed;

};

#endif
