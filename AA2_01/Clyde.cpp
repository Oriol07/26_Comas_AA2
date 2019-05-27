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

vec2 Clyde::GetPosition()
{
	return pos;
}

void Clyde::SetPosition(vec2 position) {

	pos = position;
}

void Clyde::SetCharStepped(char step) {

	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR) {
		charStepped = step;
	}

	else {
		charStepped = ' ';
	}
}
char Clyde::GetCharStepped()
{
	return charStepped;
}

bool Clyde::TouchPlayer(){

	return charStepped == JUGADOR; 
}


Direction Clyde::GetDir()
{
	return mov;
}

void Clyde::SetDir(Direction d)
{
	mov = d;
}

void Clyde::SetInitPos(vec2 position)
{
	initPos = position;
}

/********************************
* Retorna a la posició inicial. *
*********************************/
void Clyde::ReturnInitPos()
{
	pos = initPos;
}

/********************************
* Retorna la posició inicial	*
*********************************/
vec2 Clyde::GetInitPos()
{
	return initPos;
}
