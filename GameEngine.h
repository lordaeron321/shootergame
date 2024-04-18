#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>

class GameEngine
{
	

	float fPlayerX = 8.0f;
	float fPlayerY = 4.0f;
	float fPlayerA = 0.0f;

	float fFOV = 3.14159 / 4.0;

	int ScreenW = 120;
	int ScreenH = 40;

	int nMapHeight = 16;
	int nMapWidth = 16;

	int MaxDistance = 16;

	//gun variables
	float AnimationVariable = 0;
	int defaultGunPosition = 31 * 120 + 46;
	int gunPosition = defaultGunPosition;
	bool moving = false;

	int counter = 0;
	std::wstring map;
	//shoot variable
	bool if_shooting = false;

	public:
	wchar_t* screen = new wchar_t[ScreenW* ScreenH];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD dwBytesWritten = 0;
	

	GameEngine() {
		map += L"################";
		map += L"#..............#";
		map += L"#........#######";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#######.......#";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#######........#";
		map += L"#..............#";
		map += L"#......#....####";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#.......########";
		map += L"#..............#";
		map += L"################";
		//26x9
	}
	void CreateScreen();

	void DrawSprite(std::wstring sprite, int x_Size, int y_Size, int x_position, int y_position);

	void DisplayScreen();

	void WallsRayTrace();

	void CheckKeysState(float fElapsedTime);

	void PrintOnScreen(int x, int y, char character);

	


};

