#ifndef AMMO_HH
#define AMMO_HH

#include "spaceobject.hh"

class Game;

/** Class Ammo derives from SpaceObject and represents bullets, laser beams, 
	* etc. stuff to shoot with. An essential new field is lifetime, which, along 
	* with (max_)speed, determines the ammo's range. */
class Ammo : public SpaceObject {
public:
	/** Constructor.
		* @param id The ammo's ID number.
		* @param location The ammo's location in space.
		* @param game Pointer to Game object.
		* @param angle Ammo's alignment. */
	Ammo(int id, SpaceVector const &location, Game *game, double angle);
	
	/** Moves ammo in space, and takes care of lifetime. */
	void move(double timestep);

protected:
	/** How fast the ammo can move */
	double max_speed;
	
	/** The lifetime of the ammo in game frames */
	int lifetime;
};

#endif
