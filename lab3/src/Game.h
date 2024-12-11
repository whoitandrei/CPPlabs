#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector> 
#include <memory>
#include <ctime>
#include <fstream>
#include "GameObject.h"
#include "Leaderboard.h" 



class Game
{
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    enum collisionFlag {
        collectedShield,
        crash,
        nothing
    };
    collisionFlag collision(int carPos);
    void genEnemy(GameContext& context);
    void initGameObjects();
    std::wstring nickname;
    Leaderboard leaderboard;

public:
    Game(/* args */);
    ~Game();

   
    void drawBorder();
    void gameover();
    void instructions();
    void play();
    void displayInfo(int score, int shieldCount);
    void start();
    
};
