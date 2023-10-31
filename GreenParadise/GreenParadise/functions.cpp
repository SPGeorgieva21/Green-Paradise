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
	Texture2D fallingStarEventL = LoadTexture("../../sprites/fallingStarL.png");
	Texture2D fallingStarEventR = LoadTexture("../../sprites/fallingStarR.png");

	float wordlFrameWidth = (float)(earth.width / 23);
	int maxFramesE = (int)(earth.width / (int)wordlFrameWidth);

	float fallingStarFrameWidth = (float)(fallingStarEventL.width / 30);
	int maxFramesFS = (int)(fallingStarEventL.width / (int)fallingStarFrameWidth);

	float timerE = 0.0f;
	int frameE = 0;

	float timerFS = 0.0f;
	int frameFS = 0;
	int countDrawTime = 0;

	float starFallingXdec = 0, starFallingYdec = 1, baseXFS = 550, baseYFS = -270;
	bool checkIfOffScreen = false;
	int fixFS = 0, countFixFS = 0;

	// random direction of falling star
	std::random_device rd2;
	std::uniform_int_distribution <int> range2(0, 1);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		timerE += GetFrameTime();
		if (timerE >= 0.2f)
		{
			timerE = 0.0f;
			frameE += 1;
		}

		frameE = frameE % maxFramesE;

		DrawTexture(background, 0, 0, WHITE);

		
		if (!checkIfOffScreen)
		{
			countFixFS++;
			if (countFixFS == 1)
			{
				fixFS = range2(rd2);
			}
			while (countDrawTime < 10)
			{
				countDrawTime++;

				// timer for animation of falling star
				timerFS += GetFrameTime();
				if (timerFS >= 0.2f)
				{
					timerFS = 0.0f;
					frameFS += 1;
				}

				frameFS = frameFS % maxFramesFS;

				if (fixFS == true)
				{
					DrawTextureRec(fallingStarEventL, Rectangle{ (fallingStarFrameWidth * frameFS), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
					starFallingXdec += 0.1;
					starFallingYdec += 0.1;
				}
				else
				{
					DrawTextureRec(fallingStarEventR, Rectangle{ (fallingStarFrameWidth * frameFS), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
					starFallingXdec -= 0.1;
					starFallingYdec += 0.1;
				}
			}

			countDrawTime = 0;
		}
		else
		{
			// random direction of falling star
			std::random_device rd2;
			std::uniform_int_distribution <int> range2(1, 2);
			fixFS = range2(rd2);

			// random X coordinates for the falling star
			std::random_device rd;
			std::uniform_int_distribution <int> range(250, 800);
			baseXFS = range(rd);
			baseYFS = -270;
			starFallingXdec = 0;
			starFallingYdec = 1;
			checkIfOffScreen = false;
		}
		
		if (starFallingYdec > (270 * 3))
		{
			checkIfOffScreen = true;
		}

		DrawTextureRec(earth, Rectangle{ (wordlFrameWidth * frameE), 0, wordlFrameWidth, (float)earth.height }, Vector2{ (float)((GetScreenWidth() / 4) - 90), (float)50 }, RAYWHITE);

		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	UnloadTexture(background);
	UnloadTexture(earth);
	UnloadTexture(fallingStarEventL);
	UnloadTexture(fallingStarEventR);
	CloseWindow();
}

void gameRes1980x1080()
{
	system("color f0");

	std::string NSUD = "NOT SUPPORTED <=> under development";
	size_t sizeOfErr = NSUD.length();
	std::cout << '\n' << std::setw(43 + sizeOfErr) << NSUD << '\n';
}