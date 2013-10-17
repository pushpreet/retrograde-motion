/*
	ID Description: 		Main for project - Retrograde Motion
							Written by Pushpreet on 05/10/2013
	
	Version:				- 1.0.0

	Features:				- contextual help
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: orbiter.h
										line.h
										cartesian.h
										iostream
										fstream
										conio.h
										windows.h
										iomanip
										time.h
							Used In: 	Project: Retrograde Motion - Main.cpp

*/

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <time.h>
#include "cartesian.h"
#include "orbiter.h"
#include "line.h"

// mapping for various screens
#define SCREEN_WELCOME		0
#define SCREEN_NEW_EXP		1
#define SCREEN_EXP_VAR		2
#define SCREEN_RUN_EXP		3
#define SCREEN_CALC_TIME	4

// mapping for various key presses
#define TAB 	9
#define CR 		13
#define NEW		14
#define SAVE 	19
#define HISTORY	22
#define YES		121
#define NO		110

// global variables
short int CURRENT_SCREEN = 0;		// global variable to keep track of current screen
COORD screenSize;					// global variable as screenSize is needed by many functions

// function prototypes
int _control_loop( );																							// function with the main loop which is responsible for managing the flow of control
void _screen_exp_var( orbiter* orbiterPointer, int noOfOrbiters );												// function to input experiment variables
void _screen_run_exp( orbiter* orbiterPointer, int noOfOrbiters, double timePeriod, double timeInterval );		// funtion to run the experiment according to the values of orbiters provided
void calculateTime( orbiter* orbiterOne, orbiter* orbiterTwo, double timePeriod, double timeInterval );

using namespace std;

const string currentDateTime() 
{
    time_t rawTime;
	time ( &rawTime );

    return ctime( &rawTime );
}


void gotoxy( int x, int y )			// function to place the cursor at a position on the console specified by x and y
{
	COORD coord;					// structure COORD is present in windows.h
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );		// windows.h funtion to change the position of the cursor
}

void hideCursor( )					// hides the cursor
{
   HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible = FALSE;
   SetConsoleCursorInfo( consoleHandle, &info );
}

void showCursor( )					// shows the cursor
{
   HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo( consoleHandle, &info );
}

void _setConsole( )				// sets the basic attributes of the console window
{
	HWND hWnd;
	SetConsoleTitle( "Retrograde Motion" );						// set the console window's title
	hWnd = FindWindow( NULL, "Retrograde Motion" );
	
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	screenSize = GetLargestConsoleWindowSize( hOut );			// get the largest available size for the console window
	SetConsoleScreenBufferSize( hOut, screenSize );				// set the console screen buffer size to the largest
	
	ShowWindow( GetConsoleWindow( ), SW_SHOWMAXIMIZED );		// maximise the window
	
	system( "color 0C" );										// set the default screen background and text color
	system( "cls" );											// clear screen
}

void _setColor( short int colorScheme )			// changes the text and background color according to colorScheme
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	
	switch( colorScheme )
	{
		case 0:			// white on black
			SetConsoleTextAttribute( hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
			break;
		
		case 1:			// black on white
			SetConsoleTextAttribute( hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY );
			break;
			
		case 2:			// grey on black
			SetConsoleTextAttribute( hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
			break;
			
		case 3:			// red on black
			SetConsoleTextAttribute( hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY );
			break;
		
		case 4:			// green on black
			SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN );
			break;
	}    
}

void _paintScreen(  )											// paints the basic interface
{
	system( "cls" );											// clear screen
	
	_setColor( 0 );
    
	for( int i = 5 ; i < ( screenSize.X - 6 ) ; i++ )			// loop to print the horizontal border lines
	{
		gotoxy( i, 3 );											// top bold line
		cout<<(char)219;
		
		gotoxy( i, ( screenSize.Y - 8 ) );						// bottom bold line
		cout<<(char)219;
		
		gotoxy( i, 4 );											// top thin line
		cout<<(char)196;
		
		gotoxy( i, ( screenSize.Y - 9 ) );						// bottom thin line
		cout<<(char)196;
		
		gotoxy( i, 6 );											// top menu line
		cout<<(char)196;		
	}
	
	_setColor( 0 );
	
	for( int i = 4 ; i < ( screenSize.Y - 8 ) ; i++ )			// loop to print the vertical lines
	{
		gotoxy( 5, i );											// left bold line
		cout<<(char)219;
		
		gotoxy( ( screenSize.X - 7 ), i );						// right bold line
		cout<<(char)219;
		
		gotoxy( 6, i );											// left thin line
		cout<<(char)179;
		
		gotoxy( ( screenSize.X - 8 ), i );						// right thin line
		cout<<(char)179;		
	}
	
	gotoxy( 6, 4 );												// top-left angled connector
	cout<<(char)218;
	
	gotoxy( ( screenSize.X - 8 ), 4 );							// top-right angled connector
	cout<<(char)191;
	
	gotoxy( 6, ( screenSize.Y - 9 ) );							// bottom-left angled connector
	cout<<(char)192;
				   
	gotoxy( ( screenSize.X - 8 ), ( screenSize.Y - 9 ) );		// bottom-right angled connector
	cout<<(char)217;
	
	gotoxy( 6, 6 );												// left menu line connector
	cout<<(char)195;
	
	gotoxy( ( screenSize.X - 8 ), 6 );							// right menu line connector
	cout<<(char)180;	
}

void _menu(  )												// top menu
{
	int horizontalSpace = ( screenSize.X - ( 14 ) );		// total characters avilable for the menu
	int menuWordSpace = horizontalSpace / 6;				// space for each menu item = total space / no of menus
	int halfSpace = menuWordSpace / 2;
	
	switch( CURRENT_SCREEN )
	{
		case SCREEN_WELCOME:								// Welcome Screen / Save Experiment not available
			
			_setColor( 3 );
			
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			_setColor( 2 );
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			_setColor( 3 );
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 6 ), 5 );
			cout<<"View History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
		
		case SCREEN_NEW_EXP:								// New Experiment Screen / Save Experiment not available
			
			_setColor( 3 );
			
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			_setColor( 2 );
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			_setColor( 3 );
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 6 ), 5 );
			cout<<"View History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
		
		case SCREEN_EXP_VAR:								// Experiment Variables / Save Experiment not available
			
			_setColor( 3 );
			
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			_setColor( 2 );
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			_setColor( 3 );
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 6 ), 5 );
			cout<<"View History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
			
		case SCREEN_RUN_EXP:								// Run Experiment / All oprions available available
			
			_setColor( 3 );
			
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 6 ), 5 );
			cout<<"View History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
		
		case SCREEN_CALC_TIME:								// Run Experiment / All oprions available available
			
			_setColor( 2 );
			
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 6 ), 5 );
			cout<<"View History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			_setColor( 3 );
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
	}
	
}

void _screen_new_exp( )										// function to setup a new experiment
{
	_paintScreen( );										// repaints the screen to remove any previous text

	CURRENT_SCREEN = SCREEN_NEW_EXP;						// changes the global variable
	_menu( );												// calls the menu function which prints the menu according to the current screen
	
	int noOfOrbiters = 0;									// variable to store the number of orbiters specified by the user
	int control;											// variable to store the return value of _control_loop( )
	int highlighted = 0;									// variable to keep track of the highlighted option
	int orbiterNumber = 0;									// variable to keep track of the current orbiter whose value is being modified
	double input;											// variable to store the input from the keyboard as a double
	char chInput;											// variable to store the input from the keyboard as a character
		
	int horizontalSpace = ( screenSize.X - ( 14 ) );		// total characters available inside the outline
	int wordSpace = horizontalSpace / 7;					// space for each variable item = total space / no of variables
	int halfSpace = wordSpace / 2;
	
	_setColor( 3 );											// sets the color red to indicate that the option is highlighted
	gotoxy( 6 + (( horizontalSpace / 2 ) - 23 ), 10 );
	cout<<"Enter the number of revolving bodies you want :";
	
	do
	{
		control = _control_loop( );								// _control_loop( ) is called to see if the user wants to enter the value or otherwise
																// the cursor becomes visible if user chose to enter the value, i.e., pressed enter
		if( control == CR )
		{
			_setColor( 4 );
			gotoxy( 6 + ( horizontalSpace / 2 ), 12 );
			cin>>noOfOrbiters;
			hideCursor( );										// hides the cursor again indicate that the input has been registered
		}
	}while( control != CR );
	
	orbiter *orbiterPointer = new orbiter[noOfOrbiters];	// dynamically allocates memory to all the orbiters
	
	do
	{	
		switch( highlighted )				// checks which option is highlighted
		{
			case 0:							// when no option is highlighted, prints all the options and highlights the first one
				_setColor( 2 );				// grey color for option(s) that are not highlighted
				gotoxy( 6 + ( wordSpace * 0 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Body "<<( orbiterNumber + 1 )<<" :";
				
				_setColor( 3 );				// red color for highlighted option(s)
				gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Initial Position";
				
				_setColor( 2 );
				gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Orbit Radius";
				
				gotoxy( 6 + ( wordSpace * 3 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Angular Velocity";
				
				gotoxy( 6 + ( wordSpace * 4 ) + ( halfSpace - 10 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Revolution Direction";
				
				gotoxy( 6 + ( wordSpace * 5 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"Observer";
				
				gotoxy( 6 + ( wordSpace * 6 ) + ( halfSpace - 3 ), ( 20 + ( orbiterNumber * 10)) );
				cout<<"--Done--";
								
				highlighted++;				// highlight the next option
				break;
				
			case 1:							// if the first option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Orbit Radius";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Initial Position";
					
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * highlighted ) + ( halfSpace - 8 ), ( 22 + ( orbiterNumber * 10)) );
					cin>>input;
					( orbiterPointer + orbiterNumber )->setInitialPosition( input );
					break;
				}
			
			case 2:							// if the second option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 3 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Angular Velocity";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Orbit Radius";
				
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * highlighted ) + ( halfSpace - 6 ), ( 22 + ( orbiterNumber * 10)) );
					cin>>input;
					( orbiterPointer + orbiterNumber )->setOrbitRadius( input );
					break;
				}
			
			case 3:							// if the third option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 4 ) + ( halfSpace - 10 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Revolution Direction";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 3 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Angular Velocity";
					
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * highlighted ) + ( halfSpace - 8 ), ( 22 + ( orbiterNumber * 10)) );
					cin>>input;
					( orbiterPointer + orbiterNumber )->setVelocity( input, 'a' );
					break;
				}
			
			case 4:							// if the fourth option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 5 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Observer";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 4 ) + ( halfSpace - 10 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Revolution Direction";
				
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * highlighted ) + ( halfSpace - 10 ), ( 22 + ( orbiterNumber * 10)) );
					cin>>chInput;
					( orbiterPointer + orbiterNumber )->setRevolutionDirection( chInput );
					break;
				}
			
			case 5:							// if the fifth option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 6 ) + ( halfSpace - 3 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"--Done--";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 5 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Observer";
				
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * highlighted ) + ( halfSpace - 8 ), ( 22 + ( orbiterNumber * 10)) );
					cin>>chInput;
					( orbiterPointer + orbiterNumber )->setObserver( chInput );
					break;
				}
			
			case 6:							// if the sixth option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 8 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"Initial Position";
					
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 6 ) + ( halfSpace - 3 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"--Done--";
				
					highlighted = 1;				// highlight the first option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input values for the next orbiter
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * 6 ) + ( halfSpace - 3 ), ( 20 + ( orbiterNumber * 10)) );
					cout<<"--Done--";
				
					highlighted = 0;				// highlight the 0th option, i.e., for taking values for the next orbiter
					orbiterNumber++;				// increment the orbiterNumber so that values values for the next orbiter can be taken
					break;
				}
			
		}
		
		hideCursor( );								// hide cursor after each input
		
		control = _control_loop( );					// control goes back to the control loop to check the key press
		
	} while( noOfOrbiters > orbiterNumber );		// run the loop till values for all the objects have been entered
	
	_screen_exp_var( orbiterPointer, noOfOrbiters );
}

void _screen_exp_var( orbiter* orbiterPointer, int noOfOrbiters )		// function to input experiment variables
{
	_paintScreen( );										// repaint the screen to remove any earlier text
	CURRENT_SCREEN = SCREEN_EXP_VAR;						// changes the global variable
	_menu( );												// reprint the menu
	
	int done;												// variable to see if all the options have been entered
	int control;											// variable to store the return value of _control_loop( )
	int highlighted = 0;									// variable to keep track of the highlighted option
	double timePeriod, timeInterval;						// variables to store the Time Period and time Interval
	
	int horizontalSpace = ( screenSize.X - ( 14 ) );		// total characters available inside the outline
	int wordSpace = horizontalSpace / 3;					// space for each variable item = total space / no of variables
	int halfSpace = wordSpace / 2;
		
	_setColor( 3 );
	gotoxy( 6 + (( horizontalSpace / 2 ) - 15 ), 10 );
	cout<<"Experiment Variables";
	
	do
	{	
		switch( highlighted )				// checks which option is highlighted
		{
			case 0:							// when no option is highlighted, prints all the options and highlights the first one
				
				_setColor( 3 );				// red color for highlighted option(s)
				gotoxy( 6 + ( wordSpace * 0 ) + ( halfSpace - 5 ), 30 );
				cout<<"Time Period";
				
				_setColor( 2 );
				gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 6 ), 30 );
				cout<<"Time Interval";
				
				gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), 30 );
				cout<<"--Done--";
								
				highlighted++;				// highlight the next option
				break;
				
			case 1:							// if the first option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 2 );				// red color for highlighted option(s)
					gotoxy( 6 + ( wordSpace * 0 ) + ( halfSpace - 5 ), 30 );
					cout<<"Time Period";
				
					_setColor( 3 );
					gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 6 ), 30 );
					cout<<"Time Interval";
				
					highlighted++;				// highlight the next option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * 0 ) + ( halfSpace - 5 ), 32 );
					cin>>timePeriod;
					
					break;
				}
			
			case 2:							// if the second option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );				// red color for highlighted option(s)
					gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), 30 );
					cout<<"--Done--";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 6 ), 30 );
					cout<<"Time Interval";
				
					highlighted++;				// highlight the first option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input the value
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * 1 ) + ( halfSpace - 6 ), 32 );
					cin>>timeInterval;
					
					break;
				}
			
			case 3:							// if the sixth option was highlighted
				if( control == TAB )		// if tab is pressed, highlight the next option
				{
					_setColor( 3 );				// red color for highlighted option(s)
					gotoxy( 6 + ( wordSpace * 0 ) + ( halfSpace - 5 ), 30 );
					cout<<"Time Period";
				
					_setColor( 2 );
					gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), 30 );
					cout<<"--Done--";
				
					highlighted = 1;				// highlight the first option
					break;
				}
				
				else if( control == CR )	// else if enter is pressed, input values for the next orbiter
				{
					_setColor( 4 );
					gotoxy( 6 + ( wordSpace * 2 ) + ( halfSpace - 6 ), 30 );
					cout<<"--Done--";
				
					done = 1;				// if all options have been entered
					
					break;
				}
		}
		
		hideCursor( );								// hide cursor after each input
		
		control = _control_loop( );					// control goes back to the control loop to check the key press
		
	} while( done != 1 );		// run the loop till values for all the objects have been entered
	
	_screen_run_exp( orbiterPointer, noOfOrbiters, timePeriod, timeInterval );		// call the _screen_run_exp funtion with values of all the objects
		
}

void _screen_save_exp( orbiter* orbiterPointer, int noOfOrbiters, double timePeriod, double timeInterval )
{
	ofstream fileOut;
	fileOut.open( "saved_experiments.txt" , ios :: out | ios :: app );
	
	fileOut<<endl
			<<"\t"<<"****************************************************************************************************************************************************************"
			<<endl
			<<"\t"<<"****************************************************************************************************************************************************************"
			<<endl<<endl;
	
	fileOut<<"\t"<<currentDateTime( )
			<<endl<<endl;
	
	fileOut<<"\t"<<"----------------------------------------------------------------------------------------------------------------------------------------------------------------"
			<<endl;
			
	fileOut<<"\t"<<setw( 25 )<<" "
			<<setw( 25 )<<"Initial Position"
			<<setw( 25 )<<"Orbit Radius"
			<<setw( 25 )<<"Angular Velocity"
			<<setw( 25 )<<"Revolution Direction"
			<<setw( 25 )<<"Observer"
			<<endl<<endl;
	
	fileOut<<"\t"<<"----------------------------------------------------------------------------------------------------------------------------------------------------------------"
			<<endl;
	
	for( int i = 0 ; i < noOfOrbiters ; i++ )
	{
		fileOut<<"\t"<<"Orbiter "<<setw( 17 )<<( i + 1 )
				<<setw( 25 )<<( orbiterPointer + i )->getInitialPosition( )
				<<setw( 25 )<<( orbiterPointer + i )->getOrbitRadius( )
				<<setw( 25 )<<( orbiterPointer + i )->getVelocity( 'a' )
				<<setw( 25 )<<((( orbiterPointer + i )->getRevolutionDirection( ) == 'y' ) ? "Clockwise" : "Anti-Clockwise" )
				<<setw( 25 )<<((( orbiterPointer + i )->ifObserver( ) == 'y' ) ? "Yes" : "No" )
				<<endl;				
	}
	
	fileOut<<endl<<"\t"
			<<setw( 25 )<<"Time Period : "<<timePeriod
			<<setw( 25 )<<"Time Interval : "<<timeInterval
			<<endl;
			
	fileOut<<"\t"<<"----------------------------------------------------------------------------------------------------------------------------------------------------------------"
			<<endl;
			
	fileOut.close( );
	
	_setColor( 3 );
	gotoxy( ((( screenSize.X - 14 ) / 2 ) ), ( screenSize.Y - 19 ) );
	cout<<"Saved";
}

int _control_loop( )				// function with the main loop which is responsible for managing the flow of control
{
	_menu( );
	
	int keypress;
	int choice;
	
	while( true )
	{
		
		keypress = getch( );
		
		switch( keypress )
		{
			case NEW:		// Ctrl + N / New Experiment				
				if( CURRENT_SCREEN == SCREEN_WELCOME )
				{
					_screen_new_exp( );
				}
				
				else if( CURRENT_SCREEN == SCREEN_NEW_EXP || CURRENT_SCREEN == SCREEN_EXP_VAR || CURRENT_SCREEN == SCREEN_RUN_EXP )
				{
					_setColor( 3 );
					gotoxy( ((( screenSize.X - 14 ) / 2 ) - 17 ), ( screenSize.Y - 19 ) );
					cout<<"Discard this experiment? ( y / n )";
					choice = _control_loop( );
					
					if( choice == YES )
					{
						_screen_new_exp( );
					}
					
					else
					{
						_setColor( 3 );
						gotoxy( ((( screenSize.X - 14 ) / 2 ) - 17 ), ( screenSize.Y - 19 ) );
						cout<<"                                    ";
						return 0;
					}
				}
				
				break;
				
			case SAVE:		// Ctrl + S / Save Experiment
				if( CURRENT_SCREEN == SCREEN_RUN_EXP )
				{
					return SAVE;
				}
				
				break;
				
			case HISTORY:
				system( "start history.exe" );
				
				break;
			
			case TAB:		// Tab key
				return TAB;
				break;
			
			case CR:		// Carriage Return / Enter 
				showCursor( );
				return CR;
				break;
			
			case 89:
				return YES;
				break;
			
			case 121:
				return YES;
				break;
			
			case 78:
				return NO;
				break;
			
			case 110:
				return NO;
				break;
			
			case 27:		// ESC key
				exit( 0 );
				break;
		}
	}
}

void _interface( )
{
	_setConsole( );
	_paintScreen( );
	
	_setColor( 3 );
	gotoxy( ((( screenSize.X - 14 ) / 2 ) - 3 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"Retrograde Motion";
	
	while( true )
	{
		hideCursor( );
		_control_loop( );
	}

};

void _screen_run_exp( orbiter* orbiterPointer, int noOfOrbiters, double timePeriod, double timeInterval )				// runs the experiment
{
	_paintScreen( );										// repaint the screen to remove any earlier text	
	CURRENT_SCREEN = SCREEN_RUN_EXP;	
	_menu( );												// reprint the menu
	
	int observer;
	int control;
	int horizontalSpace = ( screenSize.X - ( 14 ) );		// total characters available inside the outline
	
	_setColor( 3 );
	gotoxy( 6 + (( horizontalSpace / 2 ) - 15 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"Press Enter to run experiment";
	
	do
	{
		control = _control_loop( );						// check if enter is pressed
	
		if( control == CR )
		{
			for( int i = 0 ; i < noOfOrbiters ; i++ )
			{
				if( ( orbiterPointer + i )->ifObserver( ) == 'y' )
				{
						observer = i;
						break;
				}
			}
	
			for( int i = 0 ; i < noOfOrbiters ; i++ )
			{
				if( i != observer )
				{
					calculateTime( ( orbiterPointer + observer ), ( orbiterPointer + i ), timePeriod, timeInterval );
				}
			}
		}
		
		else if( control == SAVE )
		{
			_screen_save_exp( orbiterPointer, noOfOrbiters, timePeriod, timeInterval );
		}
	}while( control != CR );
	
}

void calculateTime( orbiter* orbiterOne, orbiter* orbiterTwo, double timePeriod, double timeInterval )
{
	_paintScreen( );										// repaint the screen to remove any earlier text
	CURRENT_SCREEN = SCREEN_CALC_TIME;
	_menu( );												// reprint the menu
	
	int horizontalSpace = ( screenSize.X - ( 14 ) );
	
	cartesian pointOne, pointTwo, intersection;
	line reference( 0, 100 );
	line passing;
	double lastIntercept = 0.0;
	char newDirection, lastDirection = 'x';
	int loadDots = 0;
	
	ofstream fileOut;
	fileOut.open( "Time_Log.txt" , ios :: out | ios :: app );
	
	fileOut.setf( ios :: left );
	
	fileOut<<endl
			<<"\t"<<"********************************************************************************"
			<<endl
			<<"\t"<<"********************************************************************************"
			<<endl<<endl;
	
	fileOut<<"\t"<<currentDateTime( )
			<<endl<<endl;
	
	fileOut<<"\t"<<setw( 30 )<<" "
			<<setw( 30 )<<"Orbiter One"
			<<setw( 30 )<<"Orbiter Two"
			<<endl<<endl;
	
	fileOut<<"\t"<<setw( 30 )<<"Initial Position :"
			<<setw( 30 )<<orbiterOne->getInitialPosition( )
			<<setw( 30 )<<orbiterTwo->getInitialPosition( )
			<<endl;
	
	fileOut<<"\t"<<setw( 30 )<<"Orbit Radius :"
			<<setw( 30 )<<orbiterOne->getOrbitRadius( )
			<<setw( 30 )<<orbiterTwo->getOrbitRadius( )
			<<endl;
	
	fileOut<<"\t"<<setw( 30 )<<"Angular Velocity :"
			<<setw( 30 )<<orbiterOne->getVelocity( 'a' )
			<<setw( 30 )<<orbiterTwo->getVelocity( 'a' )
			<<endl;
	
	fileOut<<"\t"<<setw( 30 )<<"Revolution Direction :"
			<<setw( 30 )<<(( orbiterOne->getRevolutionDirection( ) == 'y' ) ? "Clockwise" : "Anti-Clockwise" )
			<<setw( 30 )<<(( orbiterTwo->getRevolutionDirection( ) == 'y' ) ? "Clockwise" : "Anti-Clockwise" )
			<<endl<<endl;
	
	fileOut<<"\t"<<"--------------------------------------------------------------------------------"
			<<endl;
			
	fileOut<<"\t"<<setw( 30 )<<"Position One"
			<<setw( 30 )<<"Position Two"
			<<setw( 30 )<<"Time"
			<<endl;
			
	fileOut<<"\t"<<"--------------------------------------------------------------------------------"
			<<endl;
		
	hideCursor( );
	_setColor( 3 );
	gotoxy( 6 + (( horizontalSpace / 2 ) - 10 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"Running";
	
	time_t lastTime, newTime;						// used to display the dots while calculating
	time( &lastTime );
	
	for( double timeElapsed = 0 ; timeElapsed < timePeriod ; timeElapsed += timeInterval )
	{
		_setColor( 3 );
		gotoxy( 6 + (( horizontalSpace / 2 ) ), (( screenSize.Y - 9 ) / 2 ) );
		
		time( &newTime );
		
		if( difftime( newTime, lastTime ) == 1 )
		{
			lastTime = newTime;
			
			if( loadDots < 5 )
			{
				gotoxy( 6 + (( horizontalSpace / 2 ) + loadDots ), (( screenSize.Y - 9 ) / 2 ) );
				cout<<".";
				loadDots++;
			}
			
			else
			{
				loadDots = 0;
				gotoxy( 6 + (( horizontalSpace / 2 ) + loadDots ), (( screenSize.Y - 9 ) / 2 ) );
				cout<<"     ";
			}
		}
		
		pointOne = orbiterOne->calcPosition( timeElapsed );
		pointTwo = orbiterTwo->calcPosition( timeElapsed );
		
		passing.twoPointForm( pointOne, pointTwo );
		
		intersection = reference.getIntersection( passing );
		
		if( intersection.x > lastIntercept )
		{
			newDirection = 'p';
			lastIntercept = intersection.x;
		}
		
		else if( intersection.x < lastIntercept )
		{
			newDirection = 'n';
			lastIntercept = intersection.x;
		}
		
		if( lastDirection == 'x' )
		{
			lastDirection = newDirection;
		}
		
		else if( newDirection != lastDirection )
		{
			fileOut<<endl<<"\t"<<"x :"<<setw( 27 )<<pointOne.x<<"x :"<<setw( 27 )<<pointTwo.x
					<<endl<<"\t"<<"y :"<<setw( 27 )<<pointOne.y<<"y :"<<setw( 27 )<<pointTwo.y
					<<setw( 30 )<<timeElapsed;
			
			lastDirection = newDirection;
		}
	}
	
	_setColor( 3 );
	gotoxy( 6 + (( horizontalSpace / 2 ) - 15 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"                    ";
	
	gotoxy( 6 + (( horizontalSpace / 2 ) - 2 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"Done";
	
	fileOut<<endl<<"\t"<<"--------------------------------------------------------------------------------"
			<<endl;
	
	fileOut.close( );
}

int main( )
{
	hideCursor( );

	_interface( );

	getch( );
	return 0;
}
