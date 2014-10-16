#ifndef MISSILE_HH
#define MISSILE_HH


#include "spaceobject.hh"
#include "ammo.hh"

class Game;
class Spacecraft;


/** Missile class derives from class Ammo and represents a self-guiding ammo. 
	*	It targets the other spacecraft in play, and has a field of vision 
	* determined by private member threshold.
	*/
class Missile : public Ammo {

public:
	/** The constructor.
		* @param id The missile's id (if it's a scud, sidewinder, maybe even an umkhonto =).
		* @param location The missile's starting location in space.
		* @param game Pointer to the Game object.
		* @param angle The missile's starting orientation.
		* @param target Pointer to the missile's target Spacecraft.
	*/
	Missile(int id, SpaceVector const &location, Game *game, double angle, Spacecraft *target);
	
	/** Moves the missile in space. */
	void move(double timestep);

private:
	/** Uses the thruster. */
	void useThruster();
	/** Seeks the target defined by private member target, and rotates the missile
		* accordingly, if target is in the field of vision determined by threshold.
		*/
	void seekTarget();
	
	void rotateLeft();
	
	void rotateRight();
	
	/** The missile's target ship, ie. the other one */
	Spacecraft *target;
	
	/** Missile's properties */
	//! Aiming threshold, or field of vision
	double threshold;
	//! turning speed
	double rotation_speed;
	//! thruster power
	double thruster_power;
};

#endif
