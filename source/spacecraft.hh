#ifndef SPACECRAFT_HH
#define SPACECRAFT_HH

#include "spacevector.hh"
#include "spaceobject.hh"
#include <math.h>


class Ammo;
class Game;
class AI;

/** Spacecraft derives from SpaceObject. Each space ship/craft is an instance 
	* of Spacecraft. Their properties are defined by the field id, given as a 
	* parameter for the constructor. */
class Spacecraft : public SpaceObject {

public:
	/** Helps with implementing the AI system. */
	friend class AI;
	
	/** Constructor.
		* @param id The ship's ID number, which determines the ship's type.
		* @param location The craft's location in space.
		* @param game Pointer to the Game object.
		*/
	Spacecraft(int id, SpaceVector const &location, Game *game);
	
	/** Move the craft in space according to its speed and affecting force. 
		* @param timestep The amount of time one frame covers. Default: 1/60 s. */
	void move(double timestep);
	
	/** Fire the ship's main weapon with this method. */
	void fire();

	/** Use the ship's special ability. 
		* The special ability may vary from turbo-boosting to firing superior 
		* weapons to.. anything, really. */
	void useSpecial();

	/** Use rocket engines. */
	void useThruster();
	
	/** Rotate ship counterclockwise. */
	void rotateLeft();

	/** Rotate ship clockwise. */
	void rotateRight();
	
	
	
	/** Acquire info about craft's properties. @{ */
	double getEnergy();
	double getMaxEnergy();
	
	double getCrew();
	double getMaxCrew();
	/** @} */

private:
	/** Copy constructor inusable */
	Spacecraft(Spacecraft &s);
	
	/** Ship-specific properties. @{*/
	/** How fast rotates; degrees/frame. */
	double rotation_speed;
	/** How much force the thruster produces. */
	double thruster_power;
	/** Crew maximum. */
	double max_crew;
	/** Maximum speed, ie. SpaceVector velocity.length() <= max_speed. */
	double max_speed;
	/** Ship's current energy reserve / battery status. */
	double energy;
	/** Ship's maximum battery level. */
	double max_energy;
	/** How much energy ship recovers per frame. */
	double energy_recover;
	/** How much energy thruster uses per frame. */
	double	thruster_energy;
	/** How much energy firing costs per shot. */
	double fire_energy;
	/** How much energy special effect uses per use. */
	double special_energy;
	/** The delay between shots. */
	int fire_delay;
	/** Counter for implementing the delay. */
	int curr_fire_delay;
	/** What type of ammunition uses. */
	int ammo_id;
	/** @} */

};

#endif
