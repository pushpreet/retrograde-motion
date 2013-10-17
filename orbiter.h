#include <math.h>
#include "cartesian.h"

#define PI 3.14159265

/*
	ID Description: 		Implementation of class orbiter
							Written by Pushpreet on 16/09/2013
	
	Version:				- 1.0.4

	Features:				- stores the position of the orbiter as an angle as well as cartesian co-ordinates
							- stores both angular and linear velocity from one input through necessary conversions
							- read methods for all the properties
							- all read and write methods input and work on SI units
							- implementation for elliptical orbits hasn't been added yet
	
	Modification Historty:  01/10/2013
								- 14:33 added the currentPosition variables in a structure so that a function can return both variables at once
							05/10/2013
								- 18:50 changed position variables to store angles in radian
								- 20:05 changed all float variables / methods to double
							17-10-13
								- 19:22 added a few read methods
	
	Dependencies:			Depends On: math.h
										cartesian.h
							Used In: 	Project: Retrograde Motion - Main.cpp

*/

class orbiter
{
	private:
   		cartesian currentPos;							// current x and y co-ordinate of the orbiter
        double initialPos;								// initial position of the orbiter in radian
		double currentPosQ;								// current position of the orbiter in radian
		double orbitRadius;								// radius of the orbit
		double angularVelocity;							// angular velocity of the orbiter
		double linearVelocity;							// linear velocity of the orbiter
		char observer;									// 'y' if observer, otherwise 'n'
		char orbitNature;								// ** NOT IMPLEMENTED ** 'y' if circular, 'n' if elliptical
		char revolutionDirection;						// 'y' if clockwise, 'n' if counter-clockwise
	
	public:
		// Write methods
		void setInitialPosition( double pos );			// sets initial position of the orbiter according to parameter pos in degree
		void setOrbitNature( char nat );				// ** NOT IMPLEMENTED ** sets nature to 'y' or 'n' if parameter nat is 'y' or 'n' respectively
		void setOrbitRadius( double rad );				// sets radius of orbit in metres according to parameter rad
		void setVelocity( double vel, char typ );		// sets both angular and linear velocity of the orbiter according to parameter val, val is angular if typ is 'a' and linear if typ is 'l'
		void setObserver( char obs );					// sets to 'y' or 'n' according to parameter obs
		void setRevolutionDirection( char dir );		// sets to 'y' or 'n' according to parameter dir
		
		// Read methods
		double getInitialPosition( );					// returns the initial position
		double getOrbitRadius( );						// returns the radius of the orbit
		double getVelocity( char typ );					// returns angular velocity if typ = 'a' or linear velocity if typ = 'l'
		char getRevolutionDirection( );					// return 'y' for clockwise and 'n' for anti-clockwise
		cartesian getPos( );							// returns Posx
		double getCurrentPosition( );					// returns current position in degree
		char ifObserver( );								// returns 'y' if observer, otherwise 'n'
		
		// Other methods
		cartesian calcPosition( double time );
		
		// Constructor(s)
		orbiter( );
};

/*
	Changelog:
	
	18/09/2013
		- --:-- added implementation for constructor
		- --:-- added implementation for all write methods
		- --:-- added implementation for all read methods
	01/10/2013
        - 15:10 added the currentPosition variables in a structure so that a function can return both variables at once
        - 15:11 removed un-neccesary read methods
	05/10/2013
		- 18:50 changed position variables to store angles in radian
		- 20:04 added implementation for calcPosition method
		- 20:05 changed all float variables / methods to double
	17-10-13
		- 19:22 added read methods to acces initial position, orbit radius, velocity and revolution direction
*/


// implemetation of constructor for class orbiter
orbiter :: orbiter( )
{
	initialPos		 	= 0.0;
	currentPosQ    		= 0.0;
	currentPos.x 		= 0.0;
	currentPos.y		= 0.0;
	orbitRadius 		= 0.0;
	angularVelocity 	= 0.0;
	linearVelocity 		= 0.0;
	observer  			= 'n';
	orbitNature 		= 'y';
	revolutionDirection = 'y';
}

/*
	*********************************
	   Definition of write methods
	*********************************
*/

// sets initialPos, currentPosQ, currentPosx and currentPosy according to parameter pos in degree
void orbiter :: setInitialPosition( double pos )
{
	pos *= ( PI / 180.0 );									// converts pos to radian
	initialPos = pos;
	currentPosQ = pos;
	currentPos.x = orbitRadius * cos( pos );				// x = rcosQ for uniform circular motion
	currentPos.y = orbitRadius * sin( pos );				// y = rsinQ for uniform circular motion
}

void orbiter :: setOrbitNature( char nat )					// ** NOT IMPLEMENTED **
{
	orbitNature = nat;
}

void orbiter :: setOrbitRadius( double rad )
{
	orbitRadius = rad;
}

// sets both linear and angular velocity according to the one provded
void orbiter :: setVelocity( double vel, char typ )
{
	if( typ == 'a' )									// if input vel is angular velocity
	{
		angularVelocity = vel;
		linearVelocity = vel * orbitRadius;				// v = wr
	}
	
	else if( typ == 'l' )								// if input vel is angular velocity
	{
		linearVelocity = vel;
		angularVelocity = vel / orbitRadius;			// w = v / r
	}
}

void orbiter :: setObserver( char obs )
{
	observer = obs;
}

void orbiter :: setRevolutionDirection( char dir )
{
	revolutionDirection = dir;
}


/*
	*********************************
	   Definition of read methods
	*********************************
*/

double orbiter :: getInitialPosition( )						// returns the initial position
{
	return initialPos;
}

double orbiter :: getOrbitRadius( )							// returns the radius of the orbit
{
	return orbitRadius;
}

double orbiter :: getVelocity( char typ )					// returns angular velocity if typ = 'a' or linear velocity if typ = 'l'
{
	if( typ == 'a' )
	{
		return angularVelocity;
	}
	
	else if( typ == 'l' )
	{
		return linearVelocity;
	}
}

char orbiter :: getRevolutionDirection( )					// return 'y' for clockwise and 'n' for anti-clockwise
{
	return revolutionDirection;
}
		
cartesian orbiter :: getPos( )
{
	return currentPos;
}

double orbiter :: getCurrentPosition( )
{
	return currentPosQ * ( 180 / PI );
}

char orbiter :: ifObserver( )
{
	return observer;
}

/*
	*********************************
      Definition of other methods
	*********************************
*/

cartesian orbiter :: calcPosition( double time )
{
	double angularVel;

	if( revolutionDirection == 'y' )
		angularVel = angularVelocity;
	else if( revolutionDirection == 'n' )
		angularVel = -1 * angularVelocity;

	currentPos.x = orbitRadius * cos( initialPos + ( angularVel * time ) );					// x = rcos( Q + wt ) for uniform circular motion
	currentPos.y = orbitRadius * sin( initialPos + ( angularVel * time ) );					// y = rsin( Q + wt ) for uniform circular motion

	currentPosQ = angularVelocity * time;

	return currentPos;
}
