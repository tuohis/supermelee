#ifndef SPACEVECTOR_HH
#define SPACEVECTOR_HH

/** Class SpaceVector represents a two-dimensional vector, and stores the
	* information in the x- and y-components. SpaceVector supports some vectorial
	* calculations, such as addition, subtraction, scalar product, dot product, 
	* vector length and angle, and unit vector.
	*/
class SpaceVector {

public:
	/** Constructor */
	SpaceVector();
	/** @param x The x-component.
		* @param y The y-component. */
	SpaceVector(double x, double y);
	/** @param length Vector length.
		* @param angle Vector angle.
		* @param a Used to separate this constructor from the x-y-constructor. */
	SpaceVector(double length, double angle, int a);
	/** Copy constructor. */
	SpaceVector(SpaceVector const &vector);
	
	/** Vector addition.
		* @param vector The vector to be added to *this.
		* @return Reference to *this. */
	SpaceVector const &add(SpaceVector const &vector);
	/** @param x The value to be added to the x-component.
		* @param y The value to be added to the y-component. 
		* @return Reference to *this. */
	SpaceVector const &add(double x, double y);
	/** @param vector The vector to be added to *this. */
	void operator+=(SpaceVector const &vector);
	
	/** Vector subtraction. Works like addition. */
	SpaceVector const &subtract(SpaceVector const &vector);
	SpaceVector const &subtract(double x, double y);
	void operator-=(SpaceVector const &vector);
	
	
	/** @param vector The vector with which the dot product is to be calculated.
		* @return Dot product of vector and *this. */
	double dproduct(SpaceVector const &vector) const;

	/** Scalar product */
	SpaceVector &operator*=(double a);

	/** Unit vector */
	SpaceVector unit() const;

	/** Vector length */
	double length() const;
	
	/** @return Vector angle in degrees, varying from 0 to 359 */
	double angle() const;
	
	/** Setting parameters. Pretty much self-explaining. */
	void set(double x, double y);
	void setX(double x);
	void setY(double y);
	SpaceVector const &operator=(SpaceVector const &vector);
	
	double getX() const;
	double getY() const;
	
	/** comparison */
	bool operator==(SpaceVector const &vector) const;

private:
	/** The fields in which the vector information is stored. */
	double x;
	double y;

};

SpaceVector operator+(SpaceVector const &vector1, SpaceVector const &vector2);
SpaceVector operator-(SpaceVector const &vector1, SpaceVector const &vector2);
SpaceVector operator-(SpaceVector const &vector);

/** Scalar product */
SpaceVector operator*(double a, SpaceVector const &vector);

#endif
