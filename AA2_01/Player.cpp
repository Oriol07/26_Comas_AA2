
#include "Player.h"

//Constructor auto
Player::Player()
{
	pos.x = 3;
	pos.y = 18;
	lifes = 3;
	score = 0;
	aMoure = false;
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
	position = pos;
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
void Player::printPlayer()
{

	//
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "Score: " << GetScore() << "         Lifes: " << lifes << std::endl;
}

