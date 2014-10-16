#include "SDL/SDL.h"
#include "input.hh"
#include "spacecraft.hh"
#include "ai.hh"

Input::Input (AI *ai)
{	
	
	this->ai = ai;
	
	/** player #1 controls */
	this->upup = true;
	this->leftup = true;
	this->rightup = true;
	this->rctrlup = true;
	this->rshiftup = true;

	/** player #2 controls */
	this->eup = true;
	this->sup = true;
	this->fup = true;
	this->oneup = true;
	this->qup = true;

}

bool Input::readInput (Spacecraft  *ship1, Spacecraft  *ship2, bool humanControl1, bool humanControl2)
{
  this->escapedown = false;


/** Poll SDL key event for any keystrokes. */
while (SDL_PollEvent(&this->keyevent))   
{
  if (this->keyevent.type == SDL_KEYDOWN)
  {
    switch(this->keyevent.key.keysym.sym){
      
	/** player #1 controls: */
	case SDLK_LEFT:
        	this->leftup = false;
		break;
      	case SDLK_RIGHT:
        	this->rightup = false;
		break;
      	case SDLK_UP:
        	this->upup = false;
		break;
      	case SDLK_RCTRL:
		this->rctrlup = false;
		break;
      	case SDLK_RSHIFT:
		this->rshiftup = false;
		break;

	/** player #2 controls */
	case SDLK_e:
		this->eup = false;
		break;
	case SDLK_s:
		this->sup = false;
		break;
	case SDLK_f:
		this->fup = false;
		break;
	case SDLK_1:
		this->oneup = false;
		break;
	case SDLK_q:
		this->qup = false;
		break;
	
	/** escape being pressed */
	case SDLK_ESCAPE:
		this->escapedown = true;
		return escapedown;

	default:
        	break;
    }
  }
  if (this->keyevent.type == SDL_KEYUP)
  {
    switch(this->keyevent.key.keysym.sym){
      
	/** player #2 controls */
	case SDLK_LEFT:
        	this->leftup = true;
		break;
      	case SDLK_RIGHT:
        	this->rightup = true;
		break;
      	case SDLK_UP:
        	this->upup = true;
		break;
      	case SDLK_RCTRL:
		this->rctrlup = true;
		break;
      	case SDLK_RSHIFT:
		this->rshiftup = true;
		break;

	/** player #2 controls */
	case SDLK_e:
		this->eup = true;
		break;
	case SDLK_s:
		this->sup = true;
		break;
	case SDLK_f:
		this->fup = true;
		break;
	case SDLK_1:
		this->oneup = true;
		break;
	case SDLK_q:
		this->qup = true;
		break;
    
	default:
			break;

	}
  }

}
  /** Call member functions of player #1 */
 if(humanControl1 && ship1 != NULL)
 { 
   if (this->upup == false)
     ship1->useThruster();	  
   if (this->leftup == false)
     ship1->rotateLeft();
   if (this->rightup == false)
     ship1->rotateRight();
   if (this->rctrlup == false)
     ship1->fire();
   if (this->rshiftup == false)
     ship1->useSpecial();
 }

  /** Call member functions of player #2 */
 if(humanControl2 && ship2 != NULL)
 { 
  if (this->eup == false)
    ship2->useThruster(); 
  if (this->sup == false)
    ship2->rotateLeft();
  if (this->fup == false)
    ship2->rotateRight();
  if (this->oneup == false)
    ship2->useSpecial();
  if (this->qup == false)
    ship2->fire();
 }

/** Use AI for cpu controlled spacecrafts */
if(ship1 != NULL && ship2 != NULL)
{
	/** Use AI for player #1 */
	 if(!humanControl1)
		this->ai->act(ship1,ship2);

	/** Use AI for player #2 */
	if(!humanControl2)
		this->ai->act(ship2,ship1);
}


return escapedown;


}
