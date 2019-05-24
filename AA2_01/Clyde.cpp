#include "Clyde.h"

//#include "Enemies.h"
#include"Player.h"
#include "Constants.h"
#include "Types.h"
#include "Map.h"
#include "Clyde.h"

/////////


Clyde::Clyde()

{

	charStepped = '*';

}

Clyde::~Clyde() {


	 
}

vec2 Clyde::getPosition()
{
	return pos;
}

void Clyde::setPosition(vec2 position) {

	pos = position;
}

void Clyde::setCharStepped(char step) {

	if (step != BLINKY || step != INKY || step != CLYDE || step != JUGADOR) {
		charStepped = step;
	}

	else {
		charStepped = ' ';
	}
}
char Clyde::getCharStepped()
{
	return charStepped;
}

bool Clyde::touchPlayer(){

	return charStepped == JUGADOR; 
}


Direction Clyde::getDir()
{
	return mov;
}

void Clyde::setDir(Direction d)
{
	mov = d;
}

