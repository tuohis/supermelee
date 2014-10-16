#include "planet.hh"

Planet::Planet(int id, SpaceVector const &location, Game *game) : SpaceObject(id, location, game)
{
	damage = angle = 0;
	velocity = force = SpaceVector(0,0);
	crew = 1000000; // Virtually indestructible
	
	switch(id) {
		case PLANET1_ID:
			mass = MASS_P1;
			size = SIZE_P1;
	}
}
	
// Cannot move
void Planet::move(double timestep) {
  this->velocity = SpaceVector(0,0);
	return;
}
