#include "SDL/SDL.h"
#include "spacecraft.hh"
#include "spaceobject.hh"
//#include "game.hh"
#include "ai.hh"
#include <math.h>
#include "spacevector.hh"
#include <iostream>

#define SHOOT_DIST 200.0
#define AVOID_DIST 40.0 

#define SPEED 200.0
#define LEAD 0.5

#define ROTATION_DIFF 5.0
#define AVOID_DIFF 30.0

#define SPECIAL_PROB 0.2

void AI::act(Spacecraft* craft, Spacecraft* enemy)
{

	double dx = (craft->getLocation().getX() + craft->getVelocity().getX()*LEAD) - (enemy->getLocation().getX() + enemy->getVelocity().getX()*LEAD);
	double dy = (craft->getLocation().getY() + craft->getVelocity().getY()*LEAD) - (enemy->getLocation().getY() + enemy->getVelocity().getY()*LEAD);
	double dist = sqrt(dx*dx + dy*dy);

	double angle = 180.0 / PI * atan2(dy , dx) + 180;
	double dangle = angle - craft->getAngle();

	if( dangle > 180.0)
	  dangle -= 360.0;
	if( dangle < -180.0)
	  dangle += 360.0;

	if(dist > AVOID_DIST)
	{
	  if( dangle < -ROTATION_DIFF)
	    craft->rotateRight();
	  else if( dangle > ROTATION_DIFF)
	    craft->rotateLeft();
	}
	else
	{
	  if( dangle > -AVOID_DIFF)
	    craft->rotateRight();
	  else if( dangle < AVOID_DIFF)
	    craft->rotateLeft();
	}

	if( (dist > SHOOT_DIST && craft->getVelocity().length() < SPEED) || dist < AVOID_DIST)
	  craft->useThruster();
	else 
	{
	  if( rand() < RAND_MAX * SPECIAL_PROB)
	    craft->useSpecial();
	  else
	    craft->fire();
	}
}
