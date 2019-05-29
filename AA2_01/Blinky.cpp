#include "Blinky.h"

///Funcions de la class Blinky

#pragma region Constructor/Destructor
//Constructor
Blinky::Blinky()
{
	charStepped = '*';
	dead = false;

}

//Destructor
Blinky::~Blinky()
{

}
#pragma endregion

#pragma region Position/Collision functions
void Blinky::setPosition(vec2 position)
{
	pos = position;
}

void Blinky::setCharStepped(char step)
{
	if (step != BLINKY && step != INKY && step != CLYDE)
		charStepped = step;
	else
		charStepped = ' ';
}
bool Blinky::touchPlayer()
{
	return charStepped == JUGADOR;
}

Direction Blinky::getDir()
{
	return mov;
}

void Blinky::setDir(Direction d)
{
	mov = d;
}

char Blinky::getCharStepped()
{
	return charStepped;
}
vec2 Blinky::getPosition()
{
	return pos;
}

void Blinky::setInitPos(vec2 position)
{	
	initPos = position;
}

/********************************
* Retorna a la posició inicial. *
*********************************/
void Blinky::returnInitPos()
{
	pos = initPos;
}

/******************************
* Retorna la posició inicial. *
*******************************/
vec2 Blinky::getInitPos()
{
	return initPos;
}

#pragma endregion

#pragma region Other functions
bool Blinky::isDead()
{
	return dead;
}
void Blinky::setDead(bool d)
{
	dead = d;
}
#pragma endregion