#include "ammo.hh"
#include "game.hh"
#include "spacevector.hh"
#include <math.h>

Ammo::Ammo(int id, SpaceVector const &location, Game *game, double angle) : 
					SpaceObject(id, location, game)
{
	this->angle = angle;
	switch(id) {
		case AMMO1_ID:
			crew = CREW_A1;
			lifetime = LIFETIME_A1;
			mass = MASS_A1;
			size = SIZE_A1;
			max_speed = MAX_SPEED_A1;
			damage = DAMAGE_A1;
			break;
		
		case AMMO2_ID:
			crew = CREW_A2;
			lifetime = LIFETIME_A2;
			mass = MASS_A2;
			size = SIZE_A2;
			max_speed = MAX_SPEED_A2;
			damage = DAMAGE_A2;
			break;
		
		case AMMO3_ID:
			crew = CREW_A3;
			lifetime = LIFETIME_A3;
			mass = MASS_A3;
			size = SIZE_A3;
			max_speed = MAX_SPEED_A3;
			damage = DAMAGE_A3;
			break;
	}

	velocity = SpaceVector(max_speed, angle, 0);
	
}

void Ammo::move(double timestep)
{
	
	/** Destroy when dead */
	if(lifetime <= 0 || crew <=0) {
		game->removeAmmo(this);
		return;
	}
	
	/** Diminish lifetime each frame */
	--lifetime;
	
	/** Calculate new velocity */
	if(this->mass > 0) {
			this->velocity += timestep / this->mass * this->force;

		/** Check if going too fast */
		// if(velocity.length() > max_speed)
			// velocity = max_speed*velocity.unit();
	}

	/** Move object with new speed */
	this->location += timestep * this->velocity;
	
	/** Check if out of space limits; move if necessary */
	game->vectorToOrigo(this->location);
	
	/** Set force to zero */
	force = SpaceVector(0,0);
	
}
