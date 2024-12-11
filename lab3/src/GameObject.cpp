    #include "GameObject.h"

    using namespace std;

    GameObject::GameObject() {}
    GameObject::~GameObject() {}


    // Car function prototypes
    void Car::draw() {
        for (int i = 0; i < CAR_SIZE; i++) {
            for (int j = 0; j < CAR_SIZE; j++) {
                gotoxy(j + carPos, i + 22); wcout << car[i][j];
            }
        }
    }

    void Car::erase() {
        for (int i = 0; i < CAR_SIZE; i++) {
            for (int j = 0; j < CAR_SIZE; j++) {
                gotoxy(j + carPos, i + 22); wcout << L" ";
            }
        }
    }

    Car::Car(){ carPos = WIN_WIDTH / 2 - 1; }
    Car::~Car() {carPos = WIN_WIDTH / 2 - 1;}
    void Car::move(bool turn) { carPos += (turn ? CAR_SIZE : -CAR_SIZE); }
    int Car::getCarPos() { return carPos; }

    void Car::act(GameContext& context){
        if (kbhit()) {
                wchar_t ch = getch();
                if (ch == L'a' || ch == L'A') {
                    if (carPos > LEFT_BORDER_X + (CAR_SIZE / 2)) 
                        move(false);
                }
                if (ch == L'd' || ch == L'D') {
                    if (carPos < RIGHT_BORDER_X - CAR_SIZE)
                        move(true);
                }
                if (ch == ESC) { // 27 = ESC
                    context.endGame();
                }
        }
        context.setCarPos(carPos);
    }

    int Car::collision(int carPos){
        return 0;
    }

    void Car::reset(){
        carPos = WIN_WIDTH / 2 - 1;
    }

    bool Car::getFlag() {return true;}
    void Car::updateFlag() {}
    void Car::gen() {}

    // EnemyObject func prototypes
    EnemyObject::EnemyObject() : y(1), flag(false), x(WIN_WIDTH / 2) {}
    EnemyObject::~EnemyObject() {y = 1; flag = false; x = 0;}
    int EnemyObject::getX() { return x; }
    int EnemyObject::getY() { return y; }
    bool EnemyObject::getFlag() {return flag; }
    void EnemyObject::move() {if (flag) y++;}
    void EnemyObject::updateFlag() { flag = (flag ? false : true);}
    void EnemyObject::gen() {x = 17 + rand() % (33);}
    void EnemyObject::setX(int val) {x=val;}

    void EnemyObject::reset() {
        erase();
        y = 1;
        updateFlag();
        gen();
    }


    // Enemy override functions
    Enemy::Enemy() : EnemyObject() {}
    Enemy::~Enemy() {}

    void Enemy::draw() {
        if (getFlag()) {
            for (int i = 0; i < CAR_SIZE; ++i){
                for (int j = 0; j < CAR_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << enemy[i][j];
                }
            }
        }        
    }

    void Enemy::erase() {
        if (getFlag()) {
            for (int i = 0; i < CAR_SIZE; ++i){
                for (int j = 0; j < CAR_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << L" ";
                }
            }
        }
    }

    int Enemy::collision(int carPos) {
        if (getY() + CAR_SIZE >= 23) {
            if (getX() + CAR_SIZE - carPos >= 0 && getX() + CAR_SIZE - carPos < 8) {
                return 1;
            }
        }
        return 0;
    }

    void Enemy::act(GameContext& context){
        move();
        context.updateLastEnemyY(getY());
        if (getY() > SCREEN_HEIGHT - CAR_SIZE) {
            reset();
            context.decreaseActiveEnemies();
            context.updateScore(1);
        }
    }

    // Shield override functions 
    Shield::Shield() : EnemyObject() {}
    Shield::~Shield() {}


    void Shield::draw() {
        if (getFlag()) {
            for (int i = 0; i < SHIELD_SIZE; ++i){
                for (int j = 0; j < SHIELD_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << shield[i][j];
                }
            }
        }   
    }

    void Shield::erase() {
        if (getFlag()) {
            for (int i = 0; i < SHIELD_SIZE; ++i){
                for (int j = 0; j < SHIELD_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << L" ";
                }
            }
        }
    }

    int Shield::collision(int carPos) {
        if (getY() + SHIELD_SIZE >= SCREEN_HEIGHT - 3) {
            if (getX() + SHIELD_SIZE - carPos >= 0 && getX() + SHIELD_SIZE - carPos < 6) {
                return 1;
            }
        }
        return 0;
    }

    void Shield::act(GameContext& context){
        move();    
        if (rand()%50==0 && !getFlag() && context.getLastEnemyY() == CAR_SIZE){
            updateFlag();
        }
        if (getY() > SCREEN_HEIGHT - SHIELD_SIZE) {
            reset();
        }
        context.resetLastEnemyY();
    }

    // MovingEnemy override functions
    MovingEnemy::MovingEnemy() : EnemyObject() {}
    MovingEnemy::~MovingEnemy() {}

    void MovingEnemy::draw() {
        if (getFlag()) {
            for (int i = 0; i < CAR_SIZE; ++i){
                for (int j = 0; j < CAR_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << enemy[i][j];
                }
            }
        }  
    }

    void MovingEnemy::erase() {
        if (getFlag()) {
            for (int i = 0; i < CAR_SIZE; ++i){
                for (int j = 0; j < CAR_SIZE; ++j) {
                    gotoxy(j+getX(), getY()+i); 
                    wcout << L" ";
                }
            }
        }
    }

    void MovingEnemy::changeCol(){
        int rm = rand()%15;
        if (rm == 1 && getY() < SCREEN_HEIGHT - 10){
            int newCol = getX() + 1 + rand()%5;
            if (newCol < RIGHT_BORDER_X - CAR_SIZE)
                setX(newCol);
        }
        else if (rm == 2 && getY() < SCREEN_HEIGHT - 10){
            int newCol = getX() - 1 - rand()%5;
            if (newCol > LEFT_BORDER_X)
                setX(newCol);
        }
    }

    int MovingEnemy::collision(int carPos) {
        if (getY() + CAR_SIZE >= 23) {
            if (getX() + CAR_SIZE - carPos >= 0 && getX() + CAR_SIZE - carPos < 9) {
                return 1;
            }
        }
        return 0;
    }

    void MovingEnemy::act(GameContext& context){
        move();
        changeCol();
        context.updateLastEnemyY(getY());
        if (getY() > SCREEN_HEIGHT - CAR_SIZE) {
            reset();
            context.decreaseActiveEnemies();
            context.updateScore(1);
        }
    }