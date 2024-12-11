#include "GameContext.h"

// Конструктор
GameContext::GameContext()
    : score(0), shieldCount(0), isGameOver(false), carPos(SCREEN_WIDTH / 2 + 1),
      screenHeight(SCREEN_HEIGHT), activeEnemies(0), lastGenTime(clock()), lastEnemyY(SCREEN_HEIGHT) {}

// Геттеры
int GameContext::getScore() const { return score; }
int GameContext::getShieldCount() const { return shieldCount; }
bool GameContext::getIsGameOver() const { return isGameOver; }
int GameContext::getCarPos() const { return carPos; }
int GameContext::getScreenHeight() const { return screenHeight; }
int GameContext::getActiveEnemies() const { return activeEnemies; }
clock_t GameContext::getLastGenTime() const { return lastGenTime; }
int GameContext::getLastEnemyY() { return lastEnemyY; }

// Сеттеры
void GameContext::setCarPos(int pos) { carPos = pos; }
void GameContext::setActiveEnemies(int count) { activeEnemies = count; }
void GameContext::updateLastEnemyY(int y) { lastEnemyY = ((y < lastEnemyY) ? y : lastEnemyY); }
void GameContext::resetLastEnemyY() { lastEnemyY = SCREEN_HEIGHT; }
void GameContext::updateLastGenTime() { lastGenTime = clock(); }

// Методы
void GameContext::updateScore(int delta) { score += delta; }
void GameContext::decreaseShieldCount() { shieldCount--; }
void GameContext::increaseShieldCount() { shieldCount++; }
void GameContext::increaseActiveEnemies() { activeEnemies++; }
void GameContext::decreaseActiveEnemies() {
    if (activeEnemies > 0) {
        activeEnemies--;
    }
}
void GameContext::endGame() { isGameOver = true; }
