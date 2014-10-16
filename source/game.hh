#ifndef GAME_HH
#define GAME_HH

#include <iostream>
#include <list>
#include "SDL/SDL.h"
#include "sound.hh"

#include "spacevector.hh"
#include "input.hh"

#define SPACECRAFTS 4
#define ASTEROIDS 10
#define GRAVITY 30.0

class SpaceObject;
class Spacecraft;
class Asteroid;
class Planet;
class Ammo;
class Explosion;

class Screen;

/** Class Game is the games main class.
 */

class Game
{

public:

  /** Constructor. It initializes all subsystems.
   */
  Game();

  /** Destructor. It frees everything created in game.
   */
  ~Game();

  /** Beginning menu
   * @return false if game should end
   */
  bool menu();

  /** Games main loop
   */
  void play();

  /** 
   * @return a list containing all objects in the game
   */
  std::list<SpaceObject *> getSpaceObjects();
	
  /**
   * @return a list containing the spacecrafts in the game
   */
  std::list<Spacecraft *> getSpacecrafts();
	
  /** 
   * @return List of explosions in space. Needed by Screen for drawing them. 
   */
  std::list<Explosion *> &getExplosions();


  /** adds new ammo
   * @param ammo ammo to be added
   */
  void addAmmo( Ammo *ammo);

  /** deletes ammo
   * @param ammo ammo to be deleted
   */
  void removeAmmo( Ammo *ammo);

  /** adds new spacecraft
   * @param spacecraft to be added
   */ 
  void addSpacecraft( Spacecraft *spacecraft);

  /** deletes spacecraft
   * @param spacecraft to be deleted
   */  
  void removeSpacecraft( Spacecraft *spacecraft);
  
  /** adds new planet
   * @param planet planet to be added
   */  
  void addPlanet( Planet *planet);

 /** deletes planet
   * @param planet planet to be deleted
   */ 
  void removePlanet( Planet *planet);
  
  /** adds new asteroid
   * @param asteroid asteroid to be added
   */  
  void addAsteroid( Asteroid *asteroid);

  /** deletes asteroid
   * @param asteroid asteroid to be deleted
   */ 
  void removeAsteroid( Asteroid *asteroid);
	
  /** adds new explosion
   * @param explosion explosion to be added
   */
  void addExplosion( Explosion *explosion);
  
  /** deletes explosion
   * @param explosion explosion to be deleted
   */
  void removeExplosion( Explosion *explosion);

  /**
   * @return the soundsystem
   */
  Sound *getSound();

  /** moves vector near to origo
   * @param vector vector to move
   */
  void vectorToOrigo(SpaceVector &vector);
  
  /** moves vector near to origo another vector
   * @param vector1 vector to move
   * @param vector2 vector near to which should be moved
   */ 
  void vectorToVector(SpaceVector &vector1, const SpaceVector &vector2);
  
  /**
   * @return the size of space
   */
  SpaceVector getSize();

  /** checks collision between two spaceObjects
   * @param object1 first object 
   * @param object2 second object
   **/
  void checkCollision( SpaceObject &object1, SpaceObject &object2);
  
  /** checks if a object does collide with some other object
   * @param object object 
   * @return true if the obect collieds with some other object
   */
  bool checkCollisionAll( SpaceObject &object);

  /** Calculates and adds gravity from planets to all other objects
   */
  void calcGravity();
  
private:

  /** Size of the space. */
  SpaceVector size;

  /** are the spacehips controlled by humands or cyborgs. */
  bool humanControl1;
  bool humanControl2;  

  /** Subsystems. */
  Input *input;  
  Screen *screen;
  Sound *sound;
  AI *ai;

  /** Spacecrafts. */
  std::list<Spacecraft *> spacecrafts;

  /** Planets. */
  std::list<Planet *> planets;

  /** Ammos. */
  std::list<Ammo *> ammos;

  /** Asteroids. */
  std::list<Asteroid *> asteroids;
	
  /** Explosions. */
  std::list<Explosion *> explosions;

};

#endif
