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

//Determinem la posicio
void Clyde::setPosition(vec2 position) {

	pos = position;
}

//Posarem quin es el caracter que es trapitja
void Clyde::setCharStepped(char step) {

	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR) {
		charStepped = step;
	}

	else {
		charStepped = ' ';
	}
}

//Obtindrem el caracter que trepitja
char Clyde::getCharStepped()
{
	return charStepped;
}


//Obtenim la direccio
Direction Clyde::getDir()
{
	return mov;
}

//Coloquem la direccio
void Clyde::setDir(Direction d)
{
	mov = d;
}
//Coloquem la direcció inicial
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
//Mirem si esta mort
bool Clyde::isDead()
{
	return dead;
}
//Determinem si esta mort
void Clyde::setDead(bool d)
{
	dead = d;
}
#pragma endregion 