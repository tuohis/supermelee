#ifndef SCREEN_HH
#define SCREEN_HH

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <GL/gl.h>
//#include "game.hh"
#include "spaceobject.hh"
#include "spacecraft.hh"
#include "spacevector.hh"
#include <iostream>
#include <list>

#define STARS 400
#define MAXZOOM 0.02
#define SPACE_SIZEX 1000
#define SPACE_SIZEY 1000

#define SPACESHIP1_TEXTURE_ID 1
#define SPACESHIP1_TEXTURE_NAME "graphics/ship1_s.png"
#define SPACESHIP2_TEXTURE_ID 2
#define SPACESHIP2_TEXTURE_NAME "graphics/ship2_s.png"
#define SPACESHIP3_TEXTURE_ID 3
#define SPACESHIP3_TEXTURE_NAME "graphics/ship3_s.png"
#define SPACESHIP4_TEXTURE_ID 4
#define SPACESHIP4_TEXTURE_NAME "graphics/ship4_s.png"

#define AMMO1_TEXTURE_ID 10
#define AMMO1_TEXTURE_NAME "graphics/ammo1.png"
#define AMMO2_TEXTURE_ID 11
#define AMMO2_TEXTURE_NAME "graphics/missile_s.png"
#define AMMO3_TEXTURE_ID 12
#define AMMO3_TEXTURE_NAME "graphics/ammo2.png"

#define ASTEROID1_TEXTURE_ID 20
#define ASTEROID1_TEXTURE_NAME "graphics/meteor.png"
#define ASTEROID2_TEXTURE_ID 21
#define ASTEROID2_TEXTURE_NAME "graphics/meteor.png"

#define PLANET1_TEXTURE_ID 100
#define PLANET1_TEXTURE_NAME "graphics/planet.png"

#define EXPLOSION_TEXTURE_NAME "graphics/explosion.png"

#define GREEN_DOT_TEXTURE_ID 101
#define GREEN_DOT_TEXTURE_NAME "graphics/greendot.png"
#define RED_DOT_TEXTURE_ID 102
#define RED_DOT_TEXTURE_NAME "graphics/reddot.png"
#define CREW_BATT_TEXTURE_ID 103
#define CREW_BATT_TEXTURE_NAME "graphics/crewbatt.png"
#define HUMAN_CYBORG_TEXTURE_ID 104
#define HUMAN_CYBORG_TEXTURE_NAME "graphics/humancyborg.png"
#define BATTLE_TEXTURE_ID 105
#define BATTLE_TEXTURE_NAME "graphics/battle.png"



class Explosion;
class Game;

class Screen
{

public:

  /** Sets up Screen. 
   * initializes openGL and loads textures
   * @param width width of screen
   * @param height height of screen
   * @param game Game-object
   */
  Screen( int width, int height, Game *game);

  /** frees surface
  */
  ~Screen();

  /** Draws every object in game
   */
  void draw(std::list<SpaceObject *> objects, std::list<Spacecraft *> spacecrafts);

  /** Draws the start menu.
  * @param select1 spacecraft that is selected for player 1
  * @param select2 spacecraft that is selected for player 2
  * @param humanControl1 true if spacecraft 1 is controlled by human
  * @param humanControl2 true if spacecraft 2 is controlled by human
  */
  void drawMenu( int select1, int select2,  bool humanControl1, bool humanControl2);

  /** Loads a texture.
   * Image must have height and width a power of two.
   * @param name name of the texture
   * @param id id of the texture
   */
  void loadTexture( char *name, int id);
  
  /** Draws a star on screen
   * @param x x-coordinate of star
   * @param y y-coordinate of star
   * @param zoom how much is zoomed
   */
  void drawStar(double x, double y, double zoom);

  /** draws the infobox of a spacecraft
   * @param spacecraft the spacecraft
   */
  void drawInfo(Spacecraft *spacecraft);

  /** 
   * @return the location of screen
   */
  SpaceVector getLocation();

private:
  
  /** the game */
  Game *game;

  /** size of screen */
  int width, height;

  /** location of screen */
  SpaceVector location;

  /** screen surface */
  SDL_Surface *screen;

  /** location of stars */
  SpaceVector stars[STARS];  
  
};

#endif
