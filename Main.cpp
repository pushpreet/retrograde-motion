#include <iostream>
#include <conio.h>
#include <windows.h>
#include "cartesian.h"
#include "orbiter.h"
#include "line.h"

// definitions for various screens
#define SCREEN_WELCOME	0
#define SCREEN_NEW_EXP	1
#define SCREEN_HISTORY	2
#define SCREEN_HELP		3

short int CURRENT_SCREEN = 0;		// global variable to keep track of current screen

using namespace std;

COORD _setConsole( )				// sets the basic attributes of the console window
{
	HWND hWnd;
	SetConsoleTitle( "Retrograde Motion" );						// set the console window's title
	hWnd = FindWindow( NULL, "Retrograde Motion" );
	
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD screenSize = GetLargestConsoleWindowSize( hOut );		// get the largest available size for the console window
	SetConsoleScreenBufferSize( hOut, screenSize );				// set the console screen buffer size to the largest
	
	ShowWindow( GetConsoleWindow( ), SW_SHOWMAXIMIZED );		// maximise the window
	
	system( "color 0C" );										// set the default screen background and text color
	system( "cls" );											// clear screen
	
	return screenSize;
}

void gotoxy(int x, int y)			// function to place the cursor at a position on the console specified by x and y
{
	COORD coord;					// structure COORD is present in windows.h
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);		// windows.h funtion to change the position of the cursor
}

void _setColor( short int colorScheme )			// changes the text and background color according to colorScheme
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
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
	}    
}

void _menu( COORD screenSize )					// top menu
{
	int horizontalSpace = ( screenSize.X - ( 14 ) );		// total characters avilable for the menu
	int menuWordSpace = horizontalSpace / 6;				// space for each menu item = total space / no of menus
	int halfSpace = menuWordSpace / 2;
	
	switch( CURRENT_SCREEN )
	{
		case SCREEN_WELCOME:								// Save Experiment not available
			
			_setColor( 3 );
			gotoxy( 6 + ( menuWordSpace * 0 ) + ( halfSpace - 7 ), 5 );
			cout<<"New Experiment";
			
			_setColor( 2 );
			gotoxy( 6 + ( menuWordSpace * 1 ) + ( halfSpace - 7 ), 5 );
			cout<<"Save Experiment";
			
			_setColor( 3 );
			gotoxy( 6 + ( menuWordSpace * 2 ) + ( halfSpace - 3 ), 5 );
			cout<<"History";
			
			gotoxy( 6 + ( menuWordSpace * 3 ) + ( halfSpace - 2 ), 5 );
			cout<<"Help";
			
			gotoxy( 6 + ( menuWordSpace * 4 ) + ( halfSpace - 2 ), 5 );
			cout<<"About";
			
			gotoxy( 6 + ( menuWordSpace * 5 ) + ( halfSpace - 2 ), 5 );
			cout<<"Exit";
			
			break;
	}
	
}

void _paintScreen( COORD screenSize )
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

void _control_loop( COORD screenSize )
{
	
}

void _interface( )
{
	COORD screenSize = _setConsole( );
	_paintScreen( screenSize );
	
	_setColor( 3 );
	gotoxy( ((( screenSize.X - 14 ) / 2 ) - 3 ), (( screenSize.Y - 9 ) / 2 ) );
	cout<<"Retrograde Motion";
	
	_control_loop( screenSize );
	
	
};

int main( )
{
	_interface( );

	getch( );
	return 0;
}
