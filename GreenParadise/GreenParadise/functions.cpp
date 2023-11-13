#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <conio.h>
#include <raylib.h>
#include "functions.h"

int countMoney = 4;	// default value - 4

const char* money[10] = {
	"0 lv", "300 lv", "600 lv", "900 lv", "1 200 lv",
	"1 500 lv", "1 800 lv", "2 100 lv", "2 400 lv", "2 700 lv"
};

const char* percantages[10] = {
	"0%", "25%", "30%", "35%", "50%",
	"65%", "70%", "75%", "80%", "100%"
};

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

void checkGamePick(int x, int y, Texture2D startB)
{
	if ((x >= (GetScreenWidth() / 2) - 250 && x <= (GetScreenWidth() / 2) - 250 + startB.width) && (y >= 380 && y <= 380 + startB.height))
	{
		beachCleaner();
	}
	else if ((x >= (GetScreenWidth() / 2) + 60 && x <= (GetScreenWidth() / 2) + 60 + startB.width) && (y >= 380 && y <= 380 + startB.height))
	{
		chanceTaker();
	}
}

void checkIfDonate(int x, int y, Texture2D images[], int* imageX, int* imageY)
{
	for (int i = 0; i < 4; i++)
	{
		if ((x >= imageX[i] && x <= imageX[i] + images[i].width) && (y >= imageY[i] && y <= imageY[i] + images[i].width))
		{
			if (money[countMoney] == "300 lv" || money[countMoney] == "600 lv" || money[countMoney] == "900 lv" || money[countMoney] == "1 200 lv" || money[countMoney] == "1 500 lv" || money[countMoney] == "1 800 lv" || money[countMoney] == "2 100 lv" || money[countMoney] == "2 400 lv" || money[countMoney] == "2 700 lv")
			{
				countMoney--;
			}
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

bool checkIfClose(int x, int y, Texture2D image, int imageX, int imageY)
{
	if ((x >= imageX && x <= imageX + image.width) && (y >= imageY && y <= imageY + image.height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void marketTabPopUp(short int* status)
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
	Texture2D tabBackground = LoadTexture("../../sprites/background/popUpWindow.png");
	Texture2D xButton = LoadTexture("../../sprites/buttons/xButton.png");
	Texture2D donateButton = LoadTexture("../../sprites/buttons/donateButton.png");
	Texture2D marketTab = LoadTexture("../../sprites/tabIcons/ecoMarketTab.png");
	Texture2D questionsTab = LoadTexture("../../sprites/tabIcons/questionsTab.png");
	Texture2D miniGamesTab = LoadTexture("../../sprites/tabIcons/ecoGamesTab.png");
	Texture2D forestFireFund = LoadTexture("../../sprites/fundIcons/fireFoundation.png");
	Texture2D forestFund = LoadTexture("../../sprites/fundIcons/forestFoundation.png");
	Texture2D waterFund = LoadTexture("../../sprites/fundIcons/seaFoundation.png");
	Texture2D cleaningFund = LoadTexture("../../sprites/fundIcons/landFoundation.png");

	int imageX2[] = { (GetScreenWidth() / 2) - 205, (GetScreenWidth() / 2) - 205, (GetScreenWidth() / 2) + 105, (GetScreenWidth() / 2) + 105 };
	int imageY2[] = { 300, 500, 300, 500 };
	Texture2D textures[4] = { forestFireFund, forestFund, waterFund, cleaningFund };

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

	int imageX[3] = { GetScreenWidth() / 2 - ((marketTab.width) / 2) - 100, GetScreenWidth() / 2 - ((questionsTab.width) / 2), GetScreenWidth() / 2 - ((miniGamesTab.width) / 2) + 100 };
	int imageY[3] = { GetScreenHeight() - (marketTab.height + 10), GetScreenHeight() - (questionsTab.height + 10), GetScreenHeight() - (miniGamesTab.height + 10) };

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
		DrawTexture(marketTab, imageX[0], imageY[0], WHITE);
		DrawTexture(questionsTab, imageX[1], imageY[1], WHITE);
		DrawTexture(miniGamesTab, imageX[2], imageY[2], WHITE);

		DrawTexture(tabBackground, 312, marketTab.height + 60, WHITE);
		DrawTexture(xButton, tabBackground.width + 266, xButton.height + 45, WHITE);
		
		DrawTexture(donateButton, (GetScreenWidth() / 2) - 205, 300, WHITE);
		DrawTexture(donateButton, (GetScreenWidth() / 2) - 205, 500, WHITE);
		DrawTexture(donateButton, (GetScreenWidth() / 2) + 105, 300, WHITE);
		DrawTexture(donateButton, (GetScreenWidth() / 2) + 105, 500, WHITE);
		
		DrawTexture(forestFireFund, (GetScreenWidth() / 2) - 300, 190, WHITE);
		DrawTexture(forestFund, (GetScreenWidth() / 2) - 220, 374, WHITE);
		DrawTexture(waterFund, (GetScreenWidth() / 2) + 45, 370, WHITE);
		DrawTexture(cleaningFund, (GetScreenWidth() / 2) + 50, 165, WHITE);

		DrawText(money[countMoney], 145, 40, 30, WHITE);
		DrawText("Money: ", 35, 40, 30, WHITE);
		DrawText("Help those fundations by donations", GetScreenWidth() / 2 - 188, 125, 21, BLACK);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			if (checkIfClose(GetMouseX(), GetMouseY(), xButton, tabBackground.width + 266, xButton.height + 45))
			{
				break;
			}
			else
			{
				checkIfDonate(GetMouseX(), GetMouseY(), textures, imageX2, imageY2);
			}
		}

		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

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
	UnloadTexture(tabBackground);
	UnloadTexture(xButton);
	UnloadTexture(donateButton);
	UnloadTexture(marketTab);
	UnloadTexture(questionsTab);
	UnloadTexture(miniGamesTab);
	UnloadTexture(forestFireFund);
	UnloadTexture(forestFund);
	UnloadTexture(waterFund);
	UnloadTexture(cleaningFund);

	*status = 0;
}

void questionsPopUp(short int* status)
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
	Texture2D tabBackground = LoadTexture("../../sprites/background/popUpWindow.png");
	Texture2D xButton = LoadTexture("../../sprites/buttons/xButton.png");
	Texture2D buyButton = LoadTexture("../../sprites/buttons/buyButton.png");
	Texture2D marketTab = LoadTexture("../../sprites/tabIcons/ecoMarketTab.png");
	Texture2D questionsTab = LoadTexture("../../sprites/tabIcons/questionsTab.png");
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

	int imageX[3] = { GetScreenWidth() / 2 - ((marketTab.width) / 2) - 100, GetScreenWidth() / 2 - ((questionsTab.width) / 2), GetScreenWidth() / 2 - ((miniGamesTab.width) / 2) + 100 };
	int imageY[3] = { GetScreenHeight() - (marketTab.height + 10), GetScreenHeight() - (questionsTab.height + 10), GetScreenHeight() - (miniGamesTab.height + 10) };

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
		DrawTexture(marketTab, imageX[0], imageY[0], WHITE);
		DrawTexture(questionsTab, imageX[1], imageY[1], WHITE);
		DrawTexture(miniGamesTab, imageX[2], imageY[2], WHITE);

		DrawTexture(tabBackground, 312, marketTab.height + 60, WHITE);
		DrawTexture(xButton, tabBackground.width + 266, xButton.height + 45, WHITE);

		DrawText(money[countMoney], 145, 40, 30, WHITE);
		DrawText("Money: ", 35, 40, 30, WHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			if (checkIfClose(GetMouseX(), GetMouseY(), xButton, tabBackground.width + 266, xButton.height + 45))
			{
				break;
			}
		}

		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

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
	UnloadTexture(tabBackground);
	UnloadTexture(xButton);
	UnloadTexture(marketTab);
	UnloadTexture(questionsTab);
	UnloadTexture(miniGamesTab);

	*status = 0;
}

void miniGamesPopUp(short int* status)
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
	Texture2D tabBackground = LoadTexture("../../sprites/background/popUpWindow.png");
	Texture2D xButton = LoadTexture("../../sprites/buttons/xButton.png");
	Texture2D playButton = LoadTexture("../../sprites/buttons/playGamesButton.png");
	Texture2D marketTab = LoadTexture("../../sprites/tabIcons/ecoMarketTab.png");
	Texture2D questionsTab = LoadTexture("../../sprites/tabIcons/questionsTab.png");
	Texture2D miniGamesTab = LoadTexture("../../sprites/tabIcons/ecoGamesTab.png");
	Texture2D beachCleaner = LoadTexture("../../sprites/miniGames/coverImages/beachCleanerCI.png");
	Texture2D chanceTaker = LoadTexture("../../sprites/miniGames/coverImages/chanceTakerCI.png");

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

	int imageX[3] = { GetScreenWidth() / 2 - ((marketTab.width) / 2) - 100, GetScreenWidth() / 2 - ((questionsTab.width) / 2), GetScreenWidth() / 2 - ((miniGamesTab.width) / 2) + 100 };
	int imageY[3] = { GetScreenHeight() - (marketTab.height + 10), GetScreenHeight() - (questionsTab.height + 10), GetScreenHeight() - (miniGamesTab.height + 10) };

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
		DrawTexture(marketTab, imageX[0], imageY[0], WHITE);
		DrawTexture(questionsTab, imageX[1], imageY[1], WHITE);
		DrawTexture(miniGamesTab, imageX[2], imageY[2], WHITE);

		DrawTexture(tabBackground, 312, marketTab.height + 60, WHITE);
		DrawTexture(xButton, tabBackground.width + 266, xButton.height + 45, WHITE);
		DrawTexture(playButton, (GetScreenWidth() / 2) - 250, 380, WHITE);
		DrawTexture(playButton, (GetScreenWidth() / 2) + 60, 380, WHITE);

		DrawTexture(beachCleaner, (GetScreenWidth() / 2) - 250, 220, WHITE);
		DrawTexture(chanceTaker, (GetScreenWidth() / 2) + 70, 220, WHITE);

		DrawText(money[countMoney], 145, 40, 30, WHITE);
		DrawText("Money: ", 35, 40, 30, WHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			if (checkIfClose(GetMouseX(), GetMouseY(), xButton, tabBackground.width + 266, xButton.height + 45))
			{
				break;
			}
			else
			{
				checkGamePick(GetMouseX(), GetMouseY(), playButton);
			}
		}

		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

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
	UnloadTexture(tabBackground);
	UnloadTexture(xButton);
	UnloadTexture(playButton);
	UnloadTexture(marketTab);
	UnloadTexture(questionsTab);
	UnloadTexture(miniGamesTab);

	*status = 0;
}

int checkIfInBoundsTabs(int x, int y, Texture2D images[], int* imageX, int* imageY)
{
	for (int i = 0; i < 3; i++)
	{
		if ((x >= imageX[i] && x <= imageX[i] + images[i].width) && (y >= imageY[i] && y <= imageY[i] + images[i].height))
		{
			if (i == 0)
			{
				return 1;
			}
			else if (i == 1)
			{
				return 2;
			}
			else if (i == 2)
			{
				return 3;
			}
		}
	}

	return 0;
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
	Texture2D questionsTab = LoadTexture("../../sprites/tabIcons/questionsTab.png");
	Texture2D miniGamesTab = LoadTexture("../../sprites/tabIcons/ecoGamesTab.png");

	Texture2D textures[] = { marketTab, questionsTab, miniGamesTab };

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
	
	short int checkIfTabActive = 0;
	int imageX[3] = { GetScreenWidth() / 2 - ((marketTab.width) / 2) - 100, GetScreenWidth() / 2 - ((questionsTab.width) / 2), GetScreenWidth() / 2 - ((miniGamesTab.width) / 2) + 100 };
	int imageY[3] = { GetScreenHeight() - (marketTab.height + 10), GetScreenHeight() - (questionsTab.height + 10), GetScreenHeight() - (miniGamesTab.height + 10) };

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
		DrawTexture(marketTab, imageX[0], imageY[0], WHITE);
		DrawTexture(questionsTab, imageX[1], imageY[1], WHITE);
		DrawTexture(miniGamesTab, imageX[2], imageY[2], WHITE);

		DrawText(money[countMoney], 145, 40, 30, WHITE);
		DrawText("Money: ", 35, 40, 30, WHITE);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (checkIfTabActive == 0)
			{
				switch (checkIfInBoundsTabs(GetMouseX(), GetMouseY(), textures, imageX, imageY))
				{
				case 1: checkIfTabActive = 1; marketTabPopUp(&checkIfTabActive); break;
				case 2: checkIfTabActive = 2; questionsPopUp(&checkIfTabActive); break;
				case 3: checkIfTabActive = 3; miniGamesPopUp(&checkIfTabActive); break;
				default:; break;
				}
			}
		}

		DrawTexturePro(mouse, Rectangle{ 0, 0, 392, 392 }, Rectangle{ xMouseTrack, yMouseTrack, 25, 25 }, Vector2{ 0, 0 }, 0, RAYWHITE);

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
	UnloadTexture(questionsTab);
	UnloadTexture(miniGamesTab);

	for (int i = 0; i < 3; i++)
	{
		UnloadTexture(textures[i]);
	}

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