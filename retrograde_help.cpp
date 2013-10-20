/*
	ID Description: 		Main for project - Retrograde Motion
							Written by Pushpreet on 05/10/2013
	
	Version:				- 1.0.0

	Features:				- 
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: fstream
										iostream
										conio.h
										windows.h
										string.h
							Used In: 	Project: Retrograde Motion - Main.cpp

*/

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string.h>

using namespace std;

COORD screenSize;

void _setConsole( )				// sets the basic attributes of the console window
{
	HWND hWnd;
	SetConsoleTitle( "Retrograde Motion - Help" );						// set the console window's title
	hWnd = FindWindow( NULL, "Retrograde Motion - Help" );
	
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	screenSize = GetLargestConsoleWindowSize( hOut );			// get the largest available size for the console window
	
	screenSize.Y += 1000;
	
	SetConsoleScreenBufferSize( hOut, screenSize );				// set the console screen buffer size to the largest
	
	ShowWindow( GetConsoleWindow( ), SW_SHOWMAXIMIZED );		// maximise the window
	
	system( "color 0f" );										// set the default screen background and text color
	system( "cls" );											// clear screen
}

void space( int space = 1, int shift = 0 )
{
	int spacing = (( screenSize.X - 85 ) / 4);
	
	for( int i = 0 ; i < ( spacing * space ) - shift ; i++ )
	{
		cout<<" ";
	}
	
}
int main( int argc, char* argv[] )
{
	_setConsole( );
	
	cout<<argv[1];
	int choice;
	
	char str[200];
	
	ifstream fileIn;
	fileIn.open( "help.txt" , ios :: in );
		
	if( !fileIn )
	{
		cout<<endl;
		space( 3, 5 );		
		cout<<"No help exists."<<endl;
		
		space( 3, 6 );
		cout<<"Press any key to exit.";
		
		getch( );
		return 0;
	}
	
	cout<<endl;
	
	space( 3 , -2 );	
	cout<<"Help"<<endl<<endl;
	
	while( fileIn.getline( str, 200, '\n' ) )
	{
		space( 1 );
		puts( str );
	}
	
	fileIn.close( );
	
	choice = getch( );
	
	if( choice == 4 )
	{
		remove( "saved_experiments.txt" );
		system( "cls" );
		cout<<endl;
	
		space( 3, 10 );	
		cout<<"History deleted. Press any key to exit."<<endl<<endl;
	}
	
	getch( );
	
	return 0;
}
