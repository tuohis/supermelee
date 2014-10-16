#include "game.hh"
#include "spaceobject.hh"
#include "spacecraft.hh"
#include "ammo.hh"
#include "asteroid.hh"
#include "explosion.hh"
#include "planet.hh"
#include "screen.hh"

#define FPS 60.0
#define WINNER_FRAMES 120

Game::Game()
{
  //init SDL

  if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) 
  {
    std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  this->size = SpaceVector( SPACE_SIZEX, SPACE_SIZEY );

  this->ai = new AI();

  //! creates Input-object
  this->input = new Input(this->ai);
                          
  //! creates Screen object
  this->screen = new Screen(640, 480, this);  

  this->sound = new Sound();
}


Game::~Game() 
{
  
  delete( this->ai);
  delete( this->screen);
  delete( this->input);

  //free all space objects
  std::list<SpaceObject *> list = this->getSpaceObjects();
  for(  std::list<SpaceObject *>::iterator it = list.begin(); it != list.end(); it++)
    delete( *it );

  SDL_Quit();
}  


bool Game::menu()
{
  bool quit = false;
  bool startGame = false;

  //which spacecrafts the players have selected
  int select1 = 0;
  int select2 = 0;

  //are the spacehips controlled by humands or cyborgs
  this->humanControl1 = true;
  this->humanControl2 = true;  

	sound->playMusic(1);	

  while( !quit && !startGame)
  {
    SDL_Event event; 
    while(SDL_PollEvent(&event))
    {  
      if(event.type == SDL_MOUSEBUTTONDOWN) 
      {
	int x = event.button.x;
	int y = event.button.y;
	if( y >= 88 && y < 152 && x >= 320 - 32 * SPACECRAFTS && x < 320 + 32 * SPACECRAFTS)
	  select1 = (x - (320 - 32 * SPACECRAFTS)) / 64;
	if( y >= 328 && y < 392 && x >= 320 - 32 * SPACECRAFTS && x < 320 + 32 * SPACECRAFTS)
	  select2 = (x - (320 - 32 * SPACECRAFTS)) / 64;

	if( x >= 480)
	{
	  if( y < 120)
	    humanControl1 = !humanControl1;
	  else if( y >= 360)
	    humanControl2 = !humanControl2;
	  else
	    startGame = true;
	}
      }
      else if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
	quit = true;
      else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	startGame = true;	      
    }

    this->screen->drawMenu(select1, select2, humanControl1, humanControl2);
  }

  //delete old spacecrafts
  for( std::list<Spacecraft *>::iterator it= this->spacecrafts.begin();it != this->spacecrafts.end(); it++)
    delete( *it);

  this->spacecrafts.clear();    

  // create the spacecrafts
  this->spacecrafts.push_back( new Spacecraft( select1+1, SpaceVector( 0.0, 0.0), this ) );
  this->spacecrafts.push_back( new Spacecraft( select2+1, SpaceVector( 200.0, 200.0), this ) );

  return quit;
}


void Game::play() 
{
  //add one planet
  this->planets.push_back( new Planet( PLANET1_ID, SpaceVector( 400.0, 400.0), this ) );

  while ( !this->menu() )
  {
    //delete old asteroids
    while( this->asteroids.size() > 0)    
      this->removeAsteroid( this->asteroids.front() );    
    
    bool quit = false;

    //sound->playEffect(1);	
    sound->playMusic(2);
    
    int winnerFrames = WINNER_FRAMES;

    //! main loop
    while( !quit ) 
    {

      Uint32 ticks = SDL_GetTicks();
      
      //if there are not enough asteroids, add one 
      if( this->asteroids.size() < ASTEROIDS)
      {
	//asteroid is added outside of screen
	double x = this->screen->getLocation().getX()+ SPACE_SIZEX/2.0;
	double y = this->screen->getLocation().getY()+ SPACE_SIZEY/2.0;

	Asteroid *asteroid = new Asteroid( ASTEROID1_ID, SpaceVector(x,y), this);
	if( !this->checkCollisionAll( *((SpaceObject *) asteroid ))  )
	  this->asteroids.push_back( asteroid );
	else
	  delete( asteroid );
      }
 
      // read input
      quit = this->input->readInput(this->spacecrafts.front(), this->spacecrafts.back(), humanControl1, humanControl2) || winnerFrames < 0;
      
      //add gravity
      this->calcGravity();

      std::list<SpaceObject *> list = this->getSpaceObjects();
      
      // move objects
      for( std::list<SpaceObject *>::iterator it= list.begin(); it != list.end(); it++)
	(*it)->move( 1.0/ FPS );
      	
	// move explosions
	std::list<Explosion *> list2 = this->getExplosions();
      for( std::list<Explosion *>::iterator it= list2.begin(); it != list2.end(); it++)
	(*it)->move( 1.0/ FPS );

      //check collisions
      list = this->getSpaceObjects();

      for( std::list<SpaceObject *>::iterator it1= list.begin(); it1 != list.end(); it1++)
	for( std::list<SpaceObject *>::iterator it2= it1; it2 != list.end(); it2++)
	  if( *it1 != *it2) 
	    this->checkCollision( *(*it1), *(*it2));
      
      //! draw screen
      this->screen->draw( this->getSpaceObjects(), this->spacecrafts );
      
      if( this->spacecrafts.front() == NULL || this->spacecrafts.back() == NULL)
	winnerFrames--;

      //! wait until 1000/ FPS ms has elapsed
      if( SDL_GetTicks() - ticks < 1000/FPS )
	SDL_Delay( (int)(1000/FPS) - (SDL_GetTicks() - ticks) );
      
      /*
	while( SDL_GetTicks() - ticks < 1000/FPS ) ;
      */
    }
  }
}


std::list<SpaceObject *> Game::getSpaceObjects()
{
  std::list<SpaceObject *> list;
    
  for( std::list<Spacecraft *>::iterator it= this->spacecrafts.begin();it != this->spacecrafts.end(); it++)
    if( *it != NULL)  //deleted spacecrafts are not added
      list.push_back( (Spacecraft *) *it);

  for( std::list<Ammo *>::iterator it= this->ammos.begin(); it != this->ammos.end(); it++)
    list.push_back( (Ammo *) *it);
	
	for( std::list<Asteroid *>::iterator it= this->asteroids.begin(); it != this->asteroids.end(); it++)
    list.push_back( (Asteroid *) *it);
	
	for( std::list<Planet *>::iterator it= this->planets.begin(); it != this->planets.end(); it++)
    list.push_back( (Planet *) *it);
  

  return list;
}


SpaceVector Game::getSize()
{
  return this->size;
}


void Game::vectorToOrigo(SpaceVector &vector)
{ 
  this->vectorToVector( vector, SpaceVector(0.0, 0.0));
}


void Game::vectorToVector(SpaceVector &vector1, const SpaceVector &vector2)
{
  vector1.subtract( vector2 );
  double sizeX = this->getSize().getX()/2.0;
  double sizeY = this->getSize().getY()/2.0;

  while( vector1.getX() < -sizeX )
    vector1.setX( vector1.getX() + this->getSize().getX() );

   while( vector1.getX() > sizeX )
    vector1.setX( vector1.getX() - this->getSize().getX() );

   while( vector1.getY() < -sizeY )
     vector1.setY( vector1.getY() + this->getSize().getY() );
   
   while( vector1.getY() > sizeY )
    vector1.setY( vector1.getY() - this->getSize().getY() );

   vector1.add( vector2 );
}

void Game::calcGravity()
{  
  std::list<SpaceObject *> objects = this->getSpaceObjects();

  for( std::list<Planet *>::iterator it1 = this->planets.begin(); it1 != this->planets.end(); it1++)
    for( std::list<SpaceObject *>::iterator it2= objects.begin(); it2 != objects.end(); it2++)	
      if( *it1 != *it2)
      {
	this->vectorToVector( (*it1)->getLocation(), (*it2)->getLocation() );
	SpaceVector d = (*it1)->getLocation() - (*it2)->getLocation();
	double length = d.length();
	d = d.unit();	
	(*it2)->addForce( (GRAVITY *(*it1)->getMass()*(*it2)->getMass() / ( length*length ))*d);
      }
}

bool Game::checkCollisionAll( SpaceObject &object)
{ 
  std::list<SpaceObject *> list = this->getSpaceObjects();
  for( std::list<SpaceObject *>::iterator it= list.begin(); it != list.end(); it++)	
    if( *it != &object)
    {
      this->vectorToVector( object.getLocation(), (*it)->getLocation() );
      double dpx = (*it)->getLocation().getX() -object.getLocation().getX();
      double dpy = (*it)->getLocation().getY() -object.getLocation().getY();  
      
      if( ( dpx*dpx + dpy*dpy - (object.getSize() + (*it)->getSize())*(object.getSize() + (*it)->getSize())) < 0.0)
	return true;  //collision
    } 
 
  //no collision
  return false;
}
  

void Game::checkCollision( SpaceObject &object1, SpaceObject &object2)
{
  //object1 must be moved near to object2  
  this->vectorToVector( object1.getLocation(), object2.getLocation() );
  
  double dpx = object2.getLocation().getX() -object1.getLocation().getX();
  double dpy = object2.getLocation().getY() -object1.getLocation().getY();  

  if( ( dpx*dpx + dpy*dpy - (object1.getSize() + object2.getSize())*(object1.getSize() + object2.getSize())) >= 0.0)
    return; //NO Collision  

  double vx1 = object1.getVelocity().getX();
  double vy1 = object1.getVelocity().getY();
  double vx2 = object2.getVelocity().getX();
  double vy2 = object2.getVelocity().getY();
  double dvx = vx2 -vx1;
  double dvy = vy2 -vy1;
  double m1 = object1.getMass();
  double m2 = object2.getMass();

 
  //Calculate how much objects have to move "back in time"

  double a = dvx*dvx + dvy*dvy;
  double b = -2.0*( dpx*dvx + dpy*dvy );
  double c = dpx*dpx + dpy*dpy - (object1.getSize()+object2.getSize()) * (object1.getSize()+object2.getSize() );

  //check if it is possible
  if( a != 0.0 && (b*b - 4.0*a*c) >= 0.0)  
  {    
    double t = (-b + sqrt( b*b - 4.0*a*c)) / (2.0  * a);

    // move objects "back in time" to place where they don't hit
    object1.getLocation().subtract( t* object1.getVelocity());
    object2.getLocation().subtract( t* object2.getVelocity());
  }
  else
  {
    std::cout << "Collision error" << std::endl;
  }
 
  //calculate new speeds for objects
  //collisions are fully elastic, so both momentum and motion energy are preserved
  
  dpx = object2.getLocation().getX() -object1.getLocation().getX();
  dpy = object2.getLocation().getY() -object1.getLocation().getY();  

  double div = 1.0 / ((m1+m2)*(dpx*dpx+dpy*dpy));

  /*
  double ux1 = ( m1*vx1*(dpx*dpx+dpy*dpy)+m2*(vx1*(dpx*dpx-dpy*dpy)+2.0*vx2*dpx*dpx+2.0*(vy2-vy1)*(dpx*dpy))) * div;
  double uy1 = ( m1*vy1*(dpx*dpx+dpy*dpy)+m2*(vy1*(dpy*dpy-dpx*dpx)+2.0*vy2*dpy*dpy+2.0*(vx2-vx1)*(dpx*dpy))) * div;
  double ux2 = ( m2*vx2*(dpx*dpx+dpy*dpy)+m1*(vx2*(dpx*dpx-dpy*dpy)+2.0*vx1*dpx*dpx+2.0*(vy1-vy2)*(dpx*dpy))) * div;
  double uy2 = ( m2*vy2*(dpx*dpx+dpy*dpy)+m1*(vy2*(dpy*dpy-dpx*dpx)+2.0*vy1*dpy*dpy+2.0*(vx1-vx2)*(dpx*dpy))) * div;
  */

  double ux1 = (-2.0*m2*vy1*dpx*dpy+2.0*m2*dpy*dpx*vy2+(2.0*vx2*dpx*dpx+(-dpx*dpx+dpy*dpy)*vx1)*m2+(dpx*dpx+dpy*dpy)*m1*vx1)*div;
  double uy1 = (((dpx*dpx-dpy*dpy)*m2+(dpx*dpx+dpy*dpy)*m1)*vy1+2.0*vy2*m2*dpy*dpy+(2.0*dpy*vx2*dpx-2.0*dpy*vx1*dpx)*m2)*div;
  double ux2 = (-2.0*m1*vy2*dpx*dpy+2.0*m1*dpy*dpx*vy1+(2.0*vx1*dpx*dpx+(-dpx*dpx+dpy*dpy)*vx2)*m1+(dpx*dpx+dpy*dpy)*m2*vx2)*div;
  double uy2 = (((dpx*dpx-dpy*dpy)*m1+(dpx*dpx+dpy*dpy)*m2)*vy2+2.0*vy1*m1*dpy*dpy+(2.0*dpy*vx1*dpx-2.0*dpy*vx2*dpx)*m1)*div;  

  SpaceVector oldV1 = object1.getVelocity();
  SpaceVector oldV2 = object2.getVelocity();
  SpaceVector u1(ux1, uy1);
  SpaceVector u2(ux2, uy2);
  
  object1.getVelocity( ) = u1;
  object2.getVelocity( ) = u2;
	
  /** Deal damage to the objects. Damage is the sum of 1) the change in object's speed
   * and 2) the damage value of the other object (a ship's damage value is usually
   *	0, ammo's > 0).
   * Even if destroyed, the objects are not deleted until the next frame, so no
   * need to worry about that. Right.
   */
  object1.doDamage(0.02*(oldV1 - u1).length() + object2.getDamage());
  object2.doDamage(0.02*(oldV2 - u2).length() + object1.getDamage());
	
}


void Game::addSpacecraft( Spacecraft *spacecraft)
{
  this->spacecrafts.push_back( spacecraft );
}


void Game::removeSpacecraft( Spacecraft *spacecraft)
{  
  if( this->spacecrafts.front() == spacecraft)
    this->spacecrafts.push_front( NULL );
  else if( this->spacecrafts.back() == spacecraft)
    this->spacecrafts.push_back( NULL );
 
  this->spacecrafts.remove( spacecraft );   

  delete spacecraft;
}    

std::list<Spacecraft *> Game::getSpacecrafts()
{
  return this->spacecrafts;
}

void Game::addAmmo( Ammo *ammo)
{
  this->ammos.push_back( ammo );
}

void Game::removeAmmo( Ammo *ammo)
{
  this->ammos.remove( ammo );
  delete ammo;

}


void Game::addPlanet( Planet *planet)
{
  this->planets.push_back( planet );
}


void Game::removePlanet( Planet *planet)
{
  this->planets.remove( planet );
  delete planet;
}

void Game::addAsteroid( Asteroid *asteroid)
{
  this->asteroids.push_back( asteroid );
}

void Game::removeAsteroid( Asteroid *asteroid)
{
  this->asteroids.remove( asteroid );
  delete asteroid;
}

void Game::addExplosion( Explosion *explosion)
{
  this->explosions.push_back( explosion );
}

void Game::removeExplosion( Explosion *explosion)
{
  this->explosions.remove( explosion );
  delete explosion;
}

std::list<Explosion *> &Game::getExplosions()
{
  return this->explosions;
}

Sound* Game::getSound()
{
return this->sound;
}


int main(  int argc, char *argv[] )
{

  Game *game = new Game();

  game->play();

  delete( game );

  return EXIT_SUCCESS;
}
