#include <iostream>
#include "spacecraft.hh"
#include "ammo.hh"
#include "missile.hh"
#include "game.hh"
#include <list>

Spacecraft::Spacecraft(int id, SpaceVector const &location, Game *game) : 
			SpaceObject(id, location, game)
{
	this->id = id;
	angle = 0;
	velocity = SpaceVector(0,0);
	curr_fire_delay = 0;
	damage = 0;
	
	/** Initialize ships based on ID */
	switch(id) {
		case 1: 
		  mass = MASS_S1;
		  size = SIZE_S1;
		  max_speed = MAX_SPEED_S1;
		  max_crew = crew = CREW_S1;
		  rotation_speed = ROTATION_SPEED_S1;
		  thruster_power = THRUSTER_POWER_S1;
		  max_energy = energy = ENERGY_S1;
		  fire_energy = FIRE_ENERGY_S1;
		  energy_recover = ENERGY_RECOVER_S1;
		  thruster_energy = THRUSTER_ENERGY_S1;
			special_energy = SPECIAL_ENERGY_S1;
		  fire_delay = FIRE_DELAY_S1;
		  ammo_id = AMMO_ID_S1;
		  break;
		
		case 2: 
		  mass = MASS_S2;
		  size = SIZE_S2;
		  max_speed = MAX_SPEED_S2;
		  max_crew = crew = CREW_S2;
		  rotation_speed = ROTATION_SPEED_S2;
		  thruster_power = THRUSTER_POWER_S2;
		  max_energy = energy = ENERGY_S2;
		  fire_energy = FIRE_ENERGY_S2;
		  energy_recover = ENERGY_RECOVER_S2;
		  thruster_energy = THRUSTER_ENERGY_S2;
			special_energy = SPECIAL_ENERGY_S2;
		  fire_delay = FIRE_DELAY_S2;
		  ammo_id = AMMO_ID_S2;
		  break;

	case 3: 
		  mass = MASS_S3;
		  size = SIZE_S3;
		  max_speed = MAX_SPEED_S3;
		  max_crew = crew = CREW_S3;
		  rotation_speed = ROTATION_SPEED_S3;
		  thruster_power = THRUSTER_POWER_S3;
		  max_energy = energy = ENERGY_S3;
		  fire_energy = FIRE_ENERGY_S3;
		  energy_recover = ENERGY_RECOVER_S3;
		  thruster_energy = THRUSTER_ENERGY_S3;
			special_energy = SPECIAL_ENERGY_S3;
		  fire_delay = FIRE_DELAY_S3;
		  ammo_id = AMMO_ID_S3;
		  break;

	case 4: 
		  mass = MASS_S4;
		  size = SIZE_S4;
		  max_speed = MAX_SPEED_S4;
		  max_crew = crew = CREW_S4;
		  rotation_speed = ROTATION_SPEED_S4;
		  thruster_power = THRUSTER_POWER_S4;
		  max_energy = energy = ENERGY_S4;
		  fire_energy = FIRE_ENERGY_S4;
		  energy_recover = ENERGY_RECOVER_S4;
		  thruster_energy = THRUSTER_ENERGY_S4;
			special_energy = SPECIAL_ENERGY_S4;
		  fire_delay = FIRE_DELAY_S4;
		  ammo_id = AMMO_ID_S4;
		  break;
			
	}
}
						
void Spacecraft::move(double timestep)
{
	/** Destroy when dead */
	if(crew <=0) {
		game->removeSpacecraft(this);
		return;
	}
	
	/** Calculate new velocity */
	if(this->mass > 0) {
			this->velocity += timestep / this->mass * this->force;

		/** Check if going too fast */
		if(this->velocity.length() > this->max_speed)
			this->velocity = max_speed*this->velocity.unit();
	}

	// set force to 0
	this->force = SpaceVector(0,0);

	/** Move object with new speed */
	this->location += timestep * this->velocity;
	
	/** Check if out of space limits; move if necessary */
	game->vectorToOrigo(this->location);

	/** Recover energy */
	energy += timestep * energy_recover;
	if (energy > max_energy)
		energy = max_energy;
	
	/** Diminish delay, so one can shoot again sometime */
	if (curr_fire_delay > 0)
		--curr_fire_delay;
	
	/** Ship 5 must reset its thruster and speed values after using special effect */
	if (id == SHIP5_ID && max_speed != MAX_SPEED_S5) {
		max_speed = MAX_SPEED_S5;
		thruster_power = THRUSTER_POWER_S5;
	}
	
	
}


void Spacecraft::fire()
{

	
	
	/** Don't want them firing 60 rounds per sec */
	if (curr_fire_delay == 0 && energy >= fire_energy) {
		energy -= fire_energy;
		
		// play sound effect "laser.wav"
		game->getSound()->playEffect(1);

		Ammo *ammo = new Ammo(ammo_id, location, game, angle);
		
		// Set ammo's position so it doesn't explode on the firing ship
		ammo->getLocation().add(SpaceVector(size + ammo->getSize() + .2, angle, 0));
		
		// Set ammo's velocity so it corresponds with the ship's movement
		// if (ammo->getMass() > 0) // Lasers go straight
			ammo->getVelocity() += velocity;
		
		game->addAmmo(ammo);
		curr_fire_delay = fire_delay;
	}
}

/** Use the ship's special ability. 
	* The special ability _may_ be a superior weapon, so behaviour like fire()
	* is needed. If the special ability doesn't inclure firing anything, just
	* return null.
	* @return pointer to ammo or NULL. */
void Spacecraft::useSpecial()
{
	if (energy >= special_energy) {
		energy -= special_energy;
		switch(id) {
			/** Ship 1 teleports. */
			case SHIP1_ID:
				do {
					location = SpaceVector((double)rand()/RAND_MAX * game->getSize().getX(), 
																(double)rand()/RAND_MAX * game->getSize().getY());
				// Don't teleport inside an object
				} while (game->checkCollisionAll(*this) == true);
			
				break;
			
			/** Ship 2 fires missiles. */
			case SHIP2_ID:
			{
				
				/* Acquire pointer to target */
				std::list<Spacecraft *> ships = game->getSpacecrafts();
				Spacecraft *target = NULL;
				if (ships.front() == this) {
					target = ships.back();
				} else {
					target = ships.front();
				}
				
				/* Create new missile object */
				Missile *missile = new Missile(MISSILE1_ID, location, game, angle, target);
				
				// Set missile's position so it doesn't explode on the firing ship
				missile->getLocation().add(SpaceVector(size + missile->getSize() + .2, angle, 0));
				// Add ship's current speed to the missile's speed
				missile->getVelocity().add(velocity);
				
				game->addAmmo(missile);
				break;
			}
			
			/** Ship 3 fires a big one. */
			case SHIP3_ID:
				{
				Ammo *ammo = new Ammo(SPECIAL_S3, location, game, angle);
		
				// Set ammo's position so it doesn't explode on the firing ship
				ammo->getLocation().add(SpaceVector(size + ammo->getSize() + .2, angle, 0));
				// Add ship's current speed to the ammo's speed
				ammo->getVelocity().add(velocity);
				
				game->addAmmo(ammo);
				break;
				}
			
			/** Ship 4 heals its crew. */
			case SHIP4_ID:
				crew += 5;
				if (crew > max_crew)
					crew = max_crew;
				break;
			
			/** Ship 5 turbo boosts. */
			case SHIP5_ID:
				max_speed = MAX_SPEED_S5 + 100;
				thruster_power = THRUSTER_POWER_S5 + 1000;
				break;
			
			/** Ship 6 lays mines. */
			case SHIP6_ID:
				
			break;
			
			default:
				break;
		}
	
	}
}

/** Use rocket engines. */
void Spacecraft::useThruster()
{
	if (energy < thruster_energy)
		return;
	else {
		this->addForce(thruster_power * SpaceVector(cos(this->angle / 180 * PI), 
																							sin(this->angle / 180 * PI)) );
		energy -= thruster_energy;
	}
}
	
/** Rotate ship counterclockwise. */
void Spacecraft::rotateLeft()
{
	this->angle += this->rotation_speed;
	if (this->angle > 180)
		this->angle -= 360;
	
}

/** Rotate ship clockwise. */
void Spacecraft::rotateRight()
{
	this->angle -= this->rotation_speed;
	if (this->angle < -180)
		this->angle += 360;
}

double Spacecraft::getEnergy()
{
	return energy;
}

double Spacecraft::getMaxEnergy()
{
	return max_energy;
}

double Spacecraft::getCrew()
{
	return crew;
}

double Spacecraft::getMaxCrew()
{
	return max_crew;
}
