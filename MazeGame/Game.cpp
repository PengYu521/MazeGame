#include "Game.h"
#include <conio.h>
#include <windows.h>

Game::Game()
    : map(ROW, COL, GRID_SIZE, TRAP_COUNT)
    , player(14, 1, MAX_HP)
    , render(map, player, WINDOW_WIDTH, WINDOW_HEIGHT)
    , currentState(GameState::MENU)
    , selectedMap(1)
    , shouldMove(false)
    , keyReleased(true)
    , frameCounter(0) {}

void Game::init()//初始化游戏
{
    render.initWindow();
    map.loadMap("./map/map1.txt");
    map.generateTraps(player.getRow(), player.getCol()); // 初始化陷阱
    map.updateCell(player.getRow(), player.getCol(), CellType::PLAYER);
    map.updateExplored(player.getRow(), player.getCol());
}

void Game::update()//状态更新
{
    if (!shouldMove) return;

    auto [nextR, nextC] = player.getNextPos();
    switch ((CellType)map.getCell(nextR, nextC)) {
    case CellType::SPACE:
        map.updateCell(player.getRow(), player.getCol(), CellType::SPACE);
        player.move(nextR, nextC);
        map.updateCell(nextR, nextC, CellType::PLAYER);
        map.updateExplored(nextR, nextC);
        break;

    case CellType::TRAP:
        player.decreaseHp();
        map.updateCell(player.getRow(), player.getCol(), CellType::SPACE);
        player.move(nextR, nextC);
        map.updateCell(nextR, nextC, CellType::PLAYER);
        map.updateExplored(nextR, nextC);

        if (player.isDead()) {
            render.drawGameOver(false);
            render.endBatch();
            _getch();
            render.closeWindow();
            exit(0);
        }
        break;

    case CellType::DOOR:
        render.drawGameOver(true);
        render.endBatch();
        _getch();
        render.closeWindow();
        exit(0);
        break;

    default:
        break;
    }

    shouldMove = false;
    keyReleased = false;
}

void Game::run()//游戏运行
{
    while (true) {
        render.beginBatch();

        if (currentState == GameState::MENU) {
            handleMenuInput();
            render.drawMenu(selectedMap);
        }
        else {
            handleGameInput();
            update();

            //更新陷阱状态
            frameCounter++;
            map.updateTraps(frameCounter); 
            if (frameCounter % TRAP_SPAWN_INTERVAL == 0) {
                map.spawnTrap(frameCounter, player.getRow(), player.getCol());
            }

            render.clearScreen();
            render.drawMap();
            render.drawPlayer();
            render.drawHp();
        }

        render.endBatch();
        Sleep(50);
    }
}

void Game::handleMenuInput()//处理菜单输入
{
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        selectedMap = 1;
        Sleep(150);
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        selectedMap = 2;
        Sleep(150);
    }
    else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
        std::string mapPath = (selectedMap == 1) ? "./map/map1.txt" : "./map/map2.txt";
        map.loadMap(mapPath);
        map.generateTraps(player.getRow(), player.getCol());
        map.updateCell(player.getRow(), player.getCol(), CellType::PLAYER);
        map.updateExplored(player.getRow(), player.getCol());
        currentState = GameState::PLAYING;
        frameCounter = 0;
        Sleep(150);
    }
}

void Game::handleGameInput()//处理键盘输入
{
    if (!(GetAsyncKeyState('W') & 0x8000) &&
        !(GetAsyncKeyState('S') & 0x8000) &&
        !(GetAsyncKeyState('A') & 0x8000) &&
        !(GetAsyncKeyState('D') & 0x8000)) {
        keyReleased = true;
    }

    if (keyReleased) {
        if (GetAsyncKeyState('W') & 0x8000) {
            player.setDirection(Direction::UP);
            shouldMove = true;
        }
        else if (GetAsyncKeyState('S') & 0x8000) {
            player.setDirection(Direction::DOWN);
            shouldMove = true;
        }
        else if (GetAsyncKeyState('A') & 0x8000) {
            player.setDirection(Direction::LEFT);
            shouldMove = true;
        }
        else if (GetAsyncKeyState('D') & 0x8000) {
            player.setDirection(Direction::RIGHT);
            shouldMove = true;
        }
    }
}