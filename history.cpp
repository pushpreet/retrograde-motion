/*
	ID Description: 		Main for project - Retrograde Motion
							Written by Pushpreet on 05/10/2013
	
	Version:				- 1.0.0

	Features:				- 
	
	Modification Historty:  NULL
	
	Dependencies:			Depends On: fstream
										iostream
										conio.h
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
	SetConsoleTitle( "Retrograde Motion - History" );						// set the console window's title
	hWnd = FindWindow( NULL, "Retrograde Motion - History" );
	
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	screenSize = GetLargestConsoleWindowSize( hOut );			// get the largest available size for the console window
	SetConsoleScreenBufferSize( hOut, screenSize );				// set the console screen buffer size to the largest
	
	ShowWindow( GetConsoleWindow( ), SW_SHOWMAXIMIZED );		// maximise the window
	
	system( "color 0f" );										// set the default screen background and text color
	system( "cls" );											// clear screen
}

int main( )
{
	_setConsole( );
	
	int spacing = (( screenSize.X - 85 ) / 4);
	
	char str[200];
	
	ifstream fileIn;
	fileIn.open( "saved_experiments.txt" , ios :: in );
		
	if( !fileIn )
	{
		cout<<endl<<"\tFile cannot be opened!";
		cout<<endl<<"\tPress any key to exit";
		
		getch( );
		return 0;
	}
	
	cout<<endl;
	
	for( int i = 0 ; i < ( spacing * 3 ) ; i++ )
	{
		cout<<" ";
	}
	
	cout<<"History"<<endl<<endl;
	
	while( fileIn.getline( str, 200, '\n' ) )
	{
		for( int i = 0 ; i < spacing ; i++ )
		{
			cout<<" ";
		}
		puts( str );
	}
	
	getch( );
	return 0;
}
