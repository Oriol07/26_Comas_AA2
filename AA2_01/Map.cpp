

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

	/********************************************************************************
	* Fem un array dinamic, amb dos espais de més, per evitar problemes de memória,	*
	* quan el jugador té com a próxima posició: (filas+1 || columnas +1);			*
	*********************************************************************************/
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
				
				jugador.setPosition(posMap);
				jugador.setInitPos(jugador.getPos());
				setPlayer(jugador.getPos());
				break;
			case BLINKY:
				posMap.x = j; posMap.y = i;
				b.setPosition(posMap);
				b.setInitPos(b.getPosition());
				setFirstDirBlinky(b);
				eBlinky.push_back(b);
				break; 
			case CLYDE: 
				posMap.x = j; posMap.y = i;
				c.setPosition(posMap);
				c.setInitPos(posMap);
				eClyde.push_back(c);
				break; 
			case INKY:
				posMap.x = j; posMap.y = i;
				this -> i.setPosition(posMap);
				this -> i.setInitPos(posMap);

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
void Map::movePlayer(Player &player)
{
	vec2 newPos = player.getPos();
	
	//calculem la nova posicio
	//Comprovem si el jugador no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
	switch (player.getDir())
	{
		case Direction::LEFT: 
			if (!bordeMapa(player.getPos(), player.getDir()))
				newPos = { player.getPos().x - 1, player.getPos().y };
			else
				newPos = { columnas - 1, player.getPos().y };
			break;

		case Direction::RIGHT: 
			if (!bordeMapa(player.getPos(), player.getDir()))
				newPos = {player.getPos().x + 1, player.getPos().y };
			else
				newPos = { 0, player.getPos().y };
			break;

		case Direction::UP: 
			if (!bordeMapa(player.getPos(), player.getDir()))
				newPos = {player.getPos().x, player.getPos().y - 1 };
			else
				newPos = { player.getPos().x, filas};
			break;

		case Direction::DOWN: 
			if (!bordeMapa(player.getPos(), player.getDir()))
				newPos = { player.getPos().x, player.getPos().y + 1 };
			else
				newPos = { player.getPos().x, 1};
			break;
	}
	player.setCharStepped(map[newPos.y][newPos.x]);

	map[player.getPos().y][player.getPos().x] = NOTHING; // Un cop el jugador es mou, actualitzem la anterior ubicació amb ' ';
	map[newPos.y][newPos.x] = JUGADOR; //  Actualitzem la nova posicio amb la cara del jugador.
	player.setPosition(newPos);
}

/******************************************
* Li donem la primera direcció al Blinky. *
*******************************************/
void Map::setFirstDirBlinky(Blinky &blink)
{
	bool haveDir = false;
	do {

		blink.setDir(Direction(rand() % 4));
		if (noExistMur(blink.getPosition(), blink.getDir()))
		{
			haveDir = true;
		}
	} while (!haveDir);

}

/***************************************
* Actualitza el moviment de un Blinky. *
****************************************/
void Map::moveBlinky(Blinky &blink)
{
	bool haveDir = false;
	do
	{
			switch (blink.getDir())
			{
			case Direction::LEFT:
				if (!noExistMur(blink.getPosition(), Direction::UP) && !noExistMur(blink.getPosition(), Direction::DOWN) && !noExistMur(blink.getPosition(), Direction::LEFT))
				{
					blink.setDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
			
				blink.setDir(Direction(rand() % 3)); // 3 per evitar el Right
				if (blink.getDir() != Direction::RIGHT)
				{
					if (noExistMur(blink.getPosition(), blink.getDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.setDir(Direction::LEFT);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.setDir(Direction::LEFT);
					haveDir = false;
				}
				break;
			case Direction::UP:
				if (!noExistMur(blink.getPosition(), Direction::RIGHT) && !noExistMur(blink.getPosition(), Direction::UP) && !noExistMur(blink.getPosition(), Direction::LEFT))
				{
					blink.setDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.setDir(Direction(rand() % 4)); //
				if (blink.getDir() != Direction::DOWN)
				{
					if (noExistMur(blink.getPosition(), blink.getDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.setDir(Direction::UP);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.setDir(Direction::UP);
					haveDir = false;
				}
				break;

			case Direction::RIGHT:
				if (!noExistMur(blink.getPosition(), Direction::RIGHT) && !noExistMur(blink.getPosition(), Direction::DOWN) && !noExistMur(blink.getPosition(), Direction::UP))
				{
					blink.setDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				blink.setDir(Direction(rand() % 4));
				if (blink.getDir() != Direction::LEFT)
				{
					if (noExistMur(blink.getPosition(), blink.getDir()))
					{
						haveDir = true;
						break;
					}
					else
					{
						blink.setDir(Direction::RIGHT);
						haveDir = false;
						break;
					}
				}
				else
				{
					blink.setDir(Direction::RIGHT);
					haveDir = false;
				}
				break;

			case Direction::DOWN:
				if (!noExistMur(blink.getPosition(), Direction::RIGHT) && !noExistMur(blink.getPosition(), Direction::DOWN) && !noExistMur(blink.getPosition(), Direction::LEFT))
				{
					blink.setDir(Direction::ZERO);
					haveDir = true; //Que es quedi quiet ja que no tindra cap a on anar i evitar que el joc es colapsi.
					break;
				}
				else
				{
					blink.setDir(Direction(rand() % 3 + 1));
					if (blink.getDir() != Direction::UP)
					{
						if (noExistMur(blink.getPosition(), blink.getDir()))
						{
							haveDir = true;
							break;
						}
						else
						{
							blink.setDir(Direction::DOWN);
							haveDir = false;
							break;
						}
					}
					else
					{
						blink.setDir(Direction::DOWN);
						haveDir = false;
					}
					break;
				}
			case Direction::ZERO:
				haveDir = true;
				break;
			}

			
	} while (!haveDir);
	vec2 newPos = blink.getPosition();

	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.
	switch (blink.getDir())
	{
	case Direction::LEFT:
		if (!bordeMapa(blink.getPosition(), blink.getDir()))
			newPos = { blink.getPosition().x - 1, blink.getPosition().y };
		else
			newPos = { columnas - 1, blink.getPosition().y };
		break;

	case Direction::RIGHT:
		if (!bordeMapa(blink.getPosition(), blink.getDir()))
			newPos = { blink.getPosition().x + 1, blink.getPosition().y };
		else
			newPos = { 0, blink.getPosition().y };
		break;

	case Direction::UP:
		if (!bordeMapa(blink.getPosition(), blink.getDir()))
			newPos = { blink.getPosition().x, blink.getPosition().y - 1 };
		else
			newPos = { blink.getPosition().x, filas };
		break;

	case Direction::DOWN:
		if (!bordeMapa(blink.getPosition(), blink.getDir()))
			newPos = { blink.getPosition().x, blink.getPosition().y + 1 };
		else
				newPos = { blink.getPosition().x, 1 };
		break;
	}
	if (blink.getCharStepped() != BLINKY)
		map[blink.getPosition().y][blink.getPosition().x] = blink.getCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;
	
		blink.setCharStepped(nextCharPosition(blink.getDir(), blink.getPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

		map[newPos.y][newPos.x] = BLINKY; //  Actualitzem la nova posicio amb la cara del jugador.
	blink.setPosition(newPos); //Actualitzem la nova posició;
}

/****************************************************
* Retorna true quan el player toca un altre enemic. *
*****************************************************/
bool Map::playertouchEnemy(Player player)
{
	if (player.getHasPowerUp())
	{
		posMap = player.getPos();
		for (int i = 0; i < eBlinky.size(); i++)
		{
			if ((eBlinky[i].getPosition().x == player.getPos().x) && (eBlinky[i].getPosition().y == player.getPos().y))
			{
				eBlinky[i].setDead(true);
				map[eBlinky[i].getPosition().y][eBlinky[i].getPosition().x] = JUGADOR;
				return true;
			}
		}
		for (int i = 0; i < eInky.size(); i++)
		{
			if ((eInky[i].getPosition().x == player.getPos().x) && (eInky[i].getPosition().y == player.getPos().y))
			{
				eInky[i].setDead(true);
				map[eInky[i].getPosition().y][eInky[i].getPosition().x] = JUGADOR;
				return true;
			}

		}
		for (int i = 0; i < eClyde.size(); i++)
		{
			if ((eClyde[i].getPosition().x == player.getPos().x) && (eClyde[i].getPosition().y == player.getPos().y))
			{
				eClyde[i].setDead(true); 
				map[eClyde[i].getPosition().y][eClyde[i].getPosition().x] = JUGADOR;
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < eBlinky.size(); i++)
		{
			if ((eBlinky[i].getPosition().x == player.getPos().x) && (eBlinky[i].getPosition().y == player.getPos().y))
			{
				eBlinky[i].setCharStepped(' '); player.setCharStepped(' ');
				return true;
			}
				
		}
		for (int i = 0; i < eClyde.size(); i++)
		{
			if ((eClyde[i].getPosition().x == player.getPos().x) && (eClyde[i].getPosition().y == player.getPos().y))
			{
				eClyde[i].setCharStepped(' '); player.setCharStepped(' ');
				return true;
			}
		}
		for (int i = 0; i < eInky.size(); i++)
		{
			if ((eInky[i].getPosition().x == player.getPos().x) && (eInky[i].getPosition().y == player.getPos().y))
			{
				eInky[i].setCharStepped(' '); player.setCharStepped(' ');
				return true;
			}
				
		}
	}
	return false;
}

/********************************************************
* Retorna el caracter que hi haura a la seguent posicio	*
*********************************************************/
char Map::nextCharPosition(Direction dir, vec2 nPos)
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
		case Direction::ZERO:
			return map[nPos.y][nPos.x];
	}
}


/*************************************
* Actualiza el moviment de un Clyde. *
**************************************/
void Map::moveClyde(Clyde &clyd, Player player)
{
		vec2 newPos = clyd.getPosition();

		//calculem la nova posicio
		//Comprovem si en Clyde no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
		switch (player.getDir())
		{
		case Direction::LEFT:

			clyd.setDir(Direction::RIGHT);

			break;

		case Direction::RIGHT:
			
				clyd.setDir(Direction::LEFT);
			
			
			break;

		case Direction::UP:

				clyd.setDir(Direction::DOWN);
		
			break;

		case Direction::DOWN:
				clyd.setDir(Direction::UP);
		
			break;
		case Direction::ZERO:
		{
			//clyd.setDir(Direction::ZERO);
		}
	}



		//calculem la nova posicio
		//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.

		switch (clyd.getDir())
		{
		case Direction::LEFT:
			if (noExistMur(clyd.getPosition(), Direction::LEFT))
			{
				if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
					newPos = { clyd.getPosition().x - 1, clyd.getPosition().y };
				else
					newPos = { columnas - 1, clyd.getPosition().y };
				
			}
			else
				clyd.setDir(Direction::ZERO);
			break;
		case Direction::RIGHT:
			if (noExistMur(clyd.getPosition(), Direction::RIGHT))
			{
				if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
					newPos = { clyd.getPosition().x + 1, clyd.getPosition().y };
				else
					newPos = { 0, clyd.getPosition().y };
			}
			else clyd.setDir(Direction::ZERO);
			break;

		case Direction::UP:
			if (noExistMur(clyd.getPosition(), Direction::UP))
			{
				if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
					newPos = { clyd.getPosition().x, clyd.getPosition().y - 1 };
				else
					newPos = { clyd.getPosition().x, filas };
			}
			else clyd.setDir(Direction::ZERO);
			break;

		case Direction::DOWN:
			if (noExistMur(clyd.getPosition(), Direction::DOWN))
			{
				if (!bordeMapa(clyd.getPosition(), clyd.getDir()))
					newPos = { clyd.getPosition().x, clyd.getPosition().y + 1 };
				else
					newPos = { clyd.getPosition().x, 1 };
			}
			else clyd.setDir(Direction::ZERO);
			break;
		}
		if (nextCharPosition(clyd.getDir(), clyd.getPosition()) != CLYDE || nextCharPosition(clyd.getDir(), clyd.getPosition()) != JUGADOR || nextCharPosition(clyd.getDir(), clyd.getPosition()) != BLINKY || nextCharPosition(clyd.getDir(), clyd.getPosition()) != INKY)
			map[clyd.getPosition().y][clyd.getPosition().x] = clyd.getCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;

		clyd.setCharStepped(nextCharPosition(clyd.getDir(), clyd.getPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

		map[newPos.y][newPos.x] = CLYDE; //  Actualitzem la nova posicio amb la cara del jugador.
		clyd.setPosition(newPos); //Actualitzem la nova posició;
	}

/************************************
* Actualiza el moviment de un Inky.	*
*************************************/
void Map::moveInky(Inky &ink, Player player)
{
	vec2 newPos = ink.getPosition();

	//calculem la nova posicio
	//Comprovem si en Clyde no es troba en un borde del mapa, en cas que si, el jugador serà teletransportat a l'altra banda.
	switch (player.getDir())
	{
		case Direction::LEFT:
			ink.setDir(player.getDir());
			break;

		case Direction::RIGHT:
			ink.setDir(player.getDir());
			break;

		case Direction::UP:
			ink.setDir(Direction::UP);
			break;

		case Direction::DOWN:
			ink.setDir(Direction::DOWN);
			break;
	}



	//calculem la nova posicio
	//Comprovem si el Binky no es troba en un borde del mapa, en cas que si, el Binky serà teletransportat a l'altra banda.

	switch (ink.getDir())
	{
		case Direction::LEFT:
			if (noExistMur(ink.getPosition(), ink.getDir()))
			{
				if (!bordeMapa(ink.getPosition(), ink.getDir()))
					newPos = { ink.getPosition().x - 1, ink.getPosition().y };
				else
					newPos = { columnas - 1, ink.getPosition().y };
				
			}
			else ink.setDir(Direction::ZERO);
			break;
		case Direction::RIGHT:
			if (noExistMur(ink.getPosition(), ink.getDir()))
			{
				if (!bordeMapa(ink.getPosition(), ink.getDir()))
					newPos = { ink.getPosition().x + 1, ink.getPosition().y };
				else
					newPos = { 0, ink.getPosition().y };
			}
			else ink.setDir(Direction::ZERO);
			break;

		case Direction::UP:
			if (noExistMur(ink.getPosition(), ink.getDir()))
			{
				if (!bordeMapa(ink.getPosition(), ink.getDir()))
					newPos = { ink.getPosition().x, ink.getPosition().y - 1 };
				else
					newPos = { ink.getPosition().x, filas };
			}
			else ink.setDir(Direction::ZERO);
			break;

		case Direction::DOWN:
			if (noExistMur(ink.getPosition(), ink.getDir()))
			{
				if (!bordeMapa(ink.getPosition(), ink.getDir()))
					newPos = { ink.getPosition().x, ink.getPosition().y + 1 };
				else
					newPos = { ink.getPosition().x, 1 };
			}
			else ink.setDir(Direction::ZERO);
			break;
	}

	if (ink.getCharStepped() != CLYDE || ink.getCharStepped() != JUGADOR || ink.getCharStepped() != BLINKY || ink.getCharStepped() != INKY )
		map[ink.getPosition().y][ink.getPosition().x] = ink.getCharStepped(); // Abans de que el Binky es mogui, actualitzem la posicio amb el que hi havia anteriorment.;

	ink.setCharStepped(nextCharPosition(ink.getDir(), ink.getPosition())); // Guardarem el que trepitjara, a menys que sigui un altre persona;

	map[newPos.y][newPos.x] = INKY; //  Actualitzem la nova posicio amb la cara del jugador.
	ink.setPosition(newPos); //Actualitzem la nova posició;

}

/**************************************************************
* Actualizem tots els moviments dels enemics en els vectors.  *
***************************************************************/
void Map::moveAI(Player player)
{
	for (int i = 0; i < eBlinky.size(); i++)
	{
		if (!eBlinky[i].isDead())
		{
			moveBlinky(eBlinky[i]);
		}
			
	}
		
	for (int i = 0; i < eClyde.size(); i++)
	{
		if (!eClyde[i].isDead())
		{
			moveClyde(eClyde[i], player);
		}
			
	}
		
	for (int i = 0; i < eInky.size(); i++)
	{
		if (!eInky[i].isDead())
		{
			moveInky(eInky[i], player);
		}
			
	}
		

}

/*********************************************************
* Torna al jugador i els enemics a la posició inicial.	 *
**********************************************************/
void Map::resetPosition(Player &player)
{
	for (int i = 0; i < eBlinky.size(); i++)
	{
		eBlinky[i].setCharStepped(map[eBlinky[i].getInitPos().y][eBlinky[i].getInitPos().x]);
		map[eBlinky[i].getPosition().y][eBlinky[i].getPosition().x] = NOTHING;
		eBlinky[i].returnInitPos();
		map[eBlinky[i].getPosition().y][eBlinky[i].getPosition().x] = BLINKY;
		setFirstDirBlinky(eBlinky[i]);
	}
	for (int i = 0; i < eClyde.size(); i++)
	{
		eClyde[i].setCharStepped(map[eClyde[i].getInitPos().y][eClyde[i].getInitPos().x]);
		map[eClyde[i].getPosition().y][eClyde[i].getPosition().x] = NOTHING;
		eClyde[i].returnInitPos();
		map[eClyde[i].getPosition().y][eClyde[i].getPosition().x] = CLYDE;
	}

	for (int i = 0; i < eInky.size(); i++)
	{
		eInky[i].setCharStepped(map[eInky[i].getInitPos().y][eInky[i].getInitPos().x]);
		map[eInky[i].getPosition().y][eInky[i].getPosition().x] = NOTHING;
		eInky[i].returnInitPos();
		map[eInky[i].getPosition().y][eInky[i].getPosition().x] = INKY;
	}
	
	player.setCharStepped(' ');
	map[player.getPos().y][player.getPos().x] = NOTHING;
	player.returnInitPos();
	map[player.getPos().y][player.getPos().x] = JUGADOR;
	player.setHasPowerUp(false);
}

/********************************************
* Print dels elements del mapa per consola. *
*********************************************/
void Map::printMap(Player player)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Lletres de color blanc, per el titol.
	std::cout << "AA2: Desiree Moreno i Oriol Comas" << std::endl << std::endl << "    ";
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
					if (player.getHasPowerUp())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 * 16); // la cara del player groga amb boca negra.
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14*16); // la cara del player groga amb boca negra.
					break;
				case BLINKY:
					if (player.getHasPowerUp()) // Enemic comestible
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 * 10); //  voltant verd, simbol gris..
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 * 16); // voltant vermell, simbol negra.
					break;
				case INKY:
					if (player.getHasPowerUp()) // Enemic comestible
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 * 10); // voltant morat, simbol verd..
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 * 16); // voltant blau, simbol negra.
					break;
				case CLYDE:
					if (player.getHasPowerUp()) // Enemic comestible
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 * 10); // voltant gris, simbol verd. 
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13 * 16); // voltant rosa, simbol negra.
					break;
				case POWER_UP:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 * 16); // voltant verd, simbol negra..
					break;
			}
			std::cout << map[i][j];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); // La resta color dark.
		}
		std::cout << std::endl << "    ";
	}
	std::cout << std::endl;
}


/********************************************
* Reinici del mapa. *
*********************************************/
void Map::resetMap()
{
	std::ifstream llegirConfig;
	llegirConfig.open("config.txt"); //obrim el fitcher ".txt"
	char puntComa;
									 //Guardem la informacio de les files i columnes.
	llegirConfig >> filas;
	llegirConfig >> puntComa;
	llegirConfig >> columnas;
	llegirConfig >> puntComa;


	for (int i = 0; i < filas + 2; i++)
	{
		llegirConfig.getline(map[i], columnas + 1); //leemos linia a linia, el config.
	}
	llegirConfig.close(); //tanquem el fitxer.

}