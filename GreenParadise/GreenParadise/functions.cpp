#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <conio.h>
#include "raylib.h"
#include "functions.h"

int resolutionSettings()
{
	system("color 0a");

	int resSize = 0;

	std::cout << "Before starting the game, please SELECT RESOLUTION SCALE: " << std::endl << "OPTIONS: 1 => 1280x720; 2 = > 1980x1080" << std::endl;

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
	system("color f0");

	InitWindow(1280, 720, "Green Paradise");
	SetTargetFPS(60); 	//SetWindowState(FLAG_VSYNC_HINT);

	Texture2D background = LoadTexture("../../sprites/bg1280-720.png");
	Texture2D earth = LoadTexture("../../sprites/worldRotation.png");
	//Texture2D fallingStarEvent = LoadTexture("../../sprites/worldRotation.png");

	float wordlFrameWidth = (float)(earth.width / 23);
	int maxFrames = (int)(earth.width / (int)wordlFrameWidth);

	float timer = 0.0f;
	int frame = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		timer += GetFrameTime();
		if (timer >= 0.2f)
		{
			timer = 0.0f;
			frame += 1;
		}

		frame = frame % maxFrames;

		/*std::random_device rd;
		std::uniform_int_distribution <int> range(1, 3);

		if (1 == range(rd))
		{

		}*/

		DrawTexture(background, 0, 0, WHITE);
		DrawTextureRec(earth, Rectangle{ (wordlFrameWidth * frame), 0, wordlFrameWidth, (float)earth.height }, Vector2{ (float)((GetScreenWidth() / 4) - 90), (float)50 }, RAYWHITE);

		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	UnloadTexture(background);
	UnloadTexture(earth);
	//UnloadTexture(fallingStarEvent);
	CloseWindow();
}

void gameRes1980x1080()
{
	system("color f0");

	std::string NSUD = "NOT SUPPORTED <=> under development";
	size_t sizeOfErr = NSUD.length();
	std::cout << '\n' << std::setw(43 + sizeOfErr) << NSUD << '\n';
}