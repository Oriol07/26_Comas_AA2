

#include "Blinky.h"



Blinky::Blinky()
{
	charStepped = '*';

}


Blinky::~Blinky()
{

}

void Blinky::SetPosition(vec2 position)
{
	pos = position;
}

void Blinky::SetCharStepped(char step)
{
	if (step != BLINKY || step != INKY || step != CLYDE || step != JUGADOR)
		charStepped = step;
	else
		charStepped = ' ';
}
bool Blinky::TouchPlayer()
{
	return charStepped == JUGADOR;
}

Direction Blinky::GetDir()
{
	return mov;
}

void Blinky::SetDir(Direction d)
{
	mov = d;
}

char Blinky::GetCharStepped()
{
	return charStepped;
}
vec2 Blinky::GetPosition()
{
	return pos;
}



