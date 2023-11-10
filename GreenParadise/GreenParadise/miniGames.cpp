#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <conio.h>
#include <raylib.h>
#include "functions.h"

void checkIfInBounds(int x, int y, Texture2D images[], int* imageX, int* imageY)
{
	for (int i = 0; i < 6; i++)
	{
		if ((x >= imageX[i] && x <= imageX[i] + images[i].width) && (y >= imageY[i] && y <= imageY[i] + images[i].width))
		{
			std::random_device rd;
			std::uniform_int_distribution <int> range(20, 750);
			imageX[i] = range(rd);
		}
	}
}

void beachCleaner()
{
	Texture2D beachBackground = LoadTexture("../../sprites/miniGames/beachCleaner/background.png");
	Texture2D plasticBag = LoadTexture("../../sprites/miniGames/beachCleaner/plasticBag.png");
	Texture2D plasticBottle = LoadTexture("../../sprites/miniGames/beachCleaner/plasticBottle.png");
	Texture2D metalCan = LoadTexture("../../sprites/miniGames/beachCleaner/metalCan.png");
	Texture2D sodaCan = LoadTexture("../../sprites/miniGames/beachCleaner/sodaCan.png");
	Texture2D garbage = LoadTexture("../../sprites/miniGames/beachCleaner/garbage.png");
	Texture2D flipFlop = LoadTexture("../../sprites/miniGames/beachCleaner/flipFlop.png");

	int imageX[] = { 740, 290, 960, 100, 540, 400 };
	int imageY[] = { 450, 480, 500, 580, 600, 630 };
	Texture2D textures[6] = { plasticBag, plasticBottle, metalCan, sodaCan, garbage, flipFlop };

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			checkIfInBounds(GetMouseX(), GetMouseY(), textures, imageX, imageY);
		}

		DrawTexture(beachBackground, 0, 0, WHITE);
		DrawTexture(plasticBag, imageX[0], imageY[0], WHITE);
		DrawTexture(plasticBottle, imageX[1], imageY[1], WHITE);
		DrawTexture(metalCan, imageX[2], imageY[2], WHITE);
		DrawTexture(sodaCan, imageX[3], imageY[3], WHITE);
		DrawTexture(garbage, imageX[4], imageY[4], WHITE);
		DrawTexture(flipFlop, imageX[5], imageY[5], WHITE);

		EndDrawing();
	}

	UnloadTexture(beachBackground);
	UnloadTexture(plasticBag);
	UnloadTexture(plasticBottle);
	UnloadTexture(metalCan);
	UnloadTexture(sodaCan);
	UnloadTexture(garbage);
	UnloadTexture(flipFlop);
	CloseWindow();
}

int startupStatus()
{
	return 0;
}