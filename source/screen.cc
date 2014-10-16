#include "screen.hh"
#include "game.hh"
#include "explosion.hh"

Screen::Screen( int width, int height, Game *game)
{ 
  this->width = width;
  this->height = height;  
  this->game = game;

  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
 
  this->screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL ) ;
  if( this->screen == NULL)
  {
    std::cout << "error setting video mode" << std::endl;
  }

  //set the clear color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  
  //set matrix mode
  //glMatrixMode( GL_MODELVIEW );

  // enable alpha testing
  //glEnable(GL_ALPHA_TEST);
  //glAlphaFunc(GL_GREATER, 0.1);
  // enable blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //load textures
  this->loadTexture( SPACESHIP1_TEXTURE_NAME, SPACESHIP1_TEXTURE_ID);
  this->loadTexture( SPACESHIP2_TEXTURE_NAME, SPACESHIP2_TEXTURE_ID);
  this->loadTexture( SPACESHIP3_TEXTURE_NAME, SPACESHIP3_TEXTURE_ID);
  this->loadTexture( SPACESHIP4_TEXTURE_NAME, SPACESHIP4_TEXTURE_ID);

  this->loadTexture(AMMO1_TEXTURE_NAME, AMMO1_TEXTURE_ID);
  this->loadTexture(AMMO2_TEXTURE_NAME, AMMO2_TEXTURE_ID);
  this->loadTexture(AMMO3_TEXTURE_NAME, AMMO3_TEXTURE_ID);

  this->loadTexture(ASTEROID1_TEXTURE_NAME, ASTEROID1_TEXTURE_ID);
  this->loadTexture(ASTEROID2_TEXTURE_NAME, ASTEROID2_TEXTURE_ID);

  this->loadTexture(PLANET1_TEXTURE_NAME, PLANET1_TEXTURE_ID);
	
	this->loadTexture(EXPLOSION_TEXTURE_NAME, EXPLOSION_ID);

  this->loadTexture( GREEN_DOT_TEXTURE_NAME, GREEN_DOT_TEXTURE_ID);
  this->loadTexture( RED_DOT_TEXTURE_NAME, RED_DOT_TEXTURE_ID);
  this->loadTexture( CREW_BATT_TEXTURE_NAME, CREW_BATT_TEXTURE_ID);
  this->loadTexture( HUMAN_CYBORG_TEXTURE_NAME, HUMAN_CYBORG_TEXTURE_ID);
  this->loadTexture( BATTLE_TEXTURE_NAME, BATTLE_TEXTURE_ID);

  //create stars
  for(int i = 0; i < STARS; i++)
    this->stars[i] = SpaceVector( rand() % (int)game->getSize().getX(), rand()% (int)game->getSize().getY() );

}

Screen::~Screen()
{
  SDL_FreeSurface( this->screen);
}

double min( double v1, double v2)
{
  if (v1 < v2)
    return v1;
  else 
    return v2;
}

double max( double v1, double v2)
{
  if (v1 > v2)
    return v1;
  else 
    return v2;
}

//draws a quad with color r,g,b
void drawQuad( double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, 
	       double cr, double cg, double cb)
{
  glColor3f( cr, cg, cb);
  glBegin(GL_QUADS);    
  glVertex2f( x1, y1);
  glVertex2f( x2, y2);
  glVertex2f( x3, y3);
  glVertex2f( x4, y4);  
  glEnd();
}


//draws a transparent quad with a texture
void drawTransparentQuad( double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,  //vertex coordinates
		       double u1, double v1, double u2, double v2, double u3, double v3, double u4, double v4,  //texture coordinates
			   int textureID, double alpha)  //texture and alpha value
{
  glColor4f( 1.0, 1.0, 1.0, alpha);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBindTexture( GL_TEXTURE_2D, textureID);

  glBegin(GL_QUADS);
  glTexCoord2f( u1, v1);
  glVertex2f( x1, y1);
  glTexCoord2f( u2, v2);
  glVertex2f( x2, y2);
  glTexCoord2f( u3, v3);
  glVertex2f( x3, y3);
  glTexCoord2f( u4, v4);
  glVertex2f( x4, y4);  
  glEnd();
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}

//draws a quad with a texture
void drawTexturedQuad( double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,  //vertex coordinates
		       double u1, double v1, double u2, double v2, double u3, double v3, double u4, double v4,  //texture coordinates
		       int textureID)
{
  drawTransparentQuad( x1, y1, x2, y2, x3, y3, x4, y4, u1, v1, u2, v2, u3, v3, u4, v4, textureID, 1.0);
 
}

void Screen::drawInfo(Spacecraft *spacecraft)
{
  //draws background
  drawQuad( -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 0.4, 0.4, 0.4);

  //has spacecraft been deleted?
  if( spacecraft == NULL)
    return;

  int crew1 = (int) (spacecraft->getCrew()+1)/2;     //left
  int crew2 = (int) spacecraft->getCrew()/2;         //right
  int maxCrew = (int) (spacecraft->getMaxCrew()+1)/2;//maxium
  int energy1 = (int) (spacecraft->getEnergy()+1)/2;     //right
  int energy2 = (int) spacecraft->getEnergy()/2;         //left
  int maxEnergy = (int) (spacecraft->getMaxEnergy()+1)/2;//maxium
  
  //draws crew indicator
  drawQuad( -0.8, -0.8, -0.6, -0.8, 
	    -0.6, -0.8 + 2.083*(float) maxCrew /ABSOLUTE_MAX_CREW, -0.8, -0.8 + 2.083*(float) maxCrew /ABSOLUTE_MAX_CREW,
	    0.0, 0.0, 0.0);  

  
  drawTexturedQuad( -0.8, -0.8, -0.7, -0.8,
		    -0.7, -0.8 + 2.083*crew1 / ABSOLUTE_MAX_CREW, -0.8, -0.8 + 2.083*crew1 / ABSOLUTE_MAX_CREW, 
		    0.0, 0.0, 1.0, 0.0, 1.0, crew1, 0.0, crew1,    
		    GREEN_DOT_TEXTURE_ID );
  
  drawTexturedQuad( -0.7, -0.8, -0.6, -0.8,
		    -0.6, -0.8 + 2.083*crew2 / ABSOLUTE_MAX_CREW, -0.7, -0.8 + 2.083*crew2 / ABSOLUTE_MAX_CREW, 
		    0.0, 0.0, 1.0, 0.0, 1.0, crew2, 0.0, crew2,    
		    GREEN_DOT_TEXTURE_ID );  


  //draws energy indicator
  drawQuad( 0.8, -0.8, 0.6, -0.8, 
	    0.6, -0.8 + 2.083*(float) maxEnergy /ABSOLUTE_MAX_ENERGY, 0.8, -0.8 + 2.083*(float) maxEnergy /ABSOLUTE_MAX_ENERGY,
	    0.0, 0.0, 0.0);  

  drawTexturedQuad( 0.8, -0.8, 0.7, -0.8,
		    0.7, -0.8 + 2.083*energy1 / ABSOLUTE_MAX_ENERGY, 0.8, -0.8 + 2.083*energy1 / ABSOLUTE_MAX_ENERGY, 
		    0.0, 0.0, 1.0, 0.0, 1.0, energy1, 0.0, energy1,    
		    RED_DOT_TEXTURE_ID );
  
  drawTexturedQuad( 0.7, -0.8, 0.6, -0.8,
		    0.6, -0.8 + 2.083*energy2 / ABSOLUTE_MAX_ENERGY, 0.7, -0.8 + 2.083*energy2 / ABSOLUTE_MAX_ENERGY, 
		    0.0, 0.0, 1.0, 0.0, 1.0, energy2, 0.0, energy2,    
		    RED_DOT_TEXTURE_ID );  
 

  //draws spacecraft images
  drawTexturedQuad (-0.3, -0.2,  0.3, -0.2, 0.3, 0.2, -0.3, 0.2,
		    0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 
		    spacecraft->getID());
 
  // "CREW" and "BATT" texts
  drawTexturedQuad( -1.0, -1.0, -0.4, -1.0, -0.4, -0.8, -1.0, -0.8,
		    0.0, 0.5, 1.0, 0.5, 1.0, 0.0, 0.0, 0.0,
		    CREW_BATT_TEXTURE_ID);

  drawTexturedQuad( 0.4, -1.0, 1.0, -1.0, 1.0, -0.8, 0.4, -0.8,
		    0.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 0.5,
		    CREW_BATT_TEXTURE_ID);
}  


void Screen::drawMenu( int select1, int select2, bool humanControl1, bool humanControl2)
{
  // set a square viewport
  glViewport(0, 0, this->width, this->height);

  // clear the window
  glClear(GL_COLOR_BUFFER_BIT);

  //draw selection boxes
  drawQuad( 0.1 * (2*select1 - SPACECRAFTS), 0.5 - 0.133, 0.1 * (2*select1 - SPACECRAFTS + 2), 0.5 - 0.133,
	      0.1 * (2*select1 - SPACECRAFTS + 2), 0.5 + 0.133, 0.1 * (2*select1 - SPACECRAFTS), 0.5 + 0.133, 
	      1.0, 1.0, 0.0);

  drawQuad( 0.1 * (2*select2 - SPACECRAFTS), -0.5 - 0.133, 0.1 * (2*select2 - SPACECRAFTS + 2), -0.5 - 0.133,
	      0.1 * (2*select2 - SPACECRAFTS + 2), -0.5 + 0.133, 0.1 * (2*select2 - SPACECRAFTS), -0.5 + 0.133, 
	      1.0, 1.0, 0.0);

  //draw spaceship menu lists
  for(int i = 0; i < SPACECRAFTS; i++)
  {
    drawQuad( 0.1 * (2*i - SPACECRAFTS + 0.125), -0.5 - 0.1166, 0.1 * (2*i - SPACECRAFTS + 1.875), -0.5 - 0.1166,
	      0.1 * (2*i - SPACECRAFTS + 1.875), -0.5 + 0.1166, 0.1 * (2*i - SPACECRAFTS + 0.125), -0.5 + 0.1166, 
	      0.4, 0.4, 0.4);

    drawTexturedQuad( 0.1 * (2*i - SPACECRAFTS + 0.25), -0.5 - 0.1, 0.1 * (2*i - SPACECRAFTS + 1.75), -0.5 - 0.1,
		      0.1 * (2*i - SPACECRAFTS + 1.75), -0.5 + 0.1, 0.1 * (2*i - SPACECRAFTS + 0.25), -0.5 + 0.1, 
		      0, 0, 1.0, 0, 1.0, 1.0, 0, 1.0, 
		      i+1);

    drawQuad( 0.1 * (2*i - SPACECRAFTS + 0.125), 0.5 - 0.1166, 0.1 * (2*i - SPACECRAFTS + 1.875), 0.5 - 0.1166,
	      0.1 * (2*i - SPACECRAFTS + 1.875), 0.5 + 0.1166, 0.1 * (2*i - SPACECRAFTS + 0.125), 0.5 + 0.1166, 
	      0.4, 0.4, 0.4);
    
    drawTexturedQuad( 0.1 * (2*i - SPACECRAFTS + 0.25), 0.5 - 0.1, 0.1 * (2*i - SPACECRAFTS + 1.75), 0.5 - 0.1,
		      0.1 * (2*i - SPACECRAFTS + 1.75), 0.5 + 0.1, 0.1 * (2*i - SPACECRAFTS + 0.25), 0.5 + 0.1, 
		      0, 0, 1.0, 0, 1.0, 1.0, 0, 1.0, 
		      i+1);    
  }

  //draw human/cyborg control
  double y=0.0;
  if( !humanControl1)
    y= 120.0/256.0;

  drawTexturedQuad( 0.5, 1.0, 1.0, 1.0, 1.0, 0.5, 0.5, 0.5,
		    0.1875, 0.03125+y, 0.8125, 0.03125+y, 0.8125, 0.5+y, 0.1875, 0.5+y,
		    HUMAN_CYBORG_TEXTURE_ID);
  y=0.0;
  if( !humanControl2)
    y= 120.0/256.0;

  drawTexturedQuad( 0.5, -0.5, 1.0, -0.5, 1.0, -1.0, 0.5, -1.0,
		    0.1875, 0.03125+y, 0.8125, 0.03125+y, 0.8125, 0.5+y, 0.1875, 0.5+y,
		    HUMAN_CYBORG_TEXTURE_ID);

  //draw BATTLE! box
  drawTexturedQuad( 0.5, 0.5, 1.0, 0.5, 1.0, -0.5, 0.5, -0.5,
		    0.1875, 0.03125, 0.8125, 0.03125, 0.8125, 0.96875, 0.1875, 0.96875,
		    BATTLE_TEXTURE_ID);


  // flush the buffer
  glFlush();
  SDL_GL_SwapBuffers();

}

//! draws everything
void Screen::draw(std::list<SpaceObject *> objects,  std::list<Spacecraft *> spacecrafts)
{
	// Add explosions to objects
	for (std::list<Explosion *>::iterator i = game->getExplosions().begin(); i 
				!= game->getExplosions().end(); i++) {
		objects.push_back(*i);
	}
	
  // set a square viewport
  glViewport(0, 0, this->height, this->height);

  // Clear the window
  glClear(GL_COLOR_BUFFER_BIT);
 
  //set matrix mode
  //glMatrixMode( GL_MODELVIEW );

  //the space ships
  Spacecraft *ship1 = spacecrafts.front();
  Spacecraft *ship2 = spacecrafts.back();

  //location of screen in space
  double screenX = 0.0;
  double screenY = 0.0;
  double zoom = MAXZOOM;

  if( ship1 != NULL && ship2 != NULL)
  {
    // move spacecrafts near to each other
    this->game->vectorToVector( ship1->getLocation(),  ship2->getLocation());    

    //calculate size of screen
    double minX = min( ship1->getLocation().getX() - ship1->getSize(), ship2->getLocation().getX() - ship2->getSize());
    double minY = min( ship1->getLocation().getY() - ship1->getSize(), ship2->getLocation().getY() - ship2->getSize());
    double maxX = max( ship1->getLocation().getX() + ship1->getSize(), ship2->getLocation().getX() + ship2->getSize());
    double maxY = max( ship1->getLocation().getY() + ship1->getSize(), ship2->getLocation().getY() + ship2->getSize());
       
    screenX = (maxX + minX) / 2.0;
    screenY = (maxY + minY) / 2.0;
        
    //zoom of the screen (how much objects are resized)
    zoom = 1.5 / max( maxX - minX, maxY - minY);
    double minzoom = 2.0 / (this->height + 2.0*(ship1->getSize() + ship2->getSize()) );
    
    if( zoom < minzoom )
      zoom = minzoom;

    if( zoom > MAXZOOM)
    zoom = MAXZOOM;
  }
  else if( ship1 != NULL)
  {
    screenX = ship1->getLocation().getX();
    screenY = ship1->getLocation().getY();
  }
  else if( ship2 != NULL)
  {
    screenX = ship2->getLocation().getX();
    screenY = ship2->getLocation().getY();
  }    

  this->location= SpaceVector( screenX, screenY);

  //load identity matrix
  glLoadIdentity();

  //draw stars
  for(int i = 0; i < STARS; i++)
  { 
    //set stars on screen
    this->game->vectorToVector( this->stars[i], this->location);

    this->drawStar( (this->stars[i].getX()-screenX)*zoom, (this->stars[i].getY()-screenY)*zoom, zoom);
  }
  

  //draw every object
  for( std::list<SpaceObject *>::iterator it = objects.begin(); it != objects.end(); it++)
  {    
    //set object on screen
    this->game->vectorToVector( (*it)->getLocation(), this->location);

    //load identity matrix
    glLoadIdentity();

    //scale object
    glScalef( zoom, zoom , 1.0);

    //translate object
    glTranslatef( (*it)->getLocation().getX() -screenX, (*it)->getLocation().getY() -screenY, 0);
    
    //rotate object
    glRotatef( (*it)->getAngle() , 0.0, 0.0 , 1.0);

    //draws the object
    drawTransparentQuad( -(*it)->getSize(), -(*it)->getSize(), (*it)->getSize(), -(*it)->getSize(),
		      (*it)->getSize(), (*it)->getSize(), -(*it)->getSize(), (*it)->getSize(),
		      0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		      (*it)->getID(), (*it)->getTransparency());  
  }

  glLoadIdentity();

  // set a viewport to right side of screen
  glViewport(this->height, 0, this->width - this->height, this->height/2);
  this->drawInfo(ship2);
  
  glViewport(this->height, this->height/2, this->width - this->height, this->height/2);
  this->drawInfo(ship1);

  // Flush the buffer
  glFlush();

  SDL_GL_SwapBuffers();
}

//draws a star on screen
void Screen::drawStar( double x, double y, double zoom)
{
  double light = 4.0*zoom/MAXZOOM;
  
  if( light > 1.0)
  {
    glColor3f( (light-1.0)/ 4.0, (light-1.0)/ 4.0 , 0.0);

    glBegin(GL_POINTS);
    glVertex2f (x, y + 2.0/this->height);
    glVertex2f (x + 2.0/this->height, y);
    glVertex2f (x - 2.0/this->height, y);
    glVertex2f (x, y - 2.0/this->height);
    glEnd();

    light = 1.0;
  }
  glColor3f( light, light , 0.0);
  
  glBegin(GL_POINTS);
  glVertex2f (x, y );
  glEnd();  
}
  
void Screen::loadTexture( char *name, int id)
{

  SDL_Surface *image = IMG_Load ( name );  
  if(image == NULL) 
  {
    std::cout << "Unable to load texture: " << name << std::endl;
    exit(1);
  }
  
  glBindTexture( GL_TEXTURE_2D, id ) ; 
  
  // Prepare the filtering of the texture image 
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ) ;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ) ;
  
  /* Map the alpha surface to the texture */
  glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, image->w, image->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, image->pixels );

  SDL_FreeSurface( image );
}

SpaceVector Screen::getLocation()
{
  return this->location;
}
