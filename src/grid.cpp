#include "grid.h"

Grid::Grid() {
    int rows = WINDOW_HEIGHT / CELL_SIZE;
    int cols = WINDOW_WIDTH / CELL_SIZE; 
    board.resize(rows, std::vector<Cell>(cols, Cell(false)));
    mode = CONWAY_GAME;
}

Grid::Grid(GameType mode) : Grid() {
    this->mode = mode;
}

void Grid::setCell(int row, int col, Cell& cell) {
    board[row][col] = cell;
}

Cell& Grid::getCell(int row, int col) {
    return board[row][col];
}

void Grid::drawCell(int row, int col, sf::RenderWindow& window) {

    if (row >= board.size() || row < 0 || col >= board[row].size() || col < 0) {
        throw out_of_range("Invalid row or column");
    }

    float x = col * CELL_SIZE;
    float y = row * CELL_SIZE;
    
    board.at(row).at(col).drawCell(window, x, y);
    
}

void Grid::drawGrid(sf::RenderWindow& window) {
    for (auto section : board) {
        for (auto cell : section) {
            
        }
    }
}