

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
				posMap.x = j; posMap.y = i; // Aprofitem la p
				
				jugador.SetPosition(posMap);
				jugador.SetInitPos(jugador.GetPos());
				SetPlayer(jugador.GetPos());
				break;
			case BLINKY:
				posMap.x = j; posMap.y = i;
				b.SetPosition(posMap);
				SetFirstDirBlinky(b);
				eBlinky.push_back(b);
				break; 
			case CLYDE: 
				posMap.x = j; posMap.y = i;
				c.SetPosition(posMap);
				eClyde.push_back(c);
				break; 
			case INKY:
				posMap.x = j; posMap.y = i;
				this -> i.SetPosition(posMap);
				eInky.push_back(this -> i);
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
void Map::SetPlayer(vec2 pos)
{
	map[pos.y][pos.x] = JUGADOR;
}

/*********************************************************************************
* Comprovem si a la próxima posició és un punt ('*'), i retornem true, si ho és. *
**********************************************************************************/
bool Map::ExistPunt(vec2 pos, Direction dir)
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
bool Map::NoExistMur(vec2 pos, Direction dir)
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
bool Map::BordeMapa(vec2 pos, Direction dir)
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
void Map::MovePlayer(Player &player)
{
	vec2 newPos = player.GetPos();
	
	//calculem la nova posicio
	//Comprovem si el jugador no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
	switch (player.GetDir())
	{
		case Direction::LEFT: 
			if (!BordeMapa(player.GetPos(), player.GetDir()))
				newPos = { player.GetPos().x - 1, player.GetPos().y };
			else
				newPos = { columnas - 1, player.GetPos().y };
			break;

		case Direction::RIGHT: 
			if (!BordeMapa(player.GetPos(), player.GetDir()))
				newPos = {player.GetPos().x + 1, player.GetPos().y };
			else
				newPos = { 0, player.GetPos().y };
			break;

		case Direction::UP: 
			if (!BordeMapa(player.GetPos(), player.GetDir()))
				newPos = {player.GetPos().x, player.GetPos().y - 1 };
			else
				newPos = { player.GetPos().x, filas};
			break;

		case Direction::DOWN: 
			if (!BordeMapa(player.GetPos(), player.GetDir()))
				newPos = { player.GetPos().x, player.GetPos().y + 1 };
			else
				newPos = { player.GetPos().x, 1};
			break;
	}
	player.SetCharStepped(map[newPos.y][newPos.x]);

	map[player.GetPos().y][player.GetPos().x] = NOTHING; // Un cop el jugador es mou, actualitzem la anterior ubicació amb ' ';
	map[newPos.y][newPos.x] = JUGADOR; //  Actualitzem la nova posicio amb la cara del jugador.
	player.SetPosition(newPos);
}

/**************************************************************
* Actualizem tots els moviments dels enemics en els vectors.  *
***************************************************************/
void Map::MoveAI(Player player)
{
	for (int i = 0; i < eBlinky.size(); i++)
		MoveBlinky(eBlinky[i]);
	for (int i = 0; i < eClyde.size(); i++)
		MoveClyde(eClyde[i], player);
	for (int i = 0; i < eInky.size(); i++)
		MoveInky(eInky[i], player);
		
}

/******************************************
* Li donem la primera direcció al Blinky  *
*******************************************/
void Map::SetFirstDirBlinky(Blinky &blink)
{
	bool haveDir = false;
	do {

		blink.SetDir(Direction(rand() % 4));
		if (NoExistMur(blink.GetPosition(), blink.GetDir()))
		{
			haveDir = true;
		}
	} while (!haveDir);

}

/***************************************
* Actualitza el moviment de un Blinky. *
****************************************/
void Map::MoveBlinky(Blinky &blink)
{
	bool haveDir = false;
	do
	{
			switch (blink.GetDir())
			{
			case Direction::LEFT:
				if (!NoExistMur(blink.GetPosition(), Direction::UP) && !NoExistMur(blink.GetPosition(), Direction::DOWN) && !NoExistMur(blink.GetPosition(), Direction::LEFT))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
			
				blink.SetDir(Direction(rand() % 3)); // 3 per evitar el Right
				if (blink.GetDir() != Direction::RIGHT)
				{
					if (NoExistMur(blink.GetPosition(), blink.GetDir()))
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
				if (!NoExistMur(blink.GetPosition(), Direction::RIGHT) && !NoExistMur(blink.GetPosition(), Direction::UP) && !NoExistMur(blink.GetPosition(), Direction::LEFT))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.SetDir(Direction(rand() % 4)); //
				if (blink.GetDir() != Direction::DOWN)
				{
					if (NoExistMur(blink.GetPosition(), blink.GetDir()))
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
				if (!NoExistMur(blink.GetPosition(), Direction::RIGHT) && !NoExistMur(blink.GetPosition(), Direction::DOWN) && !NoExistMur(blink.GetPosition(), Direction::UP))
				{
					blink.SetDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.SetDir(Direction(rand() % 4));
				if (blink.GetDir() != Direction::LEFT)
				{
					if (NoExistMur(blink.GetPosition(), blink.GetDir()))
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
				if (!NoExistMur(blink.GetPosition(), Direction::RIGHT) && !NoExistMur(blink.GetPosition(), Direction::DOWN) && !NoExistMur(blink.GetPosition(), Direction::LEFT))
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
						if (NoExistMur(blink.GetPosition(), blink.GetDir()))
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
		if (!BordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x - 1, blink.GetPosition().y };
		else
			newPos = { getCols() - 1, blink.GetPosition().y };
		break;

	case Direction::RIGHT:
		if (!BordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x + 1, blink.GetPosition().y };
		else
			newPos = { 0, blink.GetPosition().y };
		break;

	case Direction::UP:
		if (!BordeMapa(blink.GetPosition(), blink.GetDir()))
			newPos = { blink.GetPosition().x, blink.GetPosition().y - 1 };
		else
			newPos = { blink.GetPosition().x, getRows() };
		break;

	case Direction::DOWN:
		if (!BordeMapa(blink.GetPosition(), blink.GetDir()))
			if (NoExistMur(blink.GetPosition(), blink.GetDir()))
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

/****************************************************
* Retorna true quan el player toca un altre enemic. *
*****************************************************/
bool Map::PlayerTouchEnemy(Player player)
{
	for (int i = 0; i < eBlinky.size(); i++)
	{
		if (eBlinky[i].TouchPlayer() || player.TouchEnemy())
			return true;
	}
	return false;
}

/********************************************************
* Retorna el caracter que hi haura a la seguent posicio	*
*********************************************************/
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


/*************************************
* Actualiza el moviment de un Clyde. *
**************************************/
void Map::MoveClyde(Clyde &clyd, Player player)
{
		vec2 newPos = clyd.GetPosition();

		//calculem la nova posicio
		//Comprovem si en Clyde no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
		switch (player.GetDir())
		{
			case Direction::LEFT:
				if (NoExistMur(clyd.GetPosition(), Direction::RIGHT)) 
				{
					clyd.SetDir(Direction::RIGHT);
				}
				else 
				{
					clyd.SetDir(Direction::ZERO);
				}

				break;

			case Direction::RIGHT:
				if (NoExistMur(clyd.GetPosition(), Direction::LEFT)) 
				{
					clyd.SetDir(Direction::LEFT);
				}
				else
				{
					clyd.SetDir(Direction::ZERO);
				}
				break;

			case Direction::UP:
				if (NoExistMur(clyd.GetPosition(), Direction::DOWN)) 
				{
					clyd.SetDir(Direction::DOWN);
				}

				else 
				{
					clyd.SetDir(Direction::ZERO);
				}
				break;

			case Direction::DOWN:
				if (NoExistMur(clyd.GetPosition(), Direction::UP)) 
				{
					clyd.SetDir(Direction::UP);
				}
				else 
				{
					clyd.SetDir(Direction::ZERO);
				}
				break;
			case Direction::ZERO:
			{
				clyd.SetDir(Direction::ZERO);
			}
		}



	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.

	switch (clyd.GetDir())
	{
	case Direction::LEFT:
		if (!BordeMapa(clyd.GetPosition(), clyd.GetDir()))
			newPos = { clyd.GetPosition().x - 1, clyd.GetPosition().y };
		else
			newPos = { getCols() - 1, clyd.GetPosition().y };
		break;

	case Direction::RIGHT:
		if (!BordeMapa(clyd.GetPosition(), clyd.GetDir()))
			newPos = { clyd.GetPosition().x + 1, clyd.GetPosition().y };
		else
			newPos = { 0, clyd.GetPosition().y };
		break;

	case Direction::UP:
		if (!BordeMapa(clyd.GetPosition(), clyd.GetDir()))
			newPos = { clyd.GetPosition().x, clyd.GetPosition().y - 1 };
		else
			newPos = { clyd.GetPosition().x, getRows() };
		break;

	case Direction::DOWN:
		if (!BordeMapa(clyd.GetPosition(), clyd.GetDir()))
			if (NoExistMur(clyd.GetPosition(), clyd.GetDir()))
			{
				newPos = { clyd.GetPosition().x, clyd.GetPosition().y + 1 };
			}
			else
				newPos = { clyd.GetPosition().x, 1 };
		break;
	}
	if (clyd.GetCharStepped() != CLYDE || clyd.GetCharStepped() != JUGADOR || clyd.GetCharStepped() != BLINKY || clyd.GetCharStepped() != INKY)
		map[clyd.GetPosition().y][clyd.GetPosition().x] = clyd.GetCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;

	clyd.SetCharStepped(NextCharPosition(clyd.GetDir(), clyd.GetPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

	map[newPos.y][newPos.x] = CLYDE; //  Actualitzem la nova posicio amb la cara del jugador.
	clyd.SetPosition(newPos); //Actualitzem la nova posició;
}

/************************************
* Actualiza el moviment de un Inky.	*
*************************************/
void Map::MoveInky(Inky &ink, Player player)
{
	vec2 newPos = ink.GetPosition();

	//calculem la nova posicio
	//Comprovem si en Clyde no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
	switch (player.GetDir())
	{
		case Direction::LEFT:
			if (NoExistMur(ink.GetPosition(), player.GetDir()))
			{
				ink.SetDir(player.GetDir());
			}
			else
			{
				ink.SetDir(Direction::ZERO);
			}

			break;

		case Direction::RIGHT:
			if (NoExistMur(ink.GetPosition(), player.GetDir()))
			{
				ink.SetDir(player.GetDir());
			}
			else
			{
				ink.SetDir(Direction::ZERO);
			}
			break;

		case Direction::UP:
			if (NoExistMur(ink.GetPosition(), player.GetDir()))
			{
				ink.SetDir(Direction::UP);
			}

			else
			{
				ink.SetDir(Direction::ZERO);
			}
			break;

		case Direction::DOWN:
			if (NoExistMur(ink.GetPosition(), player.GetDir()))
			{
				ink.SetDir(Direction::DOWN);
			}
			else
			{
				ink.SetDir(Direction::ZERO);
			}
			break;
		case Direction::ZERO:
		{
			ink.SetDir(Direction::ZERO);
		}
	}



	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.

	switch (ink.GetDir())
	{
		case Direction::LEFT:
			if (!BordeMapa(ink.GetPosition(), ink.GetDir()))
				newPos = { ink.GetPosition().x - 1, ink.GetPosition().y };
			else
				newPos = { getCols() - 1, ink.GetPosition().y };
			break;

		case Direction::RIGHT:
			if (!BordeMapa(ink.GetPosition(), ink.GetDir()))
				newPos = { ink.GetPosition().x + 1, ink.GetPosition().y };
			else
				newPos = { 0, ink.GetPosition().y };
			break;

		case Direction::UP:
			if (!BordeMapa(ink.GetPosition(), ink.GetDir()))
				newPos = { ink.GetPosition().x, ink.GetPosition().y - 1 };
			else
				newPos = { ink.GetPosition().x, getRows() };
			break;

		case Direction::DOWN:
			if (!BordeMapa(ink.GetPosition(), ink.GetDir()))
				if (NoExistMur(ink.GetPosition(), ink.GetDir()))
				{
					newPos = { ink.GetPosition().x, ink.GetPosition().y + 1 };
				}
				else
					newPos = { ink.GetPosition().x, 1 };
			break;
	}

	if (ink.GetCharStepped() != CLYDE || ink.GetCharStepped() != JUGADOR || ink.GetCharStepped() != BLINKY || ink.GetCharStepped() != INKY )
		map[ink.GetPosition().y][ink.GetPosition().x] = ink.GetCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;

	ink.SetCharStepped(NextCharPosition(ink.GetDir(), ink.GetPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

	map[newPos.y][newPos.x] = INKY; //  Actualitzem la nova posicio amb la cara del jugador.
	ink.SetPosition(newPos); //Actualitzem la nova posició;

}
/********************************************
* Print dels elements del mapa per consola. *
*********************************************/
void Map::PrintMap()
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