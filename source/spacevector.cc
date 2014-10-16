#include "spacevector.hh"
#include <math.h>

#define PI 3.1415926


/** Constructors */
SpaceVector::SpaceVector() : x(0), y(0) {}
SpaceVector::SpaceVector(double x, double y) : x(x), y(y) {}
SpaceVector::SpaceVector(double length, double angle, int a) : 
					x(length*cos(angle/180*PI)), y(length*sin(angle/180*PI)) {}


SpaceVector::SpaceVector(SpaceVector const &vector) : x(vector.getX()), y(vector.getY()) {}

/** Vector addition  */
SpaceVector const &SpaceVector::add(SpaceVector const &vector) {
	this->x += vector.getX();
	this->y += vector.getY();
	return *this;
}

SpaceVector const &SpaceVector::add(double x, double y) {
	this->x += x;
	this->y += y;
	return *this;
}

void SpaceVector::operator+=(SpaceVector const &vector)
{
	this->add(vector);
}

/** Vector subtraction */
SpaceVector const &SpaceVector::subtract(SpaceVector const &vector) {
	this->x -= vector.getX();
	this->y -= vector.getY();
	return *this;
}
	
SpaceVector const &SpaceVector::subtract(double x, double y) {
	this->x -= x;
	this->y -= y;
	return *this;
}

void SpaceVector::operator-=(SpaceVector const &vector)
{
	this->subtract(vector);
}

/** Dot product */
double SpaceVector::dproduct(SpaceVector const &vector) const
{
	return ( this->x * vector.getX() + this->y * vector.getY() );
	
}

/** Scalar product */
SpaceVector &SpaceVector::operator*=(double a)
{
	this->x *= a;
	this->y *= a;
	return *this;
}



/** Unit vector */
SpaceVector SpaceVector::unit() const
{
	double l = this->length();
	SpaceVector unitvector(this->x / l, this->y / l);
	return unitvector;

}

/** Vector length */
double SpaceVector::length() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

/** Vector angle */
double SpaceVector::angle() const
{
	double angle = 180.0 / PI * atan2(this->y, this->x);
	// if (angle < 0)
		// angle += 360;
	return angle;
}

/** Setting parameters */
void SpaceVector::set(double x, double y)
{
	this->x=x;
	this->y=y;
}

void SpaceVector::setX(double x)
{
	this->x=x;
}

void SpaceVector::setY(double y)
{
	this->y=y;
}

/** Assignment operator */
SpaceVector const &SpaceVector::operator=(SpaceVector const &vector)
{
	this->set(vector.getX(), vector.getY());
	return *this;
}

/** Accessing parameters */
double SpaceVector::getX() const
{
	return this->x;
}

double SpaceVector::getY() const
{
	return this->y;
}

/** comparison */
bool SpaceVector::operator==(SpaceVector const &vector) const
{
	return ( this->x == vector.getX() && this->y == vector.getY() );
}

/** + and - operators */
SpaceVector operator+(SpaceVector const &vector1, SpaceVector const &vector2)
{
	SpaceVector v(vector1);
	v.add(vector2);
	return v;
}

SpaceVector operator-(SpaceVector const &vector1, SpaceVector const &vector2)
{
	SpaceVector v(vector1);
	v.subtract(vector2);
	return v;
}


/** Unary negation */
SpaceVector operator-(SpaceVector const &vector)
{
	SpaceVector ret(-(vector.getX()), -(vector.getY()));
	return ret;
}

/** Scalar product */
SpaceVector operator*(double a, SpaceVector const &vector)
{
	SpaceVector ret(vector);
	ret.set(ret.getX()*a, ret.getY()*a);
	return ret;
}
