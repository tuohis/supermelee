#ifndef SPACEOBJECT_HH
#define SPACEOBJECT_HH

#include "spacevector.hh"

#define DEFAULT_MASS 20
#define DEFAULT_SIZE 5
#define DEFAULT_MAX_SPEED 200
#define DEFAULT_CREW 50
#define DEFAULT_ANGLE 0
#define DEFAULT_VELOCITY SpaceVector(0,0)

/** @name Absolutes 
	* For drawing the status bars 
	*/
/* @{ */
#define ABSOLUTE_MAX_CREW 50
#define ABSOLUTE_MAX_ENERGY 50
/* @} */

/* @{ */
//! @name For explosions
#define EXPLOSION_ID 1000
//! Lifetime is in seconds on screen
#define EXPLOSION_LIFETIME 1.0
/* @} */

/** @name Different objects' ID numbers. 
	* The values have no greater meaning, 
	* since only the defined variables are used throughout the code. */
/* @{ */
#define SHIP1_ID 1
#define SHIP2_ID 2
#define SHIP3_ID 3
#define SHIP4_ID 4
#define SHIP5_ID 5
#define SHIP6_ID 6
#define AMMO1_ID 10
#define AMMO2_ID 11
#define AMMO3_ID 12
#define AMMO4_ID 13
#define MISSILE1_ID 11
#define MISSILE2_ID 19
#define ASTEROID1_ID 20
#define ASTEROID2_ID 21
#define PLANET1_ID 100
#define PLANET2_ID 101
/* @} */

/** @name Ship 1 stats */
/* @{ */
#define MASS_S1 20
#define SIZE_S1 5
#define MAX_SPEED_S1 200
#define CREW_S1 21
#define ROTATION_SPEED_S1 6.0
#define THRUSTER_POWER_S1 2500
#define ENERGY_S1 10
#define FIRE_ENERGY_S1 1
#define ENERGY_RECOVER_S1 5
#define THRUSTER_ENERGY_S1 0.05
#define SPECIAL_ENERGY_S1 8
#define FIRE_DELAY_S1 30
#define AMMO_ID_S1 AMMO1_ID
/* @} */

/** @name Ship 2 stats */
/* @{ */
#define MASS_S2 40
#define SIZE_S2 10
#define MAX_SPEED_S2 150
#define CREW_S2 50
#define ROTATION_SPEED_S2 3.0
#define THRUSTER_POWER_S2 3500
#define ENERGY_S2 30
#define FIRE_ENERGY_S2 2
#define ENERGY_RECOVER_S2 10
#define THRUSTER_ENERGY_S2 0.2
#define SPECIAL_ENERGY_S2 20.3
#define FIRE_DELAY_S2 60
#define AMMO_ID_S2 AMMO2_ID
/* @} */
/** @name Ship 3 stats */
/* @{ */
#define MASS_S3 30
#define SIZE_S3 6
#define MAX_SPEED_S3 150
#define CREW_S3 30
#define ROTATION_SPEED_S3 5.0
#define THRUSTER_POWER_S3 5000
#define ENERGY_S3 20
#define FIRE_ENERGY_S3 1
#define ENERGY_RECOVER_S3 10
#define THRUSTER_ENERGY_S3 0.1
#define SPECIAL_ENERGY_S3 19
#define FIRE_DELAY_S3 30
#define AMMO_ID_S3 AMMO1_ID
#define SPECIAL_S3 AMMO3_ID
/* @} */
/** @name Ship 4 stats */
/* @{ */
#define MASS_S4 30
#define SIZE_S4 6
#define MAX_SPEED_S4 150
#define CREW_S4 30
#define ROTATION_SPEED_S4 5.0
#define THRUSTER_POWER_S4 5000
#define ENERGY_S4 20
#define FIRE_ENERGY_S4 1
#define ENERGY_RECOVER_S4 10
#define THRUSTER_ENERGY_S4 0.1
#define SPECIAL_ENERGY_S4 19
#define FIRE_DELAY_S4 30
#define AMMO_ID_S4 AMMO1_ID
/* @} */
/** @name Ship 5 stats */
/* @{ */
#define MASS_S5 30
#define SIZE_S5 6
#define MAX_SPEED_S5 150
#define CREW_S5 30
#define ROTATION_SPEED_S5 5.0
#define THRUSTER_POWER_S5 5000
#define ENERGY_S5 20
#define FIRE_ENERGY_S5 1
#define ENERGY_RECOVER_S5 10
#define THRUSTER_ENERGY_S5 0.1
#define SPECIAL_ENERGY_S5 19
#define FIRE_DELAY_S5 30
#define AMMO_ID_S5 AMMO1_ID
/* @} */
/** @name Ship 6 stats */
/* @{ */
#define MASS_S6 30
#define SIZE_S6 6
#define MAX_SPEED_S6 150
#define CREW_S6 30
#define ROTATION_SPEED_S6 5.0
#define THRUSTER_POWER_S6 5000
#define ENERGY_S6 20
#define FIRE_ENERGY_S6 1
#define ENERGY_RECOVER_S6 10
#define THRUSTER_ENERGY_S6 0.1
#define SPECIAL_ENERGY_S6 19
#define FIRE_DELAY_S6 30
#define AMMO_ID_S6 AMMO1_ID
#define SPECIAL_S6 AMMO4_ID
/* @} */
/** @name Ammo 1 stats */
/* @{ */
#define MASS_A1 0
#define SIZE_A1 1
#define MAX_SPEED_A1 400
#define CREW_A1 2
#define LIFETIME_A1 90
#define DAMAGE_A1 5
/* @} */
/** @name Ammo 2 stats */
/* @{ */
#define MASS_A2 3
#define SIZE_A2 2
#define MAX_SPEED_A2 300
#define CREW_A2 2
#define LIFETIME_A2 90
#define DAMAGE_A2 7
/* @} */
/** @name Ammo 3 stats */
/* @{ */
#define MASS_A3 10
#define SIZE_A3 4
#define MAX_SPEED_A3 75
#define CREW_A3 2
#define LIFETIME_A3 120
#define DAMAGE_A3 20
/* @} */
/** @name Ammo 3 stats */
/* @{ */
// MINE!
#define MASS_A4 10
#define SIZE_A4 6
#define MAX_SPEED_A4 0
#define CREW_A4 2
#define LIFETIME_A4 1000
#define DAMAGE_A4 20
/* @} */
/** @name Missile 1 stats */
/* @{ */
#define MASS_M1 20
#define SIZE_M1 3
#define MAX_SPEED_M1 170
#define CREW_M1 1
#define LIFETIME_M1 100
#define DAMAGE_M1 8
#define THRESHOLD_M1 60
#define ROTATION_SPEED_M1 3
#define THRUSTER_POWER_M1 3000
/* @} */
/** @name Missile 2 stats */
/* @{ */
#define MASS_M2 30
#define SIZE_M2 4.5
#define MAX_SPEED_M2 100
#define CREW_M2 1
#define LIFETIME_M2 400
#define DAMAGE_M2 13
#define THRESHOLD_M2 15
#define ROTATION_SPEED_M2 3
#define THRUSTER_POWER_M2 3000
/* @} */
/** @name Planet 1 stats */
/* @{ */
#define MASS_P1 1000
#define SIZE_P1 10
/* @} */
/** @name Asteroid 1 stats */
/* @{ */
#define MASS_AS1 20
#define SIZE_AS1 4
#define CREW_AS1 20
/* @} */
/** @name Asteroid 2 stats */
/* @{ */
#define MASS_AS2 40
#define SIZE_AS2 5
#define CREW_AS2 100
/* @} */
#define PI 3.14159

class Game;

/** SpaceObject is the virtual base class for all objects in play. The Spacecrafts,
	* Ammo, Asteroids and Planets are all derived from it. SpaceObject stores the 
	* most essential pieces of information, those which are common for all the objects.*/
class SpaceObject {
public:
	/** Constructor.
		* @param id The object's id; determines the properties of the created object.
		* @param location The object's location in space.
		* @param game A pointer to the Game object. */
	SpaceObject(int id, SpaceVector const &location, Game *game);
	
	/** Destructor. This class can be derived from. */
	virtual ~SpaceObject();
	/** @name Methods for changing object's movement state */
	/* @{ */
	
	/** This method calculates object's new speed and moves the object in space
	* accordingly. Declared pure virtual, so each subclass must implement this.
	* @param timestep The amount of time between frames (default: 1/60 s)
	*/
	virtual void move(double timestep) =0;

	/** This method adds a given force to the total force affecting the object.
	* @param f Reference to the (SpaceVector) force to be added. */
	void addForce(SpaceVector const &f);
	/* @} */
	
	/** One can find out the object's location in space by calling this method.
	* @return Object's location as SpaceVector. */
	SpaceVector &getLocation();
	
	/** @return Object's velocity */
	SpaceVector &getVelocity();
	
	/** @return Object's alignment in space */
	double getAngle();
	
	/** @return Object's ID number. */
	int getID();
	
	/** @return Object's radius */
	double getSize();
	
	/** @return Object's mass */
  double getMass();

  /** Afflict damage on the ship.
		* @param amount Amount of crew to be lost.
		* @return Negative if the object is destroyed, positive otherwise	*/
	int doDamage(double amount);

	/** @return Object's damage value */
	double getDamage();

  /** @return objects transparency 0.0 = transparent 1.0 = not transparent*/
	double getTransparency();
	
protected:
	/** Pointer to Game. */
	Game *game;
	
	/** @name Object properties */
	/* @{ */
	double mass;
	double size;
	double damage;
	double crew;
	/* @} */
	
	/** Location. */
	SpaceVector location;
	/** Alignment. */
	double angle;
	
	/** @name Movement */
	/* @{ */
	SpaceVector force;
	SpaceVector velocity;
	/* @} */
	
	/** Object ID number for Screen (textures etc) */
	int id;
	/** Object transparency for drawing purposes. Gets values [0,1]. */
  double transparency;
	
};

#endif
