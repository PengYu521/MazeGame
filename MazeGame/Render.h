#ifndef RENDER_H
#define RENDER_H

#include "Common.h"
#include "Map.h"
#include "Player.h"
#include <graphics.h>

class Render //功能类
{
public:
    Render(const Map& map, const Player& player, int winW, int winH);
    void initWindow();
    void closeWindow();
    void drawMenu(int selectedMap);
    void drawMap();
    void drawPlayer();
    void drawHp();
    void clearScreen();
    void beginBatch();
    void endBatch();
    void drawGameOver(bool isWin);

private:
    const Map& map;
    const Player& player;
    int windowWidth;
    int windowHeight;
    IMAGE imgPlayer;
    void initImage();
};

#endif