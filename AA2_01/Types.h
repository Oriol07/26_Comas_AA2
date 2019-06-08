#pragma once

// Enum que conté tots els estats del joc.
enum class GameState {SPLASH_SCREEN, MAIN_MENU, GAME, PAUSE, RANKING, EXIT};

//Enum de control d'inputs.
enum class InputKey {K_ESC, K_P, K_UP, K_DOWN, K_LEFT, K_RIGHT, K_SPACE, K_0, K_1, K_2, COUNT};

// Enum que ens servira per determinar la direcció a la que anira el jugador.
enum class Direction {UP,DOWN,LEFT,RIGHT,ZERO};

// Struct que ens servira per les cordenadas x i y.
struct vec2 
{
	int x;
	int y;
};


