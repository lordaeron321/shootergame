#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>

void GameEngine::PrintOnScreen(int x, int y, char character) {
    screen[x + (y * ScreenW)] = character;
}
void GameEngine::DrawSprite(std::wstring sprite, int x_Size, int y_Size, int x_position, int y_position){
   
    for (int i = 0; i < y_Size; i++) {
        for (size_t j = 0; j < x_Size; j++){
            if (sprite[i * x_Size + j] != '*') {
                screen[((y_position + i) * ScreenW) + x_position + j] = sprite[i * x_Size + j];
            }
        }
    }
}
void GameEngine::WallsRayTrace() {
    for (int x = 0; x < ScreenW; x++)
    {
        float fRayAngle = (fPlayerA - fFOV / 2.0f) + (float)x / (float)ScreenW * fFOV;

        bool WallHit = false;
        bool BoundryHit = false;
        float TestRayLength = 0;

        float UniVectorX = cos(fRayAngle);
        float UniVectorY = sin(fRayAngle);

        while (WallHit == false && TestRayLength <= MaxDistance) {

            TestRayLength += 0.01f;

            int TestRayX = (int)(fPlayerX + UniVectorX * TestRayLength);
            int TestRayY = (int)(fPlayerY + UniVectorY * TestRayLength);

            if (map[TestRayY * nMapWidth + TestRayX] == '#') {
                WallHit = true;

                std::vector <std::pair<float, float>> points;
                for (int ix = 0; ix < 2; ix++)
                {
                    for (int iy = 0; iy < 2; iy++)
                    {
                        float pCornerX = (float)TestRayX + ix - fPlayerX;
                        float pCornerY = (float)TestRayY + iy - fPlayerY;
                        float d = sqrt(pCornerX * pCornerX + pCornerY * pCornerY);
                        float dif = (UniVectorX * pCornerX / d + UniVectorY * pCornerY / d);
                        std::pair<float, float> p;
                        p.first = d;
                        p.second = dif;
                        points.push_back(p);

                    }
                }
                std::sort(points.begin(), points.end());

                if (acos(points.at(0).second) < 0.008)BoundryHit = true;
                if (acos(points.at(1).second) < 0.008)BoundryHit = true;
            }
        }

        int WallHeight = (float)(ScreenH / 2.0) - ScreenH / ((float)TestRayLength);
        int WallBottom = ScreenH - WallHeight;


        for (int y = 0; y < ScreenH; y++)

        {
            if (y < WallBottom && y > WallHeight) {

                if (BoundryHit)screen[x + (y * ScreenW)] = ' ';
                else if (TestRayLength >= 0 && TestRayLength < 5)screen[x + (y * ScreenW)] = 0x2593;
                else if (TestRayLength >= 5 && TestRayLength < 9)screen[x + (y * ScreenW)] = 0x2592;
                else if (TestRayLength >= 9)screen[x + (y * ScreenW)] = 0x2591;

            }
            else if (y < WallHeight) {
                if (y >= 0 && y < 5)screen[x + (y * ScreenW)] = 0x2593;
                if (y >= 5 && y < 10)screen[x + (y * ScreenW)] = 0x2592;
                if (y >= 10 && y < 20)screen[x + (y * ScreenW)] = 0x2591;
            }
            else if (y > WallBottom) {
                if (y > 20 && y < 30)screen[x + (y * ScreenW)] = 0x2591;
                if (y >= 30 && y < 35)screen[x + (y * ScreenW)] = 0x2592;
                if (y >= 35 && y < 40)screen[x + (y * ScreenW)] = 0x2593;
            }
            else screen[x + (y * ScreenW)] = ' ';
        }
    }
    moving = false;
    if_shooting = false;
}

void GameEngine::DisplayScreen() {
    screen[ScreenW * ScreenH - 1] = '\0';
    WriteConsoleOutputCharacter(hConsole, screen, ScreenW * ScreenH, { 0,0 }, &dwBytesWritten);
}

void GameEngine::CheckKeysState(float fElapsedTime) {
  

    if (GetAsyncKeyState((unsigned short)'A') & 0x8000) fPlayerA -= (1.5) * fElapsedTime;

    if (GetAsyncKeyState((unsigned short)'D') & 0x8000) fPlayerA += (1.5) * fElapsedTime;

    if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {

        float EYEVectorX = cos(fPlayerA);
        float EYEVectorY = sin(fPlayerA);
        float moveX = float(fPlayerX + EYEVectorX * 4 * fElapsedTime);
        float moveY = float(fPlayerY + EYEVectorY * 4 * fElapsedTime);
        float buforX = fPlayerX;
        float buforY = fPlayerY;
        if (moveX < nMapWidth && moveX > 0)fPlayerX = moveX;
        if (moveY < nMapHeight && moveY > 0)fPlayerY = moveY;
        moving = true;
    }
    if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {

        float EYEVectorX = cos(fPlayerA);
        float EYEVectorY = sin(fPlayerA);

        float moveX = float(fPlayerX - EYEVectorX * 4 * fElapsedTime);
        float moveY = float(fPlayerY - EYEVectorY * 4 * fElapsedTime);

        if (moveX < nMapWidth && moveX > 0)fPlayerX = moveX;
        if (moveY < nMapHeight && moveY > 0)fPlayerY = moveY;

        moving = true;

    }
    if (GetAsyncKeyState((unsigned short)' ') & 0x8000) {

        if (if_shooting != true)if_shooting = true;

    }
}

void GameEngine::CreateScreen() {
    SetConsoleActiveScreenBuffer(this -> hConsole);
}