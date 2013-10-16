#include "cartesian.h"

/*
	ID Description: 		Implementation of class line
							Written by Pushpreet on 05/10/2013
	
	Version:				- 1.0.1

	Features:				- stores the line in the form of y = mx + c, where m is the slope and c is the y-intercept
							- includes method(s) to form a line through two point form
							- includes method(s) to calculate the point of intersection of two lines
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: cartesian.h
							Used In: 	Project: Retrograde Motion - Main.cpp

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
		line twoPointForm( double x1, double x2, double y1, double y2 );		// takes two points (four doubles) and returns a line passing through those points
		line twoPointForm( cartesian pointOne, cartesian pointTwo );			// takes two cartesians and returns a line passing through them
		cartesian getIntersection( line Line );									// finds the point of intersection between the calling line and the line passed through the parameter and then returns it

		// Constructors(s)
		line( );
		line( double _slope, double _yIntercept );
};

/*
	Changelog:
	
	06/10/2013
		- 01:16 added implementation for all the methods
	16-10-13 
		- 11:25 removed bugs from twoPointForm method
		- 11:33 added an overloaded form of twoPointForm method
	
*/

// implemetation of constructor for class line
line :: line( )
{
	slope = 0.0;
	yIntercept = 0.0;
}

line :: line( double _slope, double _yIntercept )
{
	slope = _slope;
	yIntercept = _yIntercept;
}

/*
	*********************************
	   Definition of write methods
	*********************************
*/

void line :: setSlope( double _slope )
{
	slope = _slope;
}

void line :: setIntercept( double _yIntercept )
{
	yIntercept = _yIntercept;
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

line line :: twoPointForm( double x1, double y1, double x2, double y2 )					// takes two points and returns a line passing through those points
{
	slope = ( y2 - y1 ) / ( x2 - x1 );													// m = ( y2 - y1 ) / ( x2 - x1 )
	yIntercept = y1 - ( x1 * slope );													// c = y1 - ( m * x1 )
	
	return *this;
}

line line :: twoPointForm( cartesian pointOne, cartesian pointTwo )						// takes two points and returns a line passing through those points
{
	slope = ( pointTwo.y - pointOne.y ) / ( pointTwo.x - pointOne.x );					// m = ( y2 - y1 ) / ( x2 - x1 )
	yIntercept = pointOne.y - ( pointOne.x * slope );									// c = y1 - ( m * x1 )
	
	return *this;
}

cartesian line :: getIntersection( line Line )											// takes two lines and returns their point of intersection
{
	cartesian point;																	// if the lines are y = ax + c
																						// and y = bx + d, then
	point.x = ( Line.getIntercept( ) - yIntercept ) / ( slope - Line.getSlope( ) );		// x = ( d - c ) / ( a - d )
	point.y = ( slope * point.x ) + yIntercept;											// y = a * ( d - c ) / ( a - d ) + c

	return point;
}
