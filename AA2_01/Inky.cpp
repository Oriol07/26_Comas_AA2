#include "Inky.h"

//#include "Enemies.h"
#include"Player.h"
#include "Constants.h"
#include "Types.h"
#include "Map.h"
#include "Blinky.h"



Inky::Inky()
{
	charStepped = '*';

}


Inky::~Inky()
{

}

void Inky::SetPosition(vec2 position)
{
	pos = position;
}

void Inky::SetCharStepped(char step)
{
	if (step != BLINKY || step != INKY || step != CLYDE || step != JUGADOR)
		charStepped = step;
	else
		charStepped = ' ';
}
bool Inky::TouchPlayer()
{
	return charStepped == JUGADOR;
}

Direction Inky::GetDir()
{
	return mov;
}

void Inky::SetDir(Direction d)
{
	mov = d;
}

char Inky::GetCharStepped()
{
	return charStepped;
}
vec2 Inky::GetPosition()
{
	return pos;
}


/*
Inky::Inky()
{

	pos.x = 3;
	pos.y = 18;
	lifes = 5;
	score = 0;
	playerRef = JUGADOR; //como se mueve igual q el, supongo q vale coger su ref??
	aMoure = false;
	gameEnded = false;
}


Inky::~Inky()
{


}

void Inky::UpdatePosition()
{

	if (_kbhit())
	{
		input = _getch();

		switch (input)
		{
		case 'W':
		case 'w': mov = Direction::UP;//ARRIBA
			//posY--;
			aMoure = true;
			break;
		case 'S':
		case 's': mov = Direction::DOWN;	//ABAJO
			aMoure = true;
			//posY++;
			break;
		case 'a':
		case 'A': mov = Direction::RIGHT;	//IZQUIERDA
			aMoure = true;
			//posX--;
			break;
		case 'd':
		case 'D': mov = Direction::LEFT;	//DERECHA
			aMoure = true;
			//posX++;
			break;
		case 27:
			gameEnded = true;
		default:
			mov = Direction::ZERO;
		}
	}


}

void Inky::SetPosition(vec2 position)
{
	position = pos;
}


int Inky::GetScore()
{
	return score; // lo devuelve, pero no lo muestra x pantalla no?S
}

void Inky::SetScore(int score)
{
	this->score = score;
}

int Inky::GetLifes()
{
	return lifes;
}

void Inky::SetLifes(int lifes)
{
	this->lifes = lifes;
}

void Inky::printInky()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //VERMELL
	//std::cout << "Score: " << GetScore() << lifes  << std::endl;
}

bool Inky::isGameEnded()
{
	return gameEnded;
}
*/