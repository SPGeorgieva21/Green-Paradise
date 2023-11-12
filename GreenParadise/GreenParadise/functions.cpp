#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <conio.h>
#include <raylib.h>
#include "functions.h"

int temporary = 0;

// Checks the resolution selected by the User
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

// Checks the status of the game selected by the User
int startupStatus(int x, int y, Texture2D startButton, Texture2D exitButton)
{
	if ((x >= (GetScreenWidth() / 2) - 150 && x <= (GetScreenWidth() / 2) - 150 + startButton.width) && (y >= 200 + startButton.height && y <= (200 + startButton.height) + startButton.height))
	{
		return 1;
	}
	else if ((x >= (GetScreenWidth() / 2) - 120 && x <= ((GetScreenWidth() / 2) - 120) + exitButton.width) && (y >= 310 + exitButton.height && y <= (310 + exitButton.height) + exitButton.height))
	{
		return 2;
	}
}

// Starts the game with resolution of 1280x720
void gameMenu1280x720()
{
	system("color f0");

	InitWindow(1280, 720, "Green Paradise");
	SetTargetFPS(60); 	// Alternative method (VSYNC) - SetWindowState(FLAG_VSYNC_HINT);

	std::vector<Texture2D> earthImgs;

	// Declaring and initializing textures
	for (size_t i = 1; i <= 23; i++)
		earthImgs.push_back(LoadTexture(TextFormat("../../sprites/worldRotationPNGs-23/%drot.png", i)));

	Texture2D mouse = LoadTexture("../../sprites/mouseSprites/mouseSprite1.png");
	Texture2D startButton = LoadTexture("../../sprites/buttons/startButton.png");
	Texture2D exitButton = LoadTexture("../../sprites/buttons/exitButton.png");
	Texture2D gameName = LoadTexture("../../sprites/buttons/gameName.png");
	Texture2D backgroundMenu = LoadTexture("../../sprites/background/bg1280-720.png");
	Texture2D earth = LoadTexture("../../sprites/worldRotation.png");
	Texture2D border = LoadTexture("../../sprites/borders/menuBorder.png");
	Texture2D fallingStarEventL = LoadTexture("../../sprites/fallingStarL.png");
	Texture2D fallingStarEventR = LoadTexture("../../sprites/fallingStarR.png");

	// Set timers
	float wordlFrameWidth = (float)(earth.width / 23);
	int maxFramesEearth = (int)(earth.width / (int)wordlFrameWidth);

	float fallingStarFrameWidth = (float)(fallingStarEventL.width / 30);
	int maxFramesFallingStar = (int)(fallingStarEventL.width / (int)fallingStarFrameWidth);

	float timerEarth = 0.0f;
	int frameEearth = 0;

	float timerFallingStar = 0.0f;
	int frameFallingStar = 0;
	int countDrawTime = 0;

	// Position shifters
	float starFallingXdec = 0, starFallingYdec = 1, baseXFS = 550, baseYFS = -270;
	bool checkIfOffScreen = false;
	int fixFallingStar = 0, countFixFallingStar = 0;
	float xMouseTrack = 0.0f, yMouseTrack = 0.0f;

	// Random direction of falling star
	std::random_device rd2;
	std::uniform_int_distribution <int> range2(0, 1);

	std::string startGame = "";

	HideCursor();

	// Starting game
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		int getXMouseTrack = GetMouseX(), getYMouseTrack = GetMouseY();
		xMouseTrack = getXMouseTrack;
		yMouseTrack = getYMouseTrack;

		timerEarth += GetFrameTime();
		if (timerEarth >= 0.2f)
		{
			timerEarth = 0.0f;
			frameEearth += 1;
		}

		frameEearth = frameEearth % maxFramesEearth;

		// Draw textures
		DrawTexture(backgroundMenu, 0, 0, WHITE);

		if (!checkIfOffScreen)
		{
			countFixFallingStar++;
			if (countFixFallingStar == 1)
			{
				fixFallingStar = range2(rd2);
			}
			while (countDrawTime < 10)	// determines the speed of the animation
			{
				countDrawTime++;

				// timer for animation of falling star
				timerFallingStar += GetFrameTime();
				if (timerFallingStar >= 0.2f)
				{
					timerFallingStar = 0.0f;
					frameFallingStar += 1;
				}

				frameFallingStar = frameFallingStar % maxFramesFallingStar;

				if (fixFallingStar == true)
				{
					DrawTextureRec(fallingStarEventL, Rectangle{ (fallingStarFrameWidth * frameFallingStar), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
					starFallingXdec += 0.1;
					starFallingYdec += 0.1;
				}
				else
				{
					DrawTextureRec(fallingStarEventR, Rectangle{ (fallingStarFrameWidth * frameFallingStar), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
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
			fixFallingStar = range2(rd2);

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

		DrawTexture(earthImgs[frameEearth], (float)((GetScreenWidth() / 4) - 90), (float)350, WHITE);

		DrawTexture(startButton,(GetScreenWidth() / 2) - 150, 200 + startButton.height, WHITE);
		DrawTexture(exitButton, (GetScreenWidth() / 2) - 120, 310 + exitButton.height, WHITE);
		DrawTexture(gameName, (GetScreenWidth() / 2) - 290, gameName.height - 28, WHITE);
		DrawTexture(border, 0, 0, WHITE);
		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			switch (startupStatus(GetMouseX(), GetMouseY(), startButton, exitButton))
			{
				case 1:	startGame = "start"; break;
				case 2: startGame = "close"; break;
			}
		}

		if (startGame == "start")
		{
			break;
		}
		else if (startGame == "close")
		{
			break;
		}

		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	//Unload textures
	for (auto it = earthImgs.begin(); it != earthImgs.end(); ++it)
		UnloadTexture(*it);

	UnloadTexture(mouse);
	UnloadTexture(startButton);
	UnloadTexture(exitButton);
	UnloadTexture(gameName);
	UnloadTexture(backgroundMenu);
	UnloadTexture(earth);
	UnloadTexture(border);
	UnloadTexture(fallingStarEventL);
	UnloadTexture(fallingStarEventR);

	if (startGame == "start")
	{
		gameRes1280x720();
	}
	else
	{
		CloseWindow();
	}
}

void gameRes1280x720()
{
	// Declaring and initializing textures
	std::vector<Texture2D> earthImgs;

	for (size_t i = 1; i <= 23; i++)
		earthImgs.push_back(LoadTexture(TextFormat("../../sprites/worldRotationPNGs-23/%drot.png", i)));
	
	Texture2D mouse = LoadTexture("../../sprites/mouseSprites/mouseSprite1.png");
	Texture2D background = LoadTexture("../../sprites/background/bg1280-720.png");
	Texture2D earth = LoadTexture("../../sprites/worldRotation.png");
	Texture2D fallingStarEventL = LoadTexture("../../sprites/fallingStarL.png");
	Texture2D fallingStarEventR = LoadTexture("../../sprites/fallingStarR.png");
	Texture2D bottomBarN = LoadTexture("../../sprites/borders/bottomBarN.png");
	Texture2D bottomBarG = LoadTexture("../../sprites/borders/bottomBarG.png");	// x >= 65%
	Texture2D bottomBarR = LoadTexture("../../sprites/borders/bottomBarR.png");	// x <= 45%
	Texture2D marketTab = LoadTexture("../../sprites/tabIcons/ecoMarketTab.png");
	Texture2D statisticsTab = LoadTexture("../../sprites/tabIcons/statisticsTab.png");
	Texture2D miniGamesTab = LoadTexture("../../sprites/tabIcons/ecoGamesTab.png");

	// Set timers
	float wordlFrameWidth = (float)(earth.width / 23);
	int maxFramesE = (int)(earth.width / (int)wordlFrameWidth);

	float fallingStarFrameWidth = (float)(fallingStarEventL.width / 30);
	int maxFramesFS = (int)(fallingStarEventL.width / (int)fallingStarFrameWidth);

	float timerEarth = 0.0f;
	int frameEearth = 0;
	
	float timerFallingStar = 0.0f;
	int frameFallingStar = 0;
	int countDrawTime = 0;

	// Position shifters
	float starFallingXdec = 0, starFallingYdec = 1, baseXFS = 550, baseYFS = -270;
	bool checkIfOffScreen = false;
	int fixFallingStar = 0, countFixFS = 0;
	float xMouseTrack = 0.0f, yMouseTrack = 0.0f;

	// random direction of falling star
	std::random_device rd2;
	std::uniform_int_distribution <int> range2(0, 1);

	HideCursor();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		int getXMouseTrack = GetMouseX(), getYMouseTrack = GetMouseY();
		xMouseTrack = getXMouseTrack;
		yMouseTrack = getYMouseTrack;

		timerEarth += GetFrameTime();
		if (timerEarth >= 0.2f)
		{
			timerEarth = 0.0f;
			frameEearth += 1;
		}

		frameEearth = frameEearth % maxFramesE;
		

		// Drawing textures
		DrawTexture(background, 0, 0, WHITE);
		
		if (!checkIfOffScreen)
		{
			countFixFS++;
			if (countFixFS == 1)
			{
				fixFallingStar = range2(rd2);
			}
			while (countDrawTime < 10)	// determines the speed of the animation
			{
				countDrawTime++;

				// timer for animation of falling star
				timerFallingStar += GetFrameTime();
				if (timerFallingStar >= 0.2f)
				{
					timerFallingStar = 0.0f;
					frameFallingStar += 1;
				}

				frameFallingStar = frameFallingStar % maxFramesFS;

				if (fixFallingStar == true)
				{
					DrawTextureRec(fallingStarEventL, Rectangle{ (fallingStarFrameWidth * frameFallingStar), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
					starFallingXdec += 0.1;
					starFallingYdec += 0.1;
				}
				else
				{
					DrawTextureRec(fallingStarEventR, Rectangle{ (fallingStarFrameWidth * frameFallingStar), 0, fallingStarFrameWidth, (float)fallingStarEventL.height }, Vector2{ (float)baseXFS - starFallingXdec, (float)baseYFS + starFallingYdec }, RAYWHITE);
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
			fixFallingStar = range2(rd2);

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

		DrawTexture(earthImgs[frameEearth], (float)((GetScreenWidth() / 4) - 90), (float)50, WHITE);
		
		DrawTexture(bottomBarN, 0, 0, WHITE);
		DrawTexture(marketTab, GetScreenWidth() / 2 - ((marketTab.width) / 2) - 100, GetScreenHeight() - (marketTab.height + 10), WHITE);
		DrawTexture(statisticsTab, GetScreenWidth() / 2 - ((statisticsTab.width) / 2), GetScreenHeight() - (statisticsTab.height + 10), WHITE);
		DrawTexture(miniGamesTab, GetScreenWidth() / 2 - ((miniGamesTab.width) / 2) + 100, GetScreenHeight() - (miniGamesTab.height + 10), WHITE);

		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	// Unload textures
	for (auto it = earthImgs.begin(); it != earthImgs.end(); ++it)
		UnloadTexture(*it);

	UnloadTexture(mouse);
	UnloadTexture(background);
	UnloadTexture(earth);
	UnloadTexture(fallingStarEventL);
	UnloadTexture(fallingStarEventR);
	UnloadTexture(bottomBarN);
	UnloadTexture(bottomBarG);
	UnloadTexture(bottomBarR);
	UnloadTexture(marketTab);
	UnloadTexture(statisticsTab);
	UnloadTexture(miniGamesTab);
	CloseWindow();
}

// Starts the game with resolution of 1980x1080 (WIP)
void gameRes1980x1080()
{
	system("color f0");

	std::string NSUD = "NOT SUPPORTED <=> under development";
	size_t sizeOfErr = NSUD.length();
	std::cout << '\n' << std::setw(43 + sizeOfErr) << NSUD << '\n';
}

void checkIfInBounds()
{
}








/*

const int rows = 3;
const int cols = 4;
const int cellSize = 100;
const int fruitSpacing = 42;

const char* fruitImages[] = {
	"img\\watermelon.png",
	"img\\pers.png",
	"img\\banan.png",
	"img\\straw.png"
};

const char* fruitDescriptions[] = {
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

void InitializeGrid() {
	spinning = true;
	roundWinnings = 0;
	roundEnded = false;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			grid[i][j] = GetRandomValue(0, 3);
		}
	}
}

void CheckForWin() {
	int winnings = 0;

	for (int i = 0; i < rows; ++i) {
		int count[4] = { 0 };

		for (int j = 0; j < cols; ++j) {
			count[grid[i][j]]++;
		}

		for (int k = 0; k < 4; ++k) {
			if (count[k] == 4) {
				switch (k) {
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

	if (winnings > 0 && !roundEnded) {
		totalWinnings += winnings;
		roundWinnings = winnings;
		roundEnded = true;
	}
}

bool IsMouseOverButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
	Vector2 mousePosition = GetMousePosition();
	return (mousePosition.x >= buttonX && mousePosition.x <= buttonX + buttonWidth &&
		mousePosition.y >= buttonY && mousePosition.y <= buttonY + buttonHeight);
}

int main() {
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

		DrawText("Moment Game", screenWidth / 2 - MeasureText("Moment Game", 30) / 2, 10, 30, WHITE);

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

	CloseWindow();

	return 0;
}



*/