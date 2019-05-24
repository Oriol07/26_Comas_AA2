

#include"Map.h"
 

//Constructor
Map::Map(Player &jugador)
{
	bool colContades = false;
	char puntComa;
	filas = 0;
	columnas = 0;

	std::ifstream llegirConfig;
	llegirConfig.open("config.txt"); //obrim el fitcher ".txt"
	
	//Guardem la informacio de les files i columnes.
	llegirConfig >> filas; 
	llegirConfig >> puntComa;
	llegirConfig >> columnas;
	llegirConfig >> puntComa;

	/*
	Fem un array dinamic, amb dos espais de més, per evitar problemes de memória, 
	quan el jugador té com a próxima posició:(filas+1 || columnas +1);
	*/
	map = new char*[filas+2]; //reserva espacio para las filas

	for (int i = 0; i < filas+2; i++)
	{
		map[i] = new char[columnas]; // reserva espacio para las columnas
		llegirConfig.getline(map[i], columnas + 1); //leemos linia a linia, el config.
	}
	llegirConfig.close(); //tanquem el fitxer.
	
	/***************************************************
	* Llegida inicial dels elements del mapa.		   *
	* Busquem on estan els elements movibles del mapa. *
	****************************************************/
	for (int i = 1; i < filas + 1; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			switch (map[i][j])
			{
			case JUGADOR: //pos del jugador.
				jugador.pos.x = j;
				jugador.pos.y = i;
				setPlayer(jugador.pos);
				break;
			/*case BLINKY:
				Blinky b;
				vec2 p;
				p.x = j; p.y = i;
				b.SetPosition(p);
				setFirstDirBlinky(b);
				eBlinky.push_back(b);
				break; */
			case CLYDE: 
				Clyde c;
				vec2 pos;
				pos.x = j; pos.y = i;
				c.setPosition(pos);
				eClyde.push_back(c);
				break; 
			}
		}
	}
	

}

//Destructor
Map::~Map()
{
	delete[] map;
	map = nullptr;
}


int Map::getCols()
{
	return columnas;
}

int Map::getRows()
{
	return filas;
}

/********************************
* Posem la posició del jugador. *
*********************************/
void Map::setPlayer(vec2 pos)
{
	map[pos.y][pos.x] = JUGADOR;
}

/*********************************************************************************
* Comprovem si a la próxima posició és un punt ('*'), i retornem true, si ho és. *
**********************************************************************************/
bool Map::existPunt(vec2 pos, Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		return (map[pos.y - 1][pos.x] == PUNT);
	case Direction::DOWN:
		return (map[pos.y + 1][pos.x] == PUNT);
	case Direction::LEFT:
		return (map[pos.y][pos.x - 1] == PUNT);
	case Direction::RIGHT:
		return (map[pos.y][pos.x + 1] == PUNT);
	}

}


/*************************************************************************************
* Comprovem si la próxima posició del jugador és un mur, retornem true en cas que no.*
**************************************************************************************/
bool Map::noExistMur(vec2 pos, Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		return (map[pos.y - 1][pos.x] != MUR);
	case Direction::DOWN:
		return (map[pos.y + 1][pos.x] != MUR);
	case Direction::LEFT:
		return (map[pos.y][pos.x - 1] != MUR);
	case Direction::RIGHT:
		return (map[pos.y][pos.x + 1] != MUR);
	}
}


/******************************************************************************************************************
* En aquesta funció rebrem la proxima direcció, en cas que la posicio sigui un borde del map retornarem true,     *
* perque a l' hora de moure el jugador es mogui a l' altra banda.												  *
*******************************************************************************************************************/
bool Map::bordeMapa(vec2 pos, Direction dir)
{
	
	switch (dir)
	{
	case Direction::UP:
		return (pos.y == 1);
	case Direction::DOWN:
		return (pos.y == filas);
	case Direction::LEFT:
		return (pos.x == 0);
	case Direction::RIGHT:
		return (pos.x == columnas - 1);
	}
}

/**************************************
* Actualitza el moviment del jugador. *
***************************************/
void Map::movePlayer(vec2 &pos, Direction dir)
{
	vec2 newPos = pos;
	
	//calculem la nova posicio
	//Comprovem si el jugador no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
	switch (dir)
	{
		case Direction::LEFT: 
			if (!bordeMapa(pos, dir))
				newPos = { pos.x - 1, pos.y };
			else
				newPos = { columnas - 1, pos.y };
			break;

		case Direction::RIGHT: 
			if (!bordeMapa(pos, dir))
				newPos = { pos.x + 1, pos.y };
			else
				newPos = { 0, pos.y };
			break;

		case Direction::UP: 
			if (!bordeMapa(pos, dir))
				newPos = { pos.x, pos.y - 1 };
			else
				newPos = { pos.x, filas};
			break;

		case Direction::DOWN: 
			if (!bordeMapa(pos, dir))
				newPos = { pos.x, pos.y + 1 };
			else
				newPos = { pos.x, 1};
			break;
	}

	map[pos.y][pos.x] = NOTHING; // Un cop el jugador es mou, actualitzem la anterior ubicació amb ' ';
	map[newPos.y][newPos.x] = JUGADOR; //  Actualitzem la nova posicio amb la cara del jugador.
	pos = newPos;  
}

void Map::moveAI(Player player)
{
	for (int i = 0; i < eBlinky.size(); i++)
		moveBlinky(eBlinky[i]);
	for (int i = 0; i < eClyde.size(); i++)
		moveClyde(eClyde[i], player);
}

void Map::setFirstDirBlinky(Blinky &blink)
{
	bool haveDir = false;
	do {

		blink.SetDir(Direction(rand() % 4));
		if (noExistMur(blink.GetPosition(), blink.GetDir()))
		{
			haveDir = true;
		}
	} while (!haveDir);

}
void Map::moveBlinky(Blinky &blink)
{
	bool haveDir = false;
	do
	{
			switch (blink.GetDir())
			{
			case Direction::LEFT:
				if (!noExistMur(blink.GetPosition(), Direction::UP) && !noExistMur(blink.GetPosition(), Direction::DOWN) && !noExistMur(blink.GetPosition(), Direction::LEFT))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
			
				blink.SetDir(Direction(rand() % 3)); // 3 per evitar el Right
				if (blink.GetDir() != Direction::RIGHT)
				{
					if (noExistMur(blink.GetPosition(), blink.GetDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.SetDir(Direction::LEFT);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.SetDir(Direction::LEFT);
					haveDir = false;
				}
				break;
			case Direction::UP:
				if (!noExistMur(blink.GetPosition(), Direction::RIGHT) && !noExistMur(blink.GetPosition(), Direction::UP) && !noExistMur(blink.GetPosition(), Direction::LEFT))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.SetDir(Direction(rand() % 4)); //
				if (blink.GetDir() != Direction::DOWN)
				{
					if (noExistMur(blink.GetPosition(), blink.GetDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.SetDir(Direction::UP);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.SetDir(Direction::UP);
					haveDir = false;
				}
				break;

			case Direction::RIGHT:
				if (!noExistMur(blink.GetPosition(), Direction::RIGHT) && !noExistMur(blink.GetPosition(), Direction::DOWN) && !noExistMur(blink.GetPosition(), Direction::UP))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.SetDir(Direction(rand() % 4));
				if (blink.GetDir() != Direction::LEFT)
				{
					if (noExistMur(blink.GetPosition(), blink.GetDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.SetDir(Direction::RIGHT);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.SetDir(Direction::RIGHT);
					haveDir = false;
				}
				break;

			case Direction::DOWN:
				if (!noExistMur(blink.GetPosition(), Direction::RIGHT) && !noExistMur(blink.GetPosition(), Direction::DOWN) && !noExistMur(blink.GetPosition(), Direction::LEFT))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				else
				{
					blink.SetDir(Direction(rand() % 3 + 1));
					if (blink.GetDir() != Direction::UP)
					{
						if (noExistMur(blink.GetPosition(), blink.GetDir()))
						{
							haveDir = true;
							break;
						}
						else
						{
							blink.SetDir(Direction::DOWN);
							haveDir = false;
							break;
						}
					}
					else
					{
						blink.SetDir(Direction::DOWN);
						haveDir = false;
					}
					break;
				}
			case Direction::ZERO:
				haveDir = true;
				break;
			}

			
	} while (!haveDir);
	vec2 newPos = blink.GetPosition();

	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.
	switch (blink.GetDir())
	{
	case Direction::LEFT:
		if (!bordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x - 1, blink.GetPosition().y };
		else
			newPos = { getCols() - 1, blink.GetPosition().y };
		break;

	case Direction::RIGHT:
		if (!bordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x + 1, blink.GetPosition().y };
		else
			newPos = { 0, blink.GetPosition().y };
		break;

	case Direction::UP:
		if (!bordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x, blink.GetPosition().y - 1 };
		else
			newPos = { blink.GetPosition().x, getRows() };
		break;

	case Direction::DOWN:
		if (!bordeMapa(blink.GetPosition(), blink.GetDir()))
			if (noExistMur(blink.GetPosition(), blink.GetDir()))
			{
				newPos = { blink.GetPosition().x, blink.GetPosition().y + 1 };
			}
			else
				newPos = { blink.GetPosition().x, 1 };
		break;
	}
	if (blink.GetCharStepped() != BLINKY)
		map[blink.GetPosition().y][blink.GetPosition().x] = blink.GetCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;
	
		blink.SetCharStepped(NextCharPosition(blink.GetDir(), blink.GetPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

		map[newPos.y][newPos.x] = BLINKY; //  Actualitzem la nova posicio amb la cara del jugador.
	blink.SetPosition(newPos); //Actualitzem la nova posició;
}



bool Map::playerTouchEnemy()
{
	for (int i = 0; i < eBlinky.size(); i++)
	{
		if (eBlinky[i].TouchPlayer())
			return true;
	}
	return false;
}

char Map::NextCharPosition(Direction dir, vec2 nPos)
{
	
	switch (dir)
	{
	case Direction::UP:
		return map[nPos.y - 1][nPos.x];
	case Direction::DOWN:
		return map[nPos.y + 1][nPos.x];
	case Direction::LEFT:
		return map[nPos.y][nPos.x - 1];
	case Direction::RIGHT:
		return map[nPos.y][nPos.x + 1];
	}
}


//CLYDE



/*void Map::moveAI()
{
	for (int i = 0; i < eClyde.size(); i++)
		moveClyde(eClyde[i]);
}*/

/*void Map::setFirstDirClyde(Clyde &clyd)
{
	bool haveDir = false;
	do {

		blink.SetDir(Direction(rand() % 4));
		if (noExistMur(blink.GetPosition(), blink.GetDir()))
		{
			haveDir = true;
		}
	} while (!haveDir);

}*/



void Map::moveClyde(Clyde &clyd, Player player)
{
		vec2 newPos = clyd.getPosition();

		//calculem la nova posicio
		//Comprovem si en Clyde no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
		switch (player.mov)
		{
			case Direction::LEFT:
				if (noExistMur(clyd.getPosition(), Direction::RIGHT)) 
				{
					clyd.setDir(Direction::RIGHT);
				}
				else 
				{
					clyd.setDir(Direction::ZERO);
				}

				break;

			case Direction::RIGHT:
				if (noExistMur(clyd.getPosition(), Direction::LEFT)) 
				{
					clyd.setDir(Direction::LEFT);
				}
				else
				{
					clyd.setDir(Direction::ZERO);
				}
				break;

			case Direction::UP:
				if (noExistMur(clyd.getPosition(), Direction::DOWN)) 
				{
					clyd.setDir(Direction::DOWN);
				}

				else 
				{
					clyd.setDir(Direction::ZERO);
				}
				break;

			case Direction::DOWN:
				if (noExistMur(clyd.getPosition(), Direction::UP)) 
				{
					clyd.setDir(Direction::UP);
				}
				else 
				{
					clyd.setDir(Direction::ZERO);
				}
				break;
			case Direction::ZERO:
			{
				clyd.setDir(Direction::ZERO);
			}
		}



	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.

	//ESTO DE ABAJO AHORA LO CAMBIO
	switch (clyd.getDir())
	{
	case Direction::LEFT:
		if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
			newPos = { clyd.getPosition().x - 1, clyd.getPosition().y };
		else
			newPos = { getCols() - 1, clyd.getPosition().y };
		break;

	case Direction::RIGHT:
		if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
			newPos = { clyd.getPosition().x + 1, clyd.getPosition().y };
		else
			newPos = { 0, clyd.getPosition().y };
		break;

	case Direction::UP:
		if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
			newPos = { clyd.getPosition().x, clyd.getPosition().y - 1 };
		else
			newPos = { clyd.getPosition().x, getRows() };
		break;

	case Direction::DOWN:
		if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
			if (noExistMur(clyd.getPosition(), clyd.getDir()))
			{
				newPos = { clyd.getPosition().x, clyd.getPosition().y + 1 };
			}
			else
				newPos = { clyd.getPosition().x, 1 };
		break;
	}
	if (clyd.getCharStepped() != CLYDE)
		map[clyd.getPosition().y][clyd.getPosition().x] = clyd.getCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;

	clyd.setCharStepped(NextCharPosition(clyd.getDir(), clyd.getPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

	map[newPos.y][newPos.x] = CLYDE; //  Actualitzem la nova posicio amb la cara del jugador.
	clyd.setPosition(newPos); //Actualitzem la nova posició;
}


/*
bool Map::playerTouchEnemy()
{
	for (int i = 0; i < eBlinky.size(); i++)
	{
		if (eBlinky[i].TouchPlayer())
			return true;
	}
	return false;
}

char Map::NextCharPosition(Direction dir, vec2 nPos)
{

	switch (dir)
	{
	case Direction::UP:
		return map[nPos.y - 1][nPos.x];
	case Direction::DOWN:
		return map[nPos.y + 1][nPos.x];
	case Direction::LEFT:
		return map[nPos.y][nPos.x - 1];
	case Direction::RIGHT:
		return map[nPos.y][nPos.x + 1];
	}
}
  */














/********************************************
* Print dels elements del mapa per consola. *
*********************************************/
void Map::printMap()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Lletres de color blanc, per el titol.
	std::cout << "AA2: Desiree Moreno i Oriol Comas" << std::endl;
	for (int i = 1; i < filas + 1; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			switch (map[i][j])
			{
				case MUR:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1*16+1); // paredes de color azul.
					break;
				case PUNT:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // ... de color blanco
					break;
				case JUGADOR:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14*16); // la cara del player groga amb boca negra.
					break;
				case BLINKY:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 * 16); // la cara del player groga amb boca negra.
					break;
				case INKY:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 * 16); // la cara del player groga amb boca negra.
					break;
				case CLYDE:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 * 16); // la cara del player groga amb boca negra.
					break;
				case POWER_UP:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 * 16); // la cara del player groga amb boca negra.
					break;
			}
			std::cout << map[i][j];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); // La resta color dark.
		}
		std::cout << std::endl;
	}
}