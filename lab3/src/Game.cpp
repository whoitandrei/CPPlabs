#include "Game.h"

using namespace std;


Game::Game(/* args */) : leaderboard("leaderboard.txt"){}

Game::~Game() {}

void Game::drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(LEFT_BORDER_X, i); wcout << L"|";
        gotoxy(RIGHT_BORDER_X, i); wcout << L"|";
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i); wcout << L"|";
    }
}

void Game::instructions() {
    system("cls");
    wcout << L"Instructions";
    wcout << L"\n----------------";
    wcout << L"\n Avoid Cars by moving left or right. ";
    wcout << L"\n collect shields to protect your car from crash ";
    wcout << L"\n enemies have 2 types: static and moving. moving can change columns while riding";
    wcout << L"\n\n Press 'a' to move left";
    wcout << L"\n Press 'd' to move right";
    wcout << L"\n Press 'esc' to exit and end game";
    wcout << L"\n\nPress any key to go back to menu";
    getch();
}

void Game::displayInfo(int score, int shieldCount){
    gotoxy(WIN_WIDTH - 3, 2); wcout << L"concentrate on road!";
    gotoxy(WIN_WIDTH + 6, 6); wcout << L"----------";
    gotoxy(WIN_WIDTH + 7, 5); wcout << L"Score: " << score << endl;
    gotoxy(WIN_WIDTH + 6, 4); wcout << L"----------";
    gotoxy(WIN_WIDTH + 2, 10); wcout << L"shields: " << "   "; // clear shields status
    gotoxy(WIN_WIDTH + 2, 10); wcout << L"shields: " << shieldCount;
}


void Game::gameover() {
    system("cls");
    wcout << endl;
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
    wcout << L"\n\tPress any key to go back to menu.";
    Sleep(500);
    std::vector<std::unique_ptr<GameObject>>().swap(gameObjects);
    // destroy context
    //update high score
    getch();
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


// Добавьте состояние для отслеживания времени генерации врагов
void Game::genEnemy(GameContext& context) {
    // Проверяем, если на экране меньше 2 врагов и прошло достаточно времени
    if (context.getActiveEnemies() < 2 && (clock() - context.getLastGenTime()) > CLOCKS_PER_SEC / 1.4) {
        for (auto& object : gameObjects) {
            // Найти первого неактивного врага
            if (dynamic_cast<EnemyObject*>(object.get()) && !object->getFlag()) {
                object->reset();
                context.increaseActiveEnemies(); // Увеличиваем количество активных врагов
                context.updateLastGenTime(); // Обновляем время последней генерации
                break;
            }
        }
    }
}

void Game::play() {
    system("cls");
    cout << "enter your nickname: \n";
    wcin >> nickname;
    system("cls");

    drawBorder();
    initGameObjects();
    // Инициализация контекста игры
    GameContext context;
    gotoxy(18, 5); wcout << L"Press any key to start";
    getch();
    gotoxy(18, 5); wcout << L"                      ";

    // Основной игровой цикл
    while (!context.getIsGameOver()) {
        drawBorder();
        displayInfo(context.getScore(), context.getShieldCount()); // щиты и счет + остальная информация
        genEnemy(context);
        leaderboard.display(WIN_WIDTH + 2, 12);
            
        // Действия всех объектов
        for (auto& object : gameObjects) {
            object->erase();
            object->act(context);  // выполняем базовые действия объектов (передвижение и удаление и тд)
            object->draw();
        }

        //обработать все (игрок + объекты) объекты на наличие коллизии и сделать из этого выводы
        collisionFlag collisionResult;
        collisionResult = collision(context.getCarPos());
        if (collisionResult != nothing){
            if (collisionResult == collectedShield) {
                context.increaseShieldCount();
            }   
            else context.decreaseShieldCount();
        }

        // Логика завершения игры или обновления состояния
        if (context.getShieldCount() < 0) {
            context.endGame();
        }

        // Задержка для стабильного FPS
        Sleep(50);
    }

    // Обработка завершения игры
    leaderboard.addEntry(nickname, context.getScore());
    gameover();
}

void Game::start(){
    do {
        system("cls");
        std::wcout << L"         ______" << std::endl;
        std::wcout << L"        /|_||_\\`.__" << std::endl;
        std::wcout << L"       (   _    _ _\\" << std::endl;
        std::wcout << L"       =`-(_)--(_)-'" << std::endl;
        std::wcout << L"                               " << std::endl;
        std::wcout << L"      Car Game by Andrei Zverev" << std::endl;
        std::wcout << L"               23206           " << std::endl;
        gotoxy(10, 10); wcout << L"Options:";
        gotoxy(10, 11); wcout << L"1. Start Game";
        gotoxy(10, 12); wcout << L"2. Instructions";
        gotoxy(10, 13); wcout << L"3. Quit";
        for (int i = 9; i < 17; i++) {
            gotoxy(30, i); wcout << L"|";
        }
        leaderboard.display(35, 10);
        gotoxy(10, 15); wcout << L"Selected option: ";
        wchar_t op = getche();

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