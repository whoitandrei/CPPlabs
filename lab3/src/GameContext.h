#pragma once
#include <ctime>

#define WIN_WIDTH 70
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26

class GameContext {
private:
    int score;
    int shieldCount;
    bool isGameOver;
    int carPos;
    int screenHeight;
    int activeEnemies;      
    clock_t lastGenTime;     
    int lastEnemyY;          

public:
    // Конструктор
    GameContext();

    // Геттеры
    int getScore() const;
    int getShieldCount() const;
    bool getIsGameOver() const;
    int getCarPos() const;
    int getScreenHeight() const;
    int getActiveEnemies() const;
    clock_t getLastGenTime() const;
    int getLastEnemyY();
    
    // Сеттеры
    void setCarPos(int pos);
    void setActiveEnemies(int count);
    void updateLastEnemyY(int y);
    void resetLastEnemyY();
    void updateLastGenTime();

    // Методы
    void updateScore(int delta);
    void decreaseShieldCount();
    void increaseShieldCount();
    void increaseActiveEnemies();
    void decreaseActiveEnemies();
    void endGame();
};
