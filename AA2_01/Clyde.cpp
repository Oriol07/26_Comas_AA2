#include "Clyde.h"

///Funcions de la class Clyde

#pragma region Constructor/Destructor
//Constructor
Clyde::Clyde()
{
	charStepped = '*';
	dead = false;
}

Clyde::~Clyde() {


	 
}
#pragma endregion

#pragma region Position/Collision functions

//obtenim la posició
vec2 Clyde::getPosition()
{
	return pos;
}

void Clyde::setPosition(vec2 position) {

	pos = position;
}

void Clyde::setCharStepped(char step) {

	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR) {
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



Direction Clyde::getDir()
{
	return mov;
}

void Clyde::setDir(Direction d)
{
	mov = d;
}

void Clyde::setInitPos(vec2 position)
{
	initPos = position;
}

/********************************
* Retorna a la posició inicial. *
*********************************/
void Clyde::returnInitPos()
{
	pos = initPos;
}

/********************************
* Retorna la posició inicial	*
*********************************/
vec2 Clyde::getInitPos()
{
	return initPos;
}

#pragma endregion

#pragma region Other functions
bool Clyde::isDead()
{
	return dead;
}
void Clyde::setDead(bool d)
{
	dead = d;
}
#pragma endregion 