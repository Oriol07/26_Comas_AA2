
#include "Player.h"

///Funcions de la class Player

#pragma region Constructor/Destructor
//Constructor auto
Player::Player()
{
	pos.x = 3;
	pos.y = 18;
	lifes = 3;
	score = 0;
	toMove = false;
	hasPowerUp = false;
}


//Destructor
Player::~Player()
{
}

#pragma endregion

#pragma region Postion/Collision functions
/*********************************
* Coloca la posició del jugador. *
**********************************/
void Player::setPosition(vec2 position)
{
	pos = position;
}

/**********************
* Retorna la posició. *
***********************/
vec2 Player::getPos()
{
	return pos;
}

/*****************************************
* Guarda la posició inicial del jugador. *
******************************************/
void Player::setInitPos(vec2 position)
{
	initPos = position;
}

/******************************
* Retorna la posició inicial. *
*******************************/
void Player::returnInitPos()
{
	pos = initPos;
}

/**************************************
* Retorna si el jugador es pot moure. *
***************************************/
bool Player::canMove()
{
	return toMove;
}

/********************************
* Definim si es pot moure o no. *
*********************************/
void Player::setCanMove(bool can)
{
	toMove = can;
}

/***********************
* Retorna la direcció. *
************************/
Direction Player::getDir()
{
	return mov;
}

/***********************
* Cambia la direcció.  *
************************/
void Player::setDir(Direction d)
{
	mov = d;
}

/*********************************
* Retorna true si toca l'enemic. *
**********************************/
bool Player::touchEnemy()
{
	return (charStepped == BLINKY || charStepped == CLYDE || charStepped == INKY);
}

/************************************
* Retorna true si toca el Power_UP. *
*************************************/
bool Player::touchPowerUp()
{
	return charStepped == POWER_UP;
}

/************************************
* Determina el caracter trepitjat.  *
*************************************/
void Player::setCharStepped(char stepp)
{
	charStepped = stepp;
}

/******************************
* Obtenim el char trepitjat.  *
*******************************/
char Player::getCharStepped()
{
	return charStepped;
}

#pragma endregion

#pragma region Score functions
/************************************
* Retorna la puntuació del jugador. *
*************************************/
int Player::getScore()
{
	return score;
}

/***********************************
* Cambia la puntuació del jugador. *
************************************/
void Player::setScore(int score)
{
	this->score = score;
}

/****************************************************
* Mirem si el jugador té el power up activat o no.  *
*****************************************************/
bool Player::getHasPowerUp()
{
	return hasPowerUp;
}

/********************************************
* Determinem si el jugador té un power up.	*
*********************************************/
void Player::setHasPowerUp(bool pU)
{
	hasPowerUp = pU;
}

#pragma endregion

#pragma region Lifes functions
/*******************************
* Retorna la vida del jugador. *
********************************/
int Player::getLifes()
{
	return lifes;
}

/******************************
* Cambia la vida del jugador. *
*******************************/
void Player::setLifes(int lifes)
{
	this->lifes = lifes;
}

#pragma endregion

#pragma region Time functions
/********************************************************
* Determinem el temps que queda per acabar el PowerUp	*
*********************************************************/
void Player::setTimePowerUp(int time)
{
	powerUpTime = time;
}

/********************************************************
* Obtenim el temps que queda per acabar el PowerUp.		*
*********************************************************/
int Player::getTimePowerUp()
{
	return powerUpTime;
}

#pragma endregion

#pragma region Print functions
/********************************
* Imprimeix la HUD del jugador. *
*********************************/
void Player::printPlayer()
{

	//
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "Score: " << getScore() << "         Lifes: " << lifes << std::endl;
}
#pragma endregion