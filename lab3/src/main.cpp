#include "Game.h"

// 2 вида машин чтобы обрабатывать столкновение по разному, переделать основной цикл игры, убрать из глоб области видимости

int main() {
    srand((unsigned)time(NULL));
    Game game;
    game.start();
    
    return 0;
}
