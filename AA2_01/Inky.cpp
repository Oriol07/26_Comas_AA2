#include "Inky.h"

///Funcions de la class Blinky

#pragma region Constructor/Destructor
//Constructor
Inky::Inky()
{
	charStepped = '*';
	dead = false;
}

//Destructor
Inky::~Inky()
{

}
#pragma endregion

#pragma region Position/Collision functions
/*********************************
* Marquem la posició del jugador *
**********************************/
void Inky::setPosition(vec2 position)
{
	pos = position;
}

/************************************
* Guardem el caracter que trepitja. *
*************************************/
void Inky::setCharStepped(char step)
{
	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR)
		charStepped = step;
	else
		charStepped = ' ';
}

/*********************************************
* Mirem si ha tocat al jugador al trepitjar. *
**********************************************/
bool Inky::touchPlayer()
{
	return charStepped == JUGADOR;
}

/**********************************************
* Obtenim la direcció a la que s'ha de moure. *
***********************************************/
Direction Inky::getDir()
{
	return mov;
}

/**********************************************
* Marquem la direcció a la que s'ha de moure. *
***********************************************/
void Inky::setDir(Direction d)
{
	mov = d;
}

/********************************
* Obtenim el caracter trepitjat *
*********************************/
char Inky::getCharStepped()
{
	return charStepped;
}

/**********************************
* Obtenim la posició del jugador. *
***********************************/
vec2 Inky::getPosition()
{
	return pos;
}

/****************************
* Marca la posició inicial. *
*****************************/
void Inky::setInitPos(vec2 position)
{
	initPos = position;
}

/********************************
* Retorna a la posició inicial. *
*********************************/
void Inky::returnInitPos()
{
	pos = initPos;
}

/******************************
* Retorna la posició inicial. *
*******************************/
vec2 Inky::getInitPos()
{
	return initPos;
}

#pragma endregion

#pragma region Other functions
bool Inky::isDead()
{
	return dead;
}
void Inky::setDead(bool d)
{
	dead = d;
}
#pragma endregion