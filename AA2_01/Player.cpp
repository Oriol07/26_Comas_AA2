
#include "Player.h"

//Constructor auto
Player::Player()
{
	pos.x = 3;
	pos.y = 18;
	lifes = 3;
	score = 0;
	toMove = false;
}

//Constructor amb posicions i vides.
Player::Player(int posX, int posY, int lifes)
{
	pos.x = posX;
	pos.y = posY;
	score = 0;
	this->lifes = lifes; 
}

//Destructor
Player::~Player()
{
}


/*********************************
* Coloca la posició del jugador. *
**********************************/
void Player::SetPosition(vec2 position)
{
	pos = position;
}

/**********************
* Retorna la posició. *
***********************/
vec2 Player::GetPos()
{
	return pos;
}

/*****************************************
* Guarda la posició inicial del jugador. *
******************************************/
void Player::SetInitPos(vec2 position)
{
	initPos = position;
}

/******************************
* Retorna la posició inicial. *
*******************************/
void Player::ReturnInitPos()
{
	pos = initPos;
}

bool Player::CanMove()
{
	return toMove;
}

void Player::SetCanMove(bool can)
{
	toMove = can;
}

Direction Player::GetDir()
{
	return mov;
}

void Player::SetDir(Direction d)
{
	mov = d;
}
/*********************************
* Retorna true si toca l'enemic. *
**********************************/
bool Player::TouchEnemy()
{
	return (charStepped == BLINKY || charStepped == CLYDE || charStepped == INKY);
}

/************************************
* Retorna la puntuació del jugador. *
*************************************/
int Player::GetScore()
{
	return score;
}

/***********************************
* Cambia la puntuació del jugador. *
************************************/
void Player::SetScore(int score)
{
	this->score = score;
}

/*******************************
* Retorna la vida del jugador. *
********************************/
int Player::GetLifes()
{
	return lifes;
}

/******************************
* Cambia la vida del jugador. *
*******************************/
void Player::SetLifes(int lifes)
{
	this->lifes = lifes;
}

/********************************
* Imprimeix la HUD del jugador. *
*********************************/
void Player::PrintPlayer()
{

	//
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "Score: " << GetScore() << "         Lifes: " << lifes << std::endl;
}

/************************************
* Determina el caracter trepitjat. *								
*************************************/
void Player::SetCharStepped(char stepp)
{
	charStepped = stepp;
}