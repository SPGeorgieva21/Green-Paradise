#include <iostream>
#include <iomanip>
#include <conio.h>
#include "raylib.h"

int resolutionSettings()
{
	int resSize = 0;

	std::cout <<"Before starting the game, please SELECT RESOLUTION SCALE: " << std::endl << "OPTIONS: 1 => 1280x720; 2 = > 1980x1080" << std::endl;

	while ((resSize != 49) && (resSize != 50))
	{
		resSize = _getch();
		if (resSize == 49)
		{
			system("cls");
			return 1;
		}
		else if (resSize == 50)
		{
			system("cls");
			return 2;
		}
	}
}

void gameRes1280x720()
{
	InitWindow(1280, 720, "Algo-Rhythm_Testing");
	SetWindowState(FLAG_VSYNC_HINT);	//SetTargetFPS(60);

	Texture2D background = LoadTexture("../../sprites/bg1280-720.png");
	/*Texture2D earthWaterMap = LoadTexture("");
	Texture2D earthGroundMap = LoadTexture("");*/

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		
		DrawTexture(background, 0, 0, WHITE);


		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	UnloadTexture(background);
	CloseWindow();
}

void gameRes1980x1080()
{

}

int main()
{
	switch (resolutionSettings())
	{
		case 1: gameRes1280x720(); break;
		case 2: gameRes1980x1080(); break;
		default: std::cout << "Error => INCORRECT INPUT." << std::endl << "Closing game...";
	}
}