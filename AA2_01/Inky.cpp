#include "Inky.h"

//Constructor
Inky::Inky()
{
	charStepped = '*';

}

//Destructor
Inky::~Inky()
{

}

/*********************************
* Marquem la posici� del jugador *
**********************************/
void Inky::SetPosition(vec2 position)
{
	pos = position;
}

/************************************
* Guardem el caracter que trepitja. *
*************************************/
void Inky::SetCharStepped(char step)
{
	if (step != BLINKY && step != INKY && step != CLYDE && step != JUGADOR)
		charStepped = step;
	else
		charStepped = ' ';
}

/*********************************************
* Mirem si ha tocat al jugador al trepitjar. *
**********************************************/
bool Inky::TouchPlayer()
{
	return charStepped == JUGADOR;
}

/**********************************************
* Obtenim la direcci� a la que s'ha de moure. *
***********************************************/
Direction Inky::GetDir()
{
	return mov;
}

/**********************************************
* Marquem la direcci� a la que s'ha de moure. *
***********************************************/
void Inky::SetDir(Direction d)
{
	mov = d;
}

/********************************
* Obtenim el caracter trepitjat *
*********************************/
char Inky::GetCharStepped()
{
	return charStepped;
}

/**********************************
* Obtenim la posici� del jugador. *
***********************************/
vec2 Inky::GetPosition()
{
	return pos;
}

/****************************
* Marca la posici� inicial. *
*****************************/
void Inky::SetInitPos(vec2 position)
{
	initPos = position;
}

/********************************
* Retorna a la posici� inicial. *
*********************************/
void Inky::ReturnInitPos()
{
	pos = initPos;
}

/******************************
* Retorna la posici� inicial. *
*******************************/
vec2 Inky::GetInitPos()
{
	return initPos;
}