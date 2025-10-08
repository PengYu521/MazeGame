#include "Map.h"
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

Map::Map(int rows, int cols, int gridSize, int trapCount)
    : rows(rows), cols(cols), gridSize(gridSize), trapCount(trapCount) {
    cellData.resize(rows, std::vector<int>((int)cols, (int)CellType::SPACE));
    explored.resize(rows, std::vector<bool>(cols, false));
    srand((unsigned int)time(nullptr));
}

bool Map::loadMap(const std::string& filename)//加载地图
{
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        printf("地图文件加载失败:%s\n", filename.c_str());
        return false;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            fin >> cellData[r][c];
        }
    }
    fin.close();
    explored.assign(rows, std::vector<bool>(cols, false));
    activeTraps.clear(); // 加载新地图时清空陷阱
    return true;
}

// 初始化陷阱
void Map::generateTraps(int playerStartR, int playerStartC)
{
    activeTraps.clear();
 
    for (int i = 0; i < trapCount; i++) {
        spawnTrap(0, playerStartR, playerStartC); 
    }
}


void Map::spawnTrap(int currentFrame, int playerR, int playerC)
{
    if (activeTraps.size() >= (size_t)trapCount) return; 

    while (true) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (cellData[r][c] == (int)CellType::SPACE &&
            !(r == playerR && c == playerC)) {

            cellData[r][c] = (int)CellType::TRAP;
            activeTraps.push_back({ r, c, currentFrame });
            break;
        }
    }
}

// 更新陷阱状态
void Map::updateTraps(int currentFrame)
{
    std::vector<Trap> remainingTraps;
    for (const auto& trap : activeTraps)
    {
        if (currentFrame - trap.spawnFrame > TRAP_LIFETIME) {
            cellData[trap.r][trap.c] = (int)CellType::SPACE;
        }
        else {
            remainingTraps.push_back(trap);
        }
    }
    activeTraps = remainingTraps;
}

void Map::updateExplored(int playerR, int playerC)
{
    for (int dr = -2; dr <= 2; dr++) {
        for (int dc = -2; dc <= 2; dc++) {
            int r = playerR + dr;
            int c = playerC + dc;
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                explored[r][c] = true;
            }
        }
    }
}

bool Map::isExplored(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return explored[r][c];
    }
    return false;
}

int Map::getCell(int r, int c) const
{
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return cellData[r][c];
    }
    return (int)CellType::WALL;
}

void Map::updateCell(int r, int c, CellType type)
{
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        cellData[r][c] = (int)type;
    }
}

int Map::getRows() const { return rows; }
int Map::getCols() const { return cols; }
int Map::getGridSize() const { return gridSize; }