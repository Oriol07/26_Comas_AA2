/***************************************************
* Grup 26.								      	   *
* - Oriol Comas Llurià                             *
* Github: https://github.com/Oriol07/26_Comas_AA2  *
****************************************************/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <vector>

#include "Constants.h"
#include "Types.h"
#include "Player.h"
#include "Blinky.h"
#include "Map.h"



int main()
{
	//Variables
	Player player;
	Map map = Map(player);
	bool keyboard[(int)InputKey::COUNT] = {};
	bool gameOver = false;
	bool mainMenuFirst = true;
	int time = 0;
	int timeMili = 0;
	
	GameState myGameState = GameState::SPLASH_SCREEN;

	///MAIN LOOP del joc.
	do
	{
		///Detecció de inputs.
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
				///DRAW
				std::cout << " ********* SPLASHSCREEN ********* " << std::endl;
				Sleep(200);
				std::cout << " Welcome to PACMAN";
				Sleep(200);
				std::cout << "."; Sleep(200); std::cout << "."; Sleep(200); std::cout << "."; Sleep(200);

				///UPDATE
				time++;

				if (time == 3) // Als 3 segons passarem al main menu
				{
					myGameState = GameState::MAIN_MENU;
					mainMenuFirst = true;
				}
				system("cls");

			break; // Fi del case SplashScreen 

			case GameState::MAIN_MENU:
				///EVENTS DE TECLAT
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
				}

				if (keyboard[(int)InputKey::K_ESC] || keyboard[(int)InputKey::K_0]) //"ESCAPE" // terminar el juego.
				{
					myGameState = GameState::EXIT;
				}
				/// DRAW
				if (mainMenuFirst)
				{
					mainMenuFirst = false;
					std::cout << " ********* MAIN MENU ********* " << std::endl;
					std::cout << " 1 - PLAY. " << std::endl << " 2 - RANKING. " << std::endl << " 0 - EXIT GAME." << std::endl;
				}
			break; // break de case Main Menu

			case GameState::PAUSE:

				///Events de teclat
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
				{
					mainMenuFirst = true;
					myGameState = GameState::MAIN_MENU;
					map.resetPosition(player);
					map.resetMap();
					
				}

				if (keyboard[(int)InputKey::K_SPACE])
				{
					myGameState = GameState::GAME;
					Sleep(1000);
					system("cls");
				}
				///DRAW 
				std::cout << " ******* PAUSE ******** \n Press SPACE to continue" << std::endl;
				system("cls");
				
			break; // Fi case Pausa

			case GameState::GAME:
				///Events de Teclat
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
				else player.setDir(Direction::ZERO); // En cas de que cap input de moviment sigui true posem la direcció quieta.					
				
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

				///UPDATE
				map.moveAI(player); // Es mouen els enemics.

				//Quan el jugador no té powerUp
				if (!player.getHasPowerUp())
				{

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
							myGameState = GameState::EXIT;
							gameOver = true;
							map.resetMap();

						}
					}
					if (player.touchPowerUp())
					{
						player.setHasPowerUp(true);
					}

				}
				else //Quan a agafat un PowerUp
				{
					if (player.canMove()) // true cuando se detecta event del teclat
					{
						if (map.noExistMur(player.getPos(), player.getDir())) //Si no existeix mur a la proxima posicio.
						{
							if (map.existPunt(player.getPos(), player.getDir())) // si es punto se suma uno.
								player.setScore(player.getScore() + 2);
							map.movePlayer(player); // mou al player a la prox posicio
						}
						player.setCanMove(false);
					}

					if (map.playertouchEnemy(player))
					{


					}
					if (player.touchPowerUp())
					{
						player.setHasPowerUp(true);
					}
				}

				/// DRAW
				std::cout << "********* PLAY *********" << std::endl;
				map.printMap(player); //printamoss MAPA
				player.printPlayer(); //printtamos HUD/Score

				/// FRAME CONTROL
				Sleep(TIME); //Refresc del joc cada un segón.
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
