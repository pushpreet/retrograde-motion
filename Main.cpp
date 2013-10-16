#include <iostream>
#include <windows.h>
#include "cartesian.h"
#include "orbiter.h"
#include "line.h"

using namespace std;

void gotoxy(int x, int y)			// function to place the cursor at a position on the console specified by x and y
{
	COORD coord;					// structure COORD is present in windows.h
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);		// windows.h funtion to change the position of the cursor
}

void _interface( )
{
	HWND hWnd;
    SetConsoleTitle( "Retrograde Motion" );
    hWnd = FindWindow( NULL, "Retrograde Motion" );
    
	HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD screenSize = GetLargestConsoleWindowSize( hOut ); 		 
	SetConsoleScreenBufferSize( hOut, screenSize );
   	
    ShowWindow( GetConsoleWindow( ), SW_SHOWMAXIMIZED );
    
    system("color 0C");
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  
	cout<<endl;

	for ( int i = 0; i < 31; i++ )
		cout<<" ";

	

	cout<<"Retrograde Motion"<<endl;
};

int main( )
{
	_interface( );

	return 0;
}
