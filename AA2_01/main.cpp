/***************************************************
* Grup 26.								      	   *
* - Oriol Comas Lluri�                             *
* Github: https://github.com/Oriol07/26_Comas_AA2  *
****************************************************/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <map>
#include <list>
#include <string>

#include "Constants.h"
#include "Types.h"
#include "Player.h"
#include "Blinky.h"
#include "Map.h"
#include "Ranking.h"



int main()
{
	//Variables
	Player player;
	Map map = Map(player);
	bool keyboard[(int)InputKey::COUNT] = {};
	bool gameOver = false;
	bool mainMenuFirst = true;
	int time = 0;
	float timeMili = 0;
	int counterRanking;
	bool chargingRanking;
	bool toEnterRanking = false;
	std::map<std::string, unsigned int> rankingGeneral; // ranking general.
	std::list<ranking> rankingTop; // ranking dels top 5
	ranking gRank; 
	
	GameState myGameState = GameState::SPLASH_SCREEN;
	
	///MAIN LOOP del joc.
	do
	{
		///Detecci� de inputs.
		keyboard[(int)InputKey::K_ESC] = GetAsyncKeyState(VK_ESCAPE);
		keyboard[(int)InputKey::K_P] = GetAsyncKeyState(0x50);
		keyboard[(int)InputKey::K_UP] = GetAsyncKeyState(VK_UP);
		keyboard[(int)InputKey::K_DOWN] = GetAsyncKeyState(VK_DOWN);
		keyboard[(int)InputKey::K_LEFT] = GetAsyncKeyState(VK_LEFT);
		keyboard[(int)InputKey::K_RIGHT] = GetAsyncKeyState(VK_RIGHT);
		keyboard[(int)InputKey::K_SPACE] = GetAsyncKeyState(VK_SPACE);
		keyboard[(int)InputKey::K_0] = GetAsyncKeyState(0x30);
		keyboard[(int)InputKey::K_1] = GetAsyncKeyState(0x31);
		keyboard[(int)InputKey::K_2] = GetAsyncKeyState(0x32);


		switch (myGameState)
		{
			case GameState::SPLASH_SCREEN:
				/// DRAW
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << " ********* SPLASHSCREEN ********* " << std::endl;
				Sleep(200);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				std::cout << " Welcome to PACMAN" << std::flush;
				Sleep(200);
				std::cout << "." << std::flush; Sleep(200); std::cout << "." << std::flush; Sleep(200); std::cout << "." << std::flush; Sleep(200);

				/// UPDATE
				time++;

				if (time == 3) // Als 3 segons passarem al main menu
				{
					myGameState = GameState::MAIN_MENU;
					mainMenuFirst = true;
				}
				system("cls");

			break; // Fi del case SplashScreen 

			case GameState::MAIN_MENU:
				/// EVENTS DE TECLAT
				if (keyboard[(int)InputKey::K_1]) 
				{
					myGameState = GameState::GAME;
					player.setLifes(3);
					player.setScore(0);
					system("cls");
				}
				if (keyboard[(int)InputKey::K_2])
				{
					myGameState = GameState::RANKING;
					chargingRanking = true;
					system("cls");
				}

				if (keyboard[(int)InputKey::K_ESC] || keyboard[(int)InputKey::K_0]) //"ESCAPE" // terminar el juego.
				{
					myGameState = GameState::EXIT;
				}
				/// DRAW
				if (mainMenuFirst)
				{
					mainMenuFirst = false;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					std::cout << " ********* MAIN MENU ********* " << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					std::cout << " 1 - PLAY. " << std::endl << " 2 - RANKING. " << std::endl << " 0 - EXIT GAME." << std::endl;
				}
			break; // break de case Main Menu

			case GameState::PAUSE:

				/// Events de teclat
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
				{
					mainMenuFirst = true;
					myGameState = GameState::MAIN_MENU;
					map.resetPosition(player);
					map.resetMap();
					Sleep(1000);
					
				}

				if (keyboard[(int)InputKey::K_SPACE])
				{
					myGameState = GameState::GAME;
					Sleep(1000);
					system("cls");
				}
				/// DRAW 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << " ******* PAUSE ******** \n Press SPACE to continue" << std::endl;
				system("cls");

				
			break; // Fi case Pausa
			
			//Cas ranking
			case GameState::RANKING:

				/// Key Events
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
				{
					mainMenuFirst = true;
					myGameState = GameState::MAIN_MENU;
					map.resetPosition(player);
					map.resetMap();
					Sleep(2500);
					system("cls");
				}
				//Preguntem
				if (toEnterRanking)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					std::cout << "What's your name?" << std::endl;
					std::cin >> player.name;
					writeRanking(player.name, player.getScore());
					toEnterRanking = false;
				}

				//  Mirem si el ranking s'ha llegit ja i ordenat.
				if (chargingRanking)
				{

					/// Update
					readRanking(rankingGeneral); //llegim
					swapRanking(rankingGeneral, rankingTop); // Passem el map a un list.
					rankingTop.sort(compareBig);
					chargingRanking = false;
					
					/// DRAW
					counterRanking = 0;
					for (std::list<ranking>::iterator it = rankingTop.begin(); it != rankingTop.end(); ++it)
					{
						counterRanking++;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), counterRanking + 1);
						std::cout << counterRanking << ". " << it->name << " " << it->score << std::endl;
						if (counterRanking == 5)
						{
							it = rankingTop.end();
							it--;
						}
					}
				}

			break; //Fi case rankin
				

			case GameState::GAME:
				/// Events de Teclat
				if (KEYPRESSED)
				{

					if (keyboard[(int)InputKey::K_UP])
					{
						player.setDir(Direction::UP); //ARRIBA
						player.setCanMove(true);
					}
					if (keyboard[(int)InputKey::K_DOWN])
					{
						player.setDir(Direction::DOWN);	//ABAJO
						player.setCanMove(true);
					}
					if (keyboard[(int)InputKey::K_RIGHT])
					{
						player.setDir(Direction::RIGHT);	//IZQUIERDA
						player.setCanMove(true);
					}
					if (keyboard[(int)InputKey::K_LEFT])
					{
						player.setDir(Direction::LEFT);	//DERECHA
						player.setCanMove(true);
					}


				}
				else player.setDir(Direction::ZERO); // En cas de que cap input de moviment sigui true posem la direcci� quieta.					
				
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
					{
						mainMenuFirst = true;
						myGameState = GameState::MAIN_MENU;
						map.resetPosition(player);
						map.resetMap();
						system("cls");
					}

				if (keyboard[(int)InputKey::K_P])
				{
					myGameState = GameState::PAUSE;
					Sleep(500);
					system("cls");
				}

				/// UPDATE
				map.moveAI(player); // Es mouen els enemics.

				//Quan el jugador no t� powerUp
				if (!player.getHasPowerUp())
				{

					if (map.playertouchEnemy(player))
					{
						map.resetPosition(player);
						player.setLifes(player.getLifes() - 1);
						std::cout << player.getCharStepped() << std::endl;
						Sleep(1000);

						if (player.getLifes() == 0)
						{
							myGameState = GameState::RANKING;
							toEnterRanking = true;
							chargingRanking = true;
							gameOver = true;
							map.resetMap();

						}
					}
					if (player.canMove()) // true cuando se detecta event del teclat
					{
						if (map.noExistMur(player.getPos(), player.getDir())) //Si no existeix mur a la proxima posicio.
						{
							if (map.existPunt(player.getPos(), player.getDir())) // si es punto se suma uno.
								player.setScore(player.getScore() + 1);
							map.movePlayer(player); // mou al player a la prox posicio
						}
						player.setCanMove(false);
					}
					if (map.playertouchEnemy(player))
					{
						map.resetPosition(player);
						player.setLifes(player.getLifes() - 1);
						std::cout << player.getCharStepped() << std::endl;
						Sleep(1000);

						if (player.getLifes() == 0)
						{
							myGameState = GameState::RANKING;
							toEnterRanking = true;
							chargingRanking = true;
							gameOver = true;
							map.resetMap();

						}
					}
	

					if (player.touchPowerUp())
					{
						player.setCharStepped(' ');
						time = 7;
						timeMili = 0;
						player.setHasPowerUp(true);
					}

				}
				else //Quan a agafat un PowerUp
				{
					timeMili++;
					if (timeMili == 2)
					{
						time--;
						timeMili = 0;
					}
					if (time < 0) player.setHasPowerUp(false);

					if (map.playertouchEnemy(player))
					{
						map.moveInitPosAI(player);
					}

					if (player.canMove()) // true cuando se detecta event del teclat
					{
						if (map.noExistMur(player.getPos(), player.getDir())) //Si no existeix mur a la proxima posicio.
						{
							if (map.existPunt(player.getPos(), player.getDir())) // si es punto se suma uno.
								player.setScore(player.getScore() + 1);
							map.movePlayer(player); // mou al player a la prox posicio
						}
						player.setCanMove(false);
					}

					if (map.playertouchEnemy(player))
					{
						map.moveInitPosAI(player);
					}
					if (player.touchPowerUp())
					{
						time = 7;
						player.setHasPowerUp(true);
					}
				}
				

				/// DRAW
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << "********* PLAY *********" << std::endl;
				map.printMap(player); //printamoss MAPA
				player.printPlayer(time); //printtamos HUD/Score

				/// FRAME CONTROL
				Sleep(TIME); //Refresc del joc cada un seg�n.
				system("cls"); // limpiamos pantalla

			break; // Fi case game
		}



	} while (myGameState != GameState::EXIT);

	system("cls"); // limpiamos pantalla
	if (gameOver)
		std::cout << "******* GAME OVER ********" << std::endl;
	std::cout << "Joc acabat" << std::endl;
	Sleep(2000); // Ending de 2 segons.

	return 0;
}
