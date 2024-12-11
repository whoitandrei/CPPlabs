#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "general_funcs.h"
#include "GameContext.h"

#define WIN_WIDTH 70
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define LEFT_BORDER_X 16
#define RIGHT_BORDER_X 54
#define CAR_SIZE 4
#define SHIELD_SIZE 2
#define ESC 27

class GameObject {
public:
    GameObject();
    virtual ~GameObject();
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void act(GameContext& context) = 0;
    virtual int collision(int carPos) = 0;
    virtual void reset() = 0;
    virtual bool getFlag() = 0;
    virtual void updateFlag() = 0;
    virtual void gen() = 0;
};


class EnemyObject : public GameObject
{
private:
    int x;
    int y;
    bool flag;
public:
    EnemyObject();
    virtual ~EnemyObject();
    void move();
    void gen() override;
    void reset() override;
    int getX();
    int getY();
    bool getFlag() override;
    void updateFlag() override;
    void setX(int val);
};

class Car : public GameObject {
private:
    wchar_t car[4][4] = {
    L' ', L'#', L'#', L' ',
    L'#', L'#', L'#', L'#',
    L' ', L'#', L'#', L' ',
    L'#', L'#', L'#', L'#'
    };

    int carPos;

public:
    Car();
    virtual ~Car();
    void move(bool turn); // true - right; false - left
    int getCarPos();
    void reset() override;
    void draw() override;
    void erase() override;
    void act(GameContext& context) override;
    int collision(int carPos) override;
    bool getFlag() override;
    void updateFlag() override;
    void gen() override;
};

class Enemy : public EnemyObject{
private:
    wchar_t enemy[4][4] = {
    L'*', L'*', L'*', L'*',
    L' ', L'*', L'*', L' ',
    L'*', L'*', L'*', L'*',
    L' ', L'*', L'*', L' '
    };

public:
    Enemy();
    virtual ~Enemy();

    void draw() override;
    void erase() override;
    int collision(int carPos) override;
    void act(GameContext& context) override;
};

class MovingEnemy : public EnemyObject {
private:
    wchar_t enemy[4][4] = {
    L'*', L'*', L'*', L'*',
    L' ', L'*', L'*', L' ',
    L'*', L'*', L'*', L'*',
    L' ', L'<', L'>', L' '
    };
public:
    MovingEnemy();
    virtual ~MovingEnemy();
    void changeCol();

    void draw() override;
    void erase() override;
    int collision(int carPos) override;
    void act(GameContext& context) override;
};


class Shield : public EnemyObject {
private:
    wchar_t shield[2][2] = {
    L'+', L'+',
    L'+', L'+',
    };

public:
    Shield();
    virtual ~Shield();

    void draw() override;
    void erase() override;
    int collision(int carPos) override;
    void act(GameContext& context) override;
};