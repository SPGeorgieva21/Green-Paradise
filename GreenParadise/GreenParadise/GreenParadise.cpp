#include <iostream>
#include "raylib.h"

int main()
{
	InitWindow(800, 600, "Algo-Rhythm_Testing");
	SetWindowState(FLAG_VSYNC_HINT);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKBLUE);

		DrawFPS(10, 10); //temporary
		EndDrawing();
	}

	CloseWindow();
}