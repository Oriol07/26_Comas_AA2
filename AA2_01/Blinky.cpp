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
/************************
* Determina la posici�. *
*************************/
void Blinky::setPosition(vec2 position)
{
	pos = position;
}

/************************************
* Determina el character trepitjat. *
*************************************/
void Blinky::setCharStepped(char step)
{
	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR)
		charStepped = step;
	else
		charStepped = ' ';
}

/********************************
* Retorna a la direcci�. *
*********************************/
Direction Blinky::getDir()
{
	return mov;
}

/****************************
* Determinem la direcci�.   *
*****************************/
void Blinky::setDir(Direction d)
{
	mov = d;
}


/********************************
* Retorna el char trepitjat.    *
*********************************/
char Blinky::getCharStepped()
{
	return charStepped;
}

/********************************
* Obtenim la posici�.           *
*********************************/
vec2 Blinky::getPosition()
{
	return pos;
}
/********************************
* Determina la posici� inicial. *
*********************************/
void Blinky::setInitPos(vec2 position)
{	
	initPos = position;
}

/********************************
* Retorna a la posici� inicial. *
*********************************/
void Blinky::returnInitPos()
{
	pos = initPos;
}

/******************************
* Retorna la posici� inicial. *
*******************************/
vec2 Blinky::getInitPos()
{
	return initPos;
}

#pragma endregion

#pragma region Other functions

/**********************
* Mirem si esta mort. *
***********************/
bool Blinky::isDead()
{
	return dead;
}
/*************************************
* Determina si el jugador esta mort. *
**************************************/
void Blinky::setDead(bool d)
{
	dead = d;
}
#pragma endregion