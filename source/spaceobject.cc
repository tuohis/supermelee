#include "spaceobject.hh"
#include "explosion.hh"
#include "game.hh"
#include <stdlib.h>

SpaceObject::SpaceObject(int id, SpaceVector const &location, Game *game) : 
							game(game), location(location), angle(DEFAULT_ANGLE), 
							force(SpaceVector(0,0)), id(id), transparency(1.0) {}

SpaceObject::~SpaceObject() {}

/** This method adds a given force to the total force affecting the object.
	* @param f Reference to the (SpaceVector) force to be added. */
void SpaceObject::addForce(SpaceVector const &f)
{
	this->force += f;
}

/** One can find out the object's location in space by calling this method.
	* @return Object's location as SpaceVector. */
SpaceVector &SpaceObject::getLocation()
{
	return this->location;
}

SpaceVector &SpaceObject::getVelocity()
{
	return this->velocity;
}

/** @return Object's alignment in space */
double SpaceObject::getAngle()
{
	return this->angle;
}

/** @return Object's ID number */
int SpaceObject::getID()
{
	return this->id;
}

double SpaceObject::getSize()
{
	return this->size;
}

double SpaceObject::getMass()
{
  return this->mass;
}

int SpaceObject::doDamage(double amount)
{
	this->crew -= amount;
	if (this->crew > 0)
		return 1;
	else {
		/** If the object is to be destroyed, add explosion */
		game->addExplosion(new Explosion(size, location, game));
		return -1;
	}
}

double SpaceObject::getDamage()
{
	return this->damage;
}

double SpaceObject::getTransparency()
{
  return this->transparency;
}
