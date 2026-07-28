#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <vector>
#include <iostream>
using namespace std;


enum GameType {
    CONWAY_GAME,
    STARWARS
};

class Grid {
    private:
        vector<vector<Cell>> board;
        GameType mode;
    
    public:
        Grid();
        Grid(GameType mode);
        Cell& getCell(int row, int col);
        void setCell(int row, int col, Cell& cell);
        void drawCell(int row, int col, sf::RenderWindow& window);
        int getNeighbors(int row, int col);
        void drawGrid(sf::RenderWindow& window);
        void conwayRule(int row, int col);
        void playGame();
        void drawByMouse(sf::RenderWindow& window);
};




#endif