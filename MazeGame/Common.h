#ifndef COMMON_H
#define COMMON_H


enum class GameState //游戏状态
{
    MENU,
    PLAYING
};

enum class CellType//方块类型
{
    SPACE,
    WALL,
    DOOR,
    PLAYER,
    TRAP
};
enum class Direction //方向类型
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const int ROW = 40;
const int COL = 40;
const int GRID_SIZE = 15;
const int MAX_HP = 3;
const int TRAP_COUNT = 8;
const int WINDOW_WIDTH = COL * GRID_SIZE;
const int WINDOW_HEIGHT = ROW * GRID_SIZE + 40;
const int TRAP_LIFETIME = 50;
const int TRAP_SPAWN_INTERVAL = 30;

#endif