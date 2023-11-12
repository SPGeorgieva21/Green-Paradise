#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <conio.h>
#include <raylib.h>
#include "functions.h"

// Check if X and Y of mouse are inside X and Y of texture/images[N]
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

// Mini game Beach Cleaner
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

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(textures[i]);
    }

	//CloseWindow();
}

// Mini game Chance Taker resources
const int rows = 3;
const int cols = 4;
const int cellSize = 100;
const int fruitSpacing = 42;

// Load images
const char* fruitImages[] = 
{
    "..\\..\\sprites\\miniGames\\chanceTaker\\watermelon.png",
    "..\\..\\sprites\\miniGames\\chanceTaker\\pers.png",
    "..\\..\\sprites\\miniGames\\chanceTaker\\banan.png",
    "..\\..\\sprites\\miniGames\\chanceTaker\\\straw.png"
};

// Game description
const char* fruitDescriptions[] = 
{
    "Watermelon - 25 levs",
    "Peach - 50 levs",
    "Banana - 75 levs",
    "Strawberry - 100 levs"
};

int grid[rows][cols];
int totalWinnings = 0;
int roundWinnings = 0;
bool spinButtonPressed = false;
bool spinning = false;
bool roundEnded = true;

void InitializeGrid() 
{
    spinning = true;
    roundWinnings = 0;
    roundEnded = false;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j) 
        {
            grid[i][j] = GetRandomValue(0, 3);
        }
    }
}

// Check if 4 fruits are the same on one row
void CheckForWin() {
    int winnings = 0;

    for (int i = 0; i < rows; ++i) 
    {
        int count[4] = { 0 };

        for (int j = 0; j < cols; ++j) 
        {
            count[grid[i][j]]++;
        }

        for (int k = 0; k < 4; ++k) 
        {
            if (count[k] == 4) 
            {
                switch (k) 
                {
                case 0:
                    winnings += 25;
                    break;
                case 1:
                    winnings += 50;
                    break;
                case 2:
                    winnings += 75;
                    break;
                case 3:
                    winnings += 100;
                    break;
                }
            }
        }
    }

    if (winnings > 0 && !roundEnded) 
    {
        totalWinnings += winnings;
        roundWinnings = winnings;
        roundEnded = true;
    }
}

// Check if X and Y of mouse are inside X and Y of button
bool IsMouseOverButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight) 
{
    Vector2 mousePosition = GetMousePosition();
    return (mousePosition.x >= buttonX && mousePosition.x <= buttonX + buttonWidth &&
        mousePosition.y >= buttonY && mousePosition.y <= buttonY + buttonHeight);
}

// Mini game Chance Taker
void chanceTaker() 
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Moment Game");
    SetTargetFPS(60);

    InitializeGrid();

    Texture2D fruitTextures[4];

    for (int i = 0; i < 4; ++i) {
        fruitTextures[i] = LoadTexture(fruitImages[i]);
    }

    while (!WindowShouldClose()) {
        if (!spinning && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOverButton(screenWidth - 100, 0, 100, screenHeight)) {
            InitializeGrid();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Chance Taker", screenWidth / 2 - MeasureText("Chance Taker", 30) / 2, 10, 30, WHITE);

        for (int i = 0; i < 4; ++i) {
            DrawText(fruitDescriptions[i], 10, 50 + i * 35, 25, RAYWHITE);
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int x = (screenWidth - cols * (cellSize + fruitSpacing)) / 2 + j * (cellSize + fruitSpacing);
                int y = (screenHeight - rows * (cellSize + fruitSpacing)) / 2 + i * (cellSize + fruitSpacing);
                DrawTexture(fruitTextures[grid[i][j]], x, y, RAYWHITE);
            }
        }

        CheckForWin();

        DrawRectangle(screenWidth - 100, 0, 100, screenHeight, GRAY);
        DrawText("SPIN", screenWidth - 80, 50, 20, RAYWHITE);

        DrawText(("Total Winnings: " + std::to_string(totalWinnings) + " levs").c_str(), 10, GetScreenHeight() - 65, 30, RAYWHITE);

        EndDrawing();

        if (spinning) {
            spinning = false;
            roundEnded = true;
        }
    }

    for (int i = 0; i < 4; ++i) {
        UnloadTexture(fruitTextures[i]);
    }

    //CloseWindow();
}