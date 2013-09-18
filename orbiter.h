#include <math.h>

/*
	ID Description: 		Implementation of class orbiter
							Written by Pushpreet on 16/09/2013
	
	Features:				- stores the position of the orbiter as an angle as well as cartesian co-ordinates
							- stores both angular and linear velocity from one input through necessary conversions
							- read methods for all the properties
							- all read and write methods input and work on SI units
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: math.h
							Used In: 	NULL

*/

class orbiter
{
	private:
		float initialPos;								// initial position of the orbiter in degree
		float currentPosQ;								// current position of the orbiter in degree
		float currentPosx;								// current x co-ordinate of the orbiter
		float currentPosy;								// current y co-ordinate of the orbiter
		float orbitRadius;								// radius of the orbit
		float angularVelocity;							// angular velocity of the orbiter
		float linearVelocity;							// linear velocity of the orbiter
		char  observer;									// 'y' if observer, otherwise 'n'
		char  orbitNature;								// 'y' if circular, 'n' if elliptical
		char  revolutionDirection;						// 'y' if clockwise, 'n' if counter-clockwise
	
	public:
		// Write methods
		void setInitialPosition( float pos );			// sets initial position of the orbiter according to parameter pos in degree
		void setOrbitNature( char nat );				// sets nature to 'y' or 'n' if parameter nat is 'y' or 'n' respectively
		void setOrbitRadius( float rad );				// sets radius of orbit in metres according to parameter rad
		void setVelocity( float vel, char typ );		// sets both angular and linear velocity of the orbiter according to parameter val, val is angular if typ is 'a' and linear if typ is 'l'
		void setObserver( char obs );					// sets to 'y' or 'n' according to parameter obs
		void setRevolutionDirection( char dir );		// sets to 'y' or 'n' according to parameter dir
		
		// Read methods
		float getInitialPosition( );					// returns initial position in degree
		float getCurrentPosition( );					// returns current position in degree
		float getPosx( );								// returns Posx
		float getPosy( );								// returns Posy
		float getOrbitRadius( );						// returns orbit radius
		float getVelocity( char typ );					// returns angular velocity or linear velocity if typ is 'a' or 'l' respectively 
		char  ifObserver( );							// returns 'y' if observer, otherwise 'n'
		char  getOrbitNature( );						// returns 'y' if circular, 'n' if elliptical
		char  getRevolutionDirection( );				// returns 'y' if clockwise, 'n' if counter-clockwise
		
		// Constructor(s)
		orbiter( );
};

/*
	Changelog:
	
	18/09/2013
		- added implementation for constructor
		- added implementation for all write methods
		- added implementation for all read methods
	
*/


// implemetation of constructor for class orbiter
orbiter :: orbiter( )
{
	initialPos		 	= 0.0;
	currentPosQ 		= 0.0;
	currentPosx 		= 0.0;
	currentPosy 		= 0.0;
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

// sets initialPos, currentPosQ, currentPosx and currentPosy according to parameter pos
void orbiter :: setInitialPosition( float pos )
{
	initialPos = pos;
	currentPosQ = pos;
	currentPosx = orbitRadius * cos( pos );				// x = rcosQ for uniform circular motion
	currentPosy = orbitRadius * sin( pos );				// y = rsinQ for uniform circular motion
}

void orbiter :: setOrbitNature( char nat )
{
	orbitNature = nat;
}

orbiter :: setOrbitRadius( float rad )
{
	orbitRadius = rad;
}

// sets both linear and angular velocity according to the one provded
void orbiter :: setVelocity( float vel, char typ )
{
	if( typ == 'a' )									// if input vel is angular velocity
	{
		angularVelocity = vel;
		linearVelocity = vel * orbitRadius;
	}
	
	else if( typ == 'l' )
	{
		linearVelocity = vel;
		angularVelocity = vel / orbitRadius;
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

float orbiter :: getInitialPosition( )
{
	return initialPos;
}

float orbiter :: getCurrentPosition( )
{
	return currentPosQ;
}

float orbiter :: getPosx( )
{
	return currentPosx;
}

float orbiter :: getPosy( )
{
	return currentPosy;
}

float orbiter :: getOrbitRadius( )
{
	return orbitRadius;
}

// returns angular velocity if typ is 'a', linear velocity if typ is 'l'
float orbiter :: getVelocity( char typ )
{
	if( typ == 'a' )
		return angularVelocity;
		
	else if( typ == 'l' )
		return linearVelocity;
	
	else
		return -1;
}

char orbiter :: isObserver( )
{
	return observer;
}

char orbiter :: getOrbitNature( )
{
	return orbitNature;
}

char orbiter :: getRevolutionDirection( )
{
	return revolutionDirection;
}
