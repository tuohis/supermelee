#include "spaceobject.hh"
#include "spacevector.hh"
class Game;

/** Explosion class is for drawing explosions when an object is violently 
	* destroyed. Its deriving from SpaceObject is because it simplifies the 
	* drawing procedure. */
class Explosion : public SpaceObject {
public:
	/** Constructor takes three parameters:
		* @param size The size of the explosion. Normally the size of exploding object.
		* @param location The location of the explosion, from the exploding object as well.
		* @param game Pointer to the Game object. */
	Explosion(double size, SpaceVector const &location, Game *game);
	
	/** Destructor. */
	~Explosion();
	
	/** This method has no other function except killing the object after a delay. */
	void move(double timestep);

private:
	/** The time the explosion is shown on screen in seconds. */
	double lifetime;  
};
