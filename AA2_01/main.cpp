/***************************************************
* Grup 26.								           *
* - Desirèe Moreno						           *
* - Oriol Comas Llurià                             *
* Github: https://github.com/Oriol07/Grup26_AA2_1  *
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
	bool GameOver = false;
	int time = 0;
	
	GameState myGameState = GameState::GAME;
	//MAIN LOOP del joc.
	do
	{
		//INPUT HANDLLER
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
				std::cout << " ********* SPLASHSCREEN ********* " << std::endl;
				Sleep(200);
				std::cout << " Welcome to PACMAN";
				Sleep(200);
				std::cout << "."; Sleep(200); std::cout << "."; Sleep(200); std::cout << "."; Sleep(200);
				time++;

				if (time == 3)
				{
					myGameState = GameState::MAIN_MENU;
				}
				system("cls");

			break; // Fi del case SplashScreen 

			case GameState::MAIN_MENU:

			break;

			case GameState::PAUSE:
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
				{
					myGameState = GameState::MAIN_MENU;
				}

				std::cout << " Pause//EN PAUSA.\n PREM 'P' per jugar" << std::endl;
				if (keyboard[(int)InputKey::K_SPACE])
				{
					myGameState = GameState::GAME;
					Sleep(1000);
				}
				system("cls");
				
			break; // Fi case Pausa

			case GameState::GAME:
				//Detecta el event del teclat, i determina quina sera la seguent posicio del jugador 
				if (KEYPRESSED)
				{

					if (keyboard[(int)InputKey::K_UP])
					{
						player.SetDir(Direction::UP); //ARRIBA
						player.SetCanMove(true);
					}
					if (keyboard[(int)InputKey::K_DOWN])
					{
						player.SetDir(Direction::DOWN);	//ABAJO
						player.SetCanMove(true);
					}
					if (keyboard[(int)InputKey::K_RIGHT])
					{
						player.SetDir(Direction::RIGHT);	//IZQUIERDA
						player.SetCanMove(true);
					}
					if (keyboard[(int)InputKey::K_LEFT])
					{
						player.SetDir(Direction::LEFT);	//DERECHA
						player.SetCanMove(true);
					}


				}
				else player.SetDir(Direction::ZERO);					
				
				if (keyboard[(int)InputKey::K_ESC]) //"ESCAPE" // terminar el juego.
					{
						myGameState = GameState::MAIN_MENU;
					}

				if (keyboard[(int)InputKey::K_P])
				{
					myGameState = GameState::PAUSE;
					Sleep(500);
					system("cls");
				}

				if (player.CanMove()) // true cuando se detecta event del teclat
				{
					if (map.NoExistMur(player.GetPos(), player.GetDir())) //Si no existeix mur a la proxima posicio.
					{
						if (map.ExistPunt(player.GetPos(), player.GetDir())) // si es punto se suma uno.
							player.SetScore(player.GetScore() + 1);
						map.MovePlayer(player); // mou al player a la prox posicio
					}
					player.SetCanMove(false);
				}
				
				map.MoveAI(player); // Es mouen els enemics.
				if (map.PlayerTouchEnemy(player))
				{
					player.SetLifes(player.GetLifes() - 1);
					
					if (player.GetLifes() == 0)
						myGameState = GameState::MAIN_MENU;
				}
				system("cls"); // limpiamos pantalla
				std::cout << "********* PLAY *********" << std::endl;
				map.PrintMap(); //printamoss MAPA
				player.PrintPlayer(); //printtamos HUD/Score
				break; // Fi case game
		}


		Sleep(TIME); //Refresc del joc cada un segón.

	} while (myGameState != GameState::EXIT);

	system("cls"); // limpiamos pantalla
	std::cout << "Joc acabat" << std::endl;
	Sleep(2000); // Ending de 2 segons.

	return 0;
}
