#include "Game.h"



Game::Game(/* args */) : leaderboard("leaderboard.txt"){}

Game::~Game() {}

void Game::drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(LEFT_BORDER_X, i); std::wcout << L"|";
        gotoxy(RIGHT_BORDER_X, i); std::wcout << L"|";
    }
    
}

void Game::instructions() {
    system("cls");
    std::wcout << L"Instructions";
    std::wcout << L"\n----------------";
    std::wcout << L"\n Avoid Cars by moving left or right. ";
    std::wcout << L"\n collect shields to protect your car from crash ";
    std::wcout << L"\n enemies have 2 types: static and moving. moving can change columns while riding";
    std::wcout << L"\n\n Press 'a' to move left";
    std::wcout << L"\n Press 'd' to move right";
    std::wcout << L"\n Press 'esc' to exit and !end game!";
    std::wcout << L"\n\nPress any key to go back to menu";
    _getch();
}

void Game::displayInfo(int score, int shieldCount){
    gotoxy(WIN_WIDTH - 3, 2); std::wcout << L"now playing: " << nickname;
    //gotoxy(WIN_WIDTH - 3, 2); std::wcout << L"concentrate on road!";
    gotoxy(WIN_WIDTH + 6, 4); std::wcout << L"----------";
    gotoxy(WIN_WIDTH + 7, 5); std::wcout << L"Score: " << score << std::endl;
    gotoxy(WIN_WIDTH + 6, 6); std::wcout << L"----------";
    gotoxy(WIN_WIDTH + 2, 10); std::wcout << L"shields: " << "   "; // clear shields status
    gotoxy(WIN_WIDTH + 2, 10); std::wcout << L"shields: " << shieldCount;
}


void Game::gameover() {
    system("cls");
    std::wcout << std::endl;
    std::wcout << L"          ***********          " << std::endl;
    std::wcout << L"       **             **       " << std::endl;
    std::wcout << L"     **     O     O     **     " << std::endl;
    std::wcout << L"    *         \\_/         *    " << std::endl;
    std::wcout << L"   *       __________      *   " << std::endl;
    std::wcout << L"    *     /          \\    *    " << std::endl;
    std::wcout << L"     **                 **     " << std::endl;
    std::wcout << L"       **             **       " << std::endl;
    std::wcout << L"          ***********          " << std::endl;
    std::wcout << L"                               " << std::endl;
    std::wcout << L"        G A M E  O V E R       " << std::endl;
    std::wcout << L"\n\tPress any key to go back to menu.";
    Sleep(500);
    std::vector<std::unique_ptr<GameObject>>().swap(gameObjects);
    // destroy context
    //update high score
    _getch();
}



void Game::initGameObjects(){
    gameObjects.push_back(std::make_unique<Car>());
    gameObjects.push_back(std::make_unique<Enemy>());
    gameObjects.push_back(std::make_unique<MovingEnemy>());
    gameObjects.push_back(std::make_unique<Shield>());
}

Game::collisionFlag Game::collision(int carPos) {
    for (auto& object : gameObjects) {
        if (dynamic_cast<Shield*>(object.get())) {
            if (object->collision(carPos)) {
                object->reset();
                return collectedShield;
            }
        }
        else if (dynamic_cast<EnemyObject*>(object.get())) {
            if (object->collision(carPos)) {
                object->reset();
                object->updateFlag();
                return crash;
            }
        } 
    }
    return nothing;
}


void Game::genEnemy(GameContext& context) {
    if (context.getActiveEnemies() < 2 && (clock() - context.getLastGenTime()) > CLOCKS_PER_SEC / 1.4) {
        for (auto& object : gameObjects) {
            if (dynamic_cast<EnemyObject*>(object.get()) && !object->getFlag()) {
                object->reset();
                context.increaseActiveEnemies();
                context.updateLastGenTime(); 
                break;
            }
        }
    }
}

void Game::play() {
    system("cls");
    std::cout << "enter your nickname (without spaces): \n";
    std::wcin >> nickname;

    system("cls");
    drawBorder();
    initGameObjects();
    GameContext context;
    
    // ожидание старта игры
    gotoxy(18, 5); std::wcout << L"Press any key to start";
    _getch();
    gotoxy(18, 5); std::wcout << L"                      ";

    while (!context.getIsGameOver()) {
        drawBorder();
        displayInfo(context.getScore(), context.getShieldCount()); 
        genEnemy(context);
        leaderboard.display(WIN_WIDTH + 2, 12);
            
        for (auto& object : gameObjects) {
            object->erase();
            object->act(context);  
            object->draw();
        }

        collisionFlag collisionResult;
        collisionResult = collision(context.getCarPos());
        if (collisionResult != nothing){
            if (collisionResult == collectedShield) {
                context.increaseShieldCount();
            }   
            else context.decreaseShieldCount();
        }

        if (context.getShieldCount() < 0) {
            context.endGame();
        }

        Sleep(50);
    }

    leaderboard.addEntry(nickname, context.getScore());
    gameover();
}

void Game::start(){
    do {
        setcursor(false, 0);
        system("cls");
        std::wcout << L"         ______" << std::endl;
        std::wcout << L"        /|_||_\\`.__" << std::endl;
        std::wcout << L"       (   _    _ _\\" << std::endl;
        std::wcout << L"       =`-(_)--(_)-'" << std::endl;
        std::wcout << L"                               " << std::endl;
        std::wcout << L"      Car Game by Andrei Zverev" << std::endl;
        std::wcout << L"               23206           " << std::endl;
        gotoxy(10, 10); std::wcout << L"Options:";
        gotoxy(10, 11); std::wcout << L"1. Start Game";
        gotoxy(10, 12); std::wcout << L"2. Instructions";
        gotoxy(10, 13); std::wcout << L"3. Quit";
        for (int i = 9; i < 17; i++) {
            gotoxy(30, i); std::wcout << L"|";
        }
        leaderboard.display(35, 10);
        gotoxy(10, 15); std::wcout << L"Selected option: ";
        wchar_t op = _getche();

        if (op == L'1') {
            play();
        }
        else if (op == L'2') instructions();
        else if (op == L'3') {
            system("cls");
            setcursor(true, 20);
            exit(0);
        }

    } while (1);
}