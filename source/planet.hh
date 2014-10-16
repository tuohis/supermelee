#ifndef PLANETOID_HH
#define PLANETOID_HH

#include "spacevector.hh"
#include "spaceobject.hh"

/** Planets are derived from SpaceObject. They are inanimate, static objects, 
	* and they have a field of gravity. */
class Planet : public SpaceObject {
public:
	/** Constructor.
		* @param id Planet's ID.
		* @param location Planet's location in space.
		* @param game Pointer to the Game object. */
	Planet(int id, SpaceVector const &location, Game *game);
	
	/** Cannot move, yet must be implemented to fulfill SpaceObject's requirements */
	void move(double timestep);

};

#endif
