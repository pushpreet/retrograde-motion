#include <iostream>
#include <windows.h>
#include <dos.h>
#include "orbiter.h"
#include "line.h"

using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main( )
{
	orbiter orb;
	orb.setOrbitRadius( 10.0 );
	orb.setVelocity(10.0,'a');

	for (double i = 0.0; i < 100; i+=0.01)
	{
		orb.calcPosition( i ) ;
		gotoxy(10+orb.getPos().x,10+orb.getPos().y);
		cout<<".";
		Sleep(500);
	}

	return 0;
}