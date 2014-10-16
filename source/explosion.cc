#include "explosion.hh"
#include "game.hh"

Explosion::Explosion(double size, SpaceVector const &location, Game *game) :
					SpaceObject(EXPLOSION_ID, location, game)
{
	this->size = size-1;
	if (size<1)
		size=1;
	this->lifetime = EXPLOSION_LIFETIME;
}

Explosion::~Explosion() {}


void Explosion::move(double timestep)
{
	/** Diminish lifetime */
	lifetime -= timestep;
	size += 200*timestep/size;
	
	/** Make bigger and more transparent, so the explosion seems to grow and 
		* fade away */
	transparency = this->lifetime / (double) EXPLOSION_LIFETIME;
	size = size * 1.01;
	
	/** Delete when lifetime <= 0 */
	if (lifetime <= 0)
		game->removeExplosion(this);
}
