#include "grid.h"

Grid::Grid() {
    int rows = WINDOW_HEIGHT / CELL_SIZE;
    int cols = WINDOW_WIDTH / CELL_SIZE; 
    board.resize(rows, std::vector<Cell>(cols, Cell(false)));
    nextBoard.resize(rows, std::vector<Cell>(cols, Cell(false)));
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

int Grid::getNeighbors(int row, int col) {
    int neighbors = 0;
    for (int dr = -1; dr <= 1; dr++){
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow < board.size() && newCol < board[0].size()) {
                if (board[newRow][newCol].getIsAlive()) {
                    neighbors++;
                }
            }
        }
    }
    return neighbors;
}

void Grid::drawGrid(sf::RenderWindow& window) {
    for (int r = 0; r < board.size(); r++) {
        for (int c = 0; c < board[r].size(); c++) {
            drawCell(r, c, window);
        }
    } 
}

void Grid::conwayRule(int row, int col) {
    int neighbors = getNeighbors(row, col);
    bool currentlyAlive = board[row][col].getIsAlive();

    if (currentlyAlive) {
        nextBoard[row][col].setIsAlive(
            neighbors == 2 || neighbors == 3
        );
    }
    else {
        nextBoard[row][col].setIsAlive(neighbors == 3);
    }
}

void Grid::playGame() {
    for (int r = 0; r < board.size(); r++) {
        for (int c = 0; c < board[r].size(); c++) {
            switch (mode) {
                case CONWAY_GAME:
                    conwayRule(r, c);
                    break;
                
                default:
                    break;
            }
        }
    }
    board.swap(nextBoard);
}

void Grid::drawByMouse(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        cout << "mouse clicked!!!!" << endl;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        int col = mousePos.x / CELL_SIZE;
        int row = mousePos.y / CELL_SIZE;

        board[row][col].setIsAlive(true);
    }
}