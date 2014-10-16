#include "asteroid.hh"
#include "game.hh"
#include <math.h>
#include <stdlib.h>

Asteroid::Asteroid(int id, SpaceVector const &location, Game *game) : SpaceObject(id, location, game)
{
	switch(id) {
		case ASTEROID1_ID:			// Asteroid 1
			mass = MASS_AS1;
			size = SIZE_AS1;
			crew = CREW_AS1;
			break;
		case ASTEROID2_ID:				// Asteroid 2
			mass = MASS_AS2;
			size = SIZE_AS2;
			crew = CREW_AS2;
			
	}
	
	damage = 0;
	velocity = SpaceVector(rand()/(double)RAND_MAX*100+10, rand()/(double)RAND_MAX*360, 0); // Random velocity
	rotation_speed = (rand()/(double)RAND_MAX - 0.5)*6; // How fast rotates 'round itself

}

void Asteroid::move(double timestep)
{
	/** Destroy when dead */
	if(crew <=0) {
		game->removeAsteroid(this);
		return;
	}
	
	/** Rotate, so the asteroid looks a bit more animate */
	angle += rotation_speed;
	
	/** Calculate new velocity */
	this->velocity += timestep / this->mass * this->force;

	// set force to 0
	this->force = SpaceVector(0,0);

	/** Move object with new speed */
	this->location += timestep * this->velocity;
	
	/** Check if out of space limits; move if necessary */
	game->vectorToOrigo(this->location);
}
