#ifndef MAP_H
#define MAP_H

#include "Common.h"
#include <vector>
#include <string>

struct Trap 
{
    int r;
    int c;
    int spawnFrame;
};

class Map //地图类
{
public:
    Map(int rows, int cols, int gridSize, int trapCount);
    bool loadMap(const std::string& filename);
    void generateTraps(int playerStartR, int playerStartC); 
    void spawnTrap(int currentFrame, int playerR, int playerC); 
    void updateTraps(int currentFrame); 

    void updateExplored(int playerR, int playerC);
    bool isExplored(int r, int c) const;
    int getCell(int r, int c) const;
    void updateCell(int r, int c, CellType type);
    int getRows() const;
    int getCols() const;
    int getGridSize() const;

private:
    int rows;
    int cols;
    int gridSize;
    int trapCount; 
    std::vector<std::vector<int>> cellData;
    std::vector<std::vector<bool>> explored;
    std::vector<Trap> activeTraps; 
};

#endif