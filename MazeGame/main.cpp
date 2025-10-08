#include "Game.h"
#include <windows.h>

int main()
{
    HWND hwndConsole = GetConsoleWindow();
    ShowWindow(hwndConsole, SW_SHOW);

    // 创建游戏对象
    Game game;
    // 初始化游戏
    game.init();
    // 启动游戏
    game.run();

    return 0;
}