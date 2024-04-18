#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <Windows.h>
#include <thread>
#include"GameEngine.h"
#define M_PI 3.14159265358979323846

std::wstring fire;

int main()
{
    fire += L"*******▀▀*****▀▀**********";
    fire += L"*****▀▀▀▀▀***▀▀▀▀*****▀▀**";
    fire += L"**▀▀**▀▀▀▀▀*▀▀▀▀▀▀**▀▀▀***";
    fire += L"***▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀****";
    fire += L"*****▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀***";
    fire += L"**▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀*****";
    fire += L"*****▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀*****";
    fire += L"***▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀*****";
    fire += L"**▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀*****";
    
    int iterator = 0;
    GameEngine shooter;

    //std::thread routine(move_sprite);

    shooter.CreateScreen();

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    //routine.join();
    //int pos = iterator;
    while (true) {
        

        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();
        
        shooter.CheckKeysState(fElapsedTime);
        shooter.WallsRayTrace();
     
        shooter.DrawSprite(fire, 26, 9, 30, 20);
        shooter.DrawSprite(fire, 26, 9, iterator, 20);

        shooter.DisplayScreen();
    }
    return 0;
}
