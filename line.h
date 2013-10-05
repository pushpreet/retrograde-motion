#include "cartesian.h"

/*
	ID Description: 		Implementation of class line
							Written by Pushpreet on 05/10/2013
	
	Version:				- 1.0.0

	Features:				- stores the line in the form of y = mx + c, where m is the slope and c is the y-intercept
							- includes method(s) to form a line through two point form
							- includes method(s) to calculate the point of intersection of two lines
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: math.h
							Used In: 	NULL

*/

class line
{
	private:
		double slope;								// y = mx + c, where m is the slope
		double yIntercept;							// and c is the y-intercept

	public:
		// Write methods
		void setSlope( double slp );				// set slope of the line equal to the parameter slp
		void setIntercept( double intercept );		// set y-intercept of the line equal to the parameter intercept

		// Read methods
		double getSlope( );							// returns the slope of the line
		double getIntercept( );						// returns the y-interxcept of the line

		// Other methods
		line twoPointForm( double x1, double x2, double y1, double y2 );
		cartesian getIntersection( line lineOne, line lineTwo );

		// Constructors(s)
		line( );
};

/*
	Changelog:
	
	06/10/2013
		- 01:16 added implementation for all the methods
	
*/

// implemetation of constructor for class line
line :: line( )
{
	slope = 0.0;
	yIntercept = 0.0;
}

/*
	*********************************
	   Definition of write methods
	*********************************
*/

void line :: setSlope( double slp )
{
	slope = slp;
}

void line :: setIntercept( double intercept )
{
	yIntercept = intercept;
}

/*
	*********************************
	   Definition of read methods
	*********************************
*/

double line :: getSlope( )
{
	return slope;
}

double line :: getIntercept( )
{
	return yIntercept;
}

/*
	*********************************
      Definition of other methods
	*********************************
*/

line line :: twoPointForm( double x1, double x2, double y1, double y2)					// takes two points and returns a line passing through those points
{
	slope = ( y2 - y1 ) / ( x2 - x1 );													// m = ( y2 - y1 ) / ( x2 - x1 )
	yIntercept = y1 - ( x1 * slope );													// c = y1 - ( m * x1 )
	
	return *this;
}

cartesian line :: getIntersection( line lineOne, line lineTwo )							// takes two lines and returns their point of intersection
{
	cartesian point;																										// if the lines are y = ax + c
																															// and y = bx + d, then
	point.x = ( lineTwo.getIntercept( ) - lineOne.getIntercept( ) ) / ( lineOne.getSlope( ) - lineTwo.getSlope( ) );		// x = ( d - c ) / ( a - d )
	point.y = ( lineOne.getSlope( ) * point.x ) + lineOne.getIntercept( );													// y = a * ( d - c ) / ( a - d ) + c

	return point;
}