#include "Player.h"

Player::Player(int startR, int startC, int maxHp)
    : row(startR), col(startC), dir(Direction::RIGHT), hp(maxHp), maxHp(maxHp) {}

void Player::setDirection(Direction newDir) 
{
    dir = newDir;
}

std::pair<int, int> Player::getNextPos() const
{
    int nextR = row;
    int nextC = col;
    switch (dir) {
    case Direction::UP:    nextR--; break;
    case Direction::DOWN:  nextR++; break;
    case Direction::LEFT:  nextC--; break;
    case Direction::RIGHT: nextC++; break;
    }
    return { nextR, nextC };
}

void Player::move(int newR, int newC) 
{
    row = newR;
    col = newC;
}

void Player::decreaseHp() //扣血
{
    if (hp > 0) hp--;
}

bool Player::isDead() const //判断死亡
{
    return hp <= 0;
}

int Player::getRow() const { return row; }
int Player::getCol() const { return col; }
int Player::getHp() const { return hp; }
int Player::getMaxHp() const { return maxHp; }