#include "missile.hh"
#include "game.hh"
#include "spacecraft.hh"
#include <iostream>

Missile::Missile(int id, SpaceVector const &location, Game *game, double angle,
						Spacecraft *target) : Ammo(id, location, game, angle), target(target)
{
	switch(id) {
		case MISSILE1_ID:
			crew = CREW_M1;
			lifetime = LIFETIME_M1;
			mass = MASS_M1;
			size = SIZE_M1;
			max_speed = MAX_SPEED_M1;
			damage = DAMAGE_M1;
			
			threshold = THRESHOLD_M1;
			rotation_speed = ROTATION_SPEED_M1;
			thruster_power = THRUSTER_POWER_M1;
			
			velocity = SpaceVector(100, angle, 0);
			break;
		
		case MISSILE2_ID:
			crew = CREW_M2;
			lifetime = LIFETIME_M2;
			mass = MASS_M2;
			size = SIZE_M2;
			max_speed = MAX_SPEED_M2;
			damage = DAMAGE_M2;
			
			threshold = THRESHOLD_M2;
			rotation_speed = ROTATION_SPEED_M2;
			thruster_power = THRUSTER_POWER_M2;
			break;
	}
	
}

void Missile::move(double timestep)
{
	/** Destroy when dead */
	if(lifetime <= 0 || crew <=0) {
		game->removeAmmo(this);
		return;
	}
	/** Diminish lifetime each frame */
	--lifetime;
	
	/** Seek target (if exists) and turn if needed */
	if (target != NULL)
		seekTarget();
	
	/** Thruster is always on */
	useThruster();

	/** Calculate new velocity */
	this->velocity += timestep / this->mass * this->force;

	/** Check if going too fast */
	if(velocity.length() > max_speed)
		velocity = max_speed*velocity.unit();

	/** Move object with new speed */
	this->location += timestep * this->velocity;
	
	/** Check if out of space limits; move if necessary */
	game->vectorToOrigo(this->location);
	
	/** Set force to zero */
	force = SpaceVector(0,0);
	
}

void Missile::seekTarget()
{
	/** targetAngle is the difference between missile's orientation and the 
		* vector between missile and target */
	SpaceVector targetLocation = target->getLocation();
	game->vectorToVector(targetLocation, location);
	
	double targetAngle = (targetLocation - location).angle() - angle;
	
	while (targetAngle < -180)
		targetAngle += 360;
	while (targetAngle > 180)
		targetAngle -= 360;
	
	/** If target within threshold, lock on */
	if (targetAngle > 0) {
		if (targetAngle + rotation_speed < threshold)
			rotateLeft();
		else if (targetAngle < threshold)
			rotateRight();
	}
	else if (targetAngle < 0) {
		if (targetAngle - rotation_speed > -threshold)
			rotateRight();
		else if (targetAngle > -threshold)
			rotateLeft();
	}
	
}

void Missile::useThruster()
{
	addForce(SpaceVector(thruster_power, angle, 0));
}

void Missile::rotateLeft()
{
	angle += rotation_speed;
	if (angle > 180)
		angle -= 360;
}

void Missile::rotateRight()
{
	angle -= rotation_speed;
	if (angle < -180)
		angle += 360;
}
