#include "grid.h"
#include "macos_window.h"
#include <random>

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
            if (newRow >= 0 && newCol >= 0 &&
                newRow < static_cast<int>(board.size()) &&
                newCol < static_cast<int>(board[0].size())) {
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

// Live cells survive with 2 or 3, dead cells become alive with exactly 2 neighbors
void Grid::highLifeRule(int row, int col) {
    int neighbors = getNeighbors(row, col);
    bool currentlyAlive = board[row][col].getIsAlive();

    if (currentlyAlive) {
        nextBoard[row][col].setIsAlive(
            neighbors == 2 || neighbors == 3
        );
    }
    else {
        nextBoard[row][col].setIsAlive(neighbors == 3 || neighbors == 6);
    } 
}

void Grid::playGame() {
    for (int r = 0; r < board.size(); r++) {
        for (int c = 0; c < board[r].size(); c++) {
            switch (mode) {
                case CONWAY_GAME:
                    conwayRule(r, c);
                    break;
                case HIGH_LIFE:
                    highLifeRule(r, c);
                    break;
                
                default:
                    break;
            }
        }
    }
    board.swap(nextBoard);
}

void Grid::randomize(float aliveProbability)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::bernoulli_distribution isAlive(aliveProbability);

    for (auto& row : board) {
        for (auto& cell : row) {
            cell.setIsAlive(isAlive(generator));
        }
    }
}

void Grid::drawByMouse(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        const sf::Vector2f normalizedMouse =
            getNormalizedMousePosition(window.getNativeHandle());
        if (normalizedMouse.x < 0.f || normalizedMouse.y < 0.f) {
            return;
        }

        const sf::Vector2f mousePos = {
            normalizedMouse.x * static_cast<float>(WINDOW_WIDTH),
            normalizedMouse.y * static_cast<float>(WINDOW_HEIGHT)};

        int col = static_cast<int>(mousePos.x / CELL_SIZE);
        int row = static_cast<int>(mousePos.y / CELL_SIZE);

        if (row >= 0 &&
            col >= 0 &&
            row < static_cast<int>(board.size()) &&
            col < static_cast<int>(board[row].size()))
        {
            board[row][col].setIsAlive(true);
        }
    }
}
