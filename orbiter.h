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
		float initialPosition;							// initial position of the orbiter in degree
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
}
