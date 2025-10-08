#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Map.h"
#include "Player.h"
#include "Render.h"

class Game //游戏类
{
public:
    Game();
    void init();
    void run();

private:
    GameState currentState;
    int selectedMap;
    bool shouldMove;
    bool keyReleased;
    int frameCounter; 
    Map map;
    Player player;
    Render render;
    void handleMenuInput();
    void handleGameInput();
    void update();
};

#endif