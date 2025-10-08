#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include <utility>

class Player //玩家类
{
public:
    Player(int startR, int startC, int maxHp);
    void setDirection(Direction newDir);
    std::pair<int, int> getNextPos() const;
    void move(int newR, int newC);
    void decreaseHp();
    bool isDead() const;
    int getRow() const;
    int getCol() const;
    int getHp() const;
    int getMaxHp() const;

private:
    int row;
    int col;
    Direction dir;
    int hp;
    int maxHp;
};

#endif