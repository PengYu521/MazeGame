#include "Render.h"
#include <windows.h>
#include <tchar.h>

#pragma warning(disable: 4996)

Render::Render(const Map& map, const Player& player, int winW, int winH)
    : map(map), player(player), windowWidth(winW), windowHeight(winH) {
    initImage();
}

void Render::initWindow() //初始化
{
    initgraph(windowWidth, windowHeight);
    setbkcolor(WHITE);
    cleardevice();
}

void Render::closeWindow()
{
    closegraph();
}

void Render::drawMenu(int selectedMap) //绘制菜单
{
    cleardevice();
    settextcolor(BLACK);

    settextstyle(30, 0, _T("宋体"));
    outtextxy(windowWidth / 2 - 100, 50, _T("迷宫游戏"));

    setlinecolor(BLACK);
    setfillcolor(LIGHTGRAY);
    fillrectangle(windowWidth / 2 - 150, 150, windowWidth / 2 + 150, 200);
    fillrectangle(windowWidth / 2 - 150, 220, windowWidth / 2 + 150, 270);

    settextstyle(20, 0, _T("宋体"));
    outtextxy(windowWidth / 2 - 30, 165, _T("地图1"));
    outtextxy(windowWidth / 2 - 30, 235, _T("地图2"));

    setlinecolor(RED);
    setlinestyle(PS_SOLID, 3);
    if (selectedMap == 1) {
        rectangle(windowWidth / 2 - 150, 150, windowWidth / 2 + 150, 200);
    }
    else {
        rectangle(windowWidth / 2 - 150, 220, windowWidth / 2 + 150, 270);
    }
    setlinestyle(PS_SOLID, 1);

    settextstyle(16, 0, _T("宋体"));
    outtextxy(windowWidth / 2 - 120, 350, _T("使用上下键选择，回车键确定"));
}


void Render::drawMap() //绘制地图
{
    int gridSize = map.getGridSize();
    setfillcolor(RGB(50, 50, 50)); 
    fillrectangle(0, 0, windowWidth, windowHeight - 40);

    for (int r = 0; r < map.getRows(); r++) {
        for (int c = 0; c < map.getCols(); c++) {

            if (!map.isExplored(r, c)) {
                continue;
            }

            int x = c * gridSize;
            int y = r * gridSize;
            switch ((CellType)map.getCell(r, c)) {
            case CellType::WALL:
                setfillcolor(RGB(93, 107, 153));
                fillrectangle(x, y, x + gridSize, y + gridSize);
                break;
            case CellType::DOOR:
                setfillcolor(RGB(0, 0, 170));
                fillrectangle(x, y, x + gridSize, y + gridSize);
                break;
            case CellType::TRAP:
                setfillcolor(RGB(255, 165, 0));
                fillrectangle(x, y, x + gridSize, y + gridSize);
                setlinecolor(BLACK);
                line(x, y, x + gridSize, y + gridSize);
                line(x + gridSize, y, x, y + gridSize);
                break;
            case CellType::SPACE:
                setfillcolor(WHITE);
                fillrectangle(x, y, x + gridSize, y + gridSize);
                break;
          
            default:
                setfillcolor(WHITE);
                fillrectangle(x, y, x + gridSize, y + gridSize);
                break;
            }
        }
    }
}

void Render::drawPlayer() //绘制玩家头像
{
    int gridSize = map.getGridSize();
    int x = player.getCol() * gridSize;
    int y = player.getRow() * gridSize;
    if (imgPlayer.getwidth() > 0) {
        putimage(x, y, &imgPlayer);
    }
    else {
        setfillcolor(RED);
        fillrectangle(x, y, x + gridSize, y + gridSize);
    }
}

void Render::drawHp() //绘制血条
{
    int hpY = windowHeight - 30;
    setfillcolor(RGB(200, 200, 200));
    fillrectangle(10, hpY, 10 + player.getMaxHp() * 30, hpY + 20);
    setfillcolor(RED);
    fillrectangle(10, hpY, 10 + player.getHp() * 30, hpY + 20);
    setlinecolor(BLACK);
    rectangle(10, hpY, 10 + player.getMaxHp() * 30, hpY + 20);

    TCHAR hpText[20];
    _stprintf_s(hpText, _T("HP: %d/%d"), player.getHp(), player.getMaxHp());
    settextcolor(BLACK);
    settextstyle(16, 0, _T("宋体"));
    outtextxy(10 + player.getMaxHp() * 30 + 10, hpY, hpText);
}

void Render::beginBatch()
{
    BeginBatchDraw();
}

void Render::endBatch()
{
    FlushBatchDraw();
}

void Render::drawGameOver(bool isWin) //游戏结束画面
{
    settextcolor(RED);
    settextstyle(24, 0, _T("宋体"));
    if (isWin) {
        outtextxy(50, 100, _T("游戏胜利！"));
    }
    else {
        outtextxy(50, 100, _T("游戏失败！"));
        outtextxy(20, 140, _T("血量耗尽"));
    }
    outtextxy(20, 180, _T("请关闭游戏"));
}

void Render::initImage() //初始化人物
{
    if (loadimage(&imgPlayer, _T("./player.jpg"), map.getGridSize(), map.getGridSize()) != 0) {
        MessageBox(NULL, _T("player.jpg不存在，用红色方块代替"), _T("提示"), MB_OK);
    }
}
void Render::clearScreen()//清屏
{
    cleardevice();
}