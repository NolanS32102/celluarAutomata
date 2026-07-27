#ifndef CELL_H
#define CELL_H


#include <SFML/Graphics.hpp>
#include "constants.h"

class Cell {
    private:
        bool isAlive;
    
    public:
        Cell() : isAlive(true) {};
        Cell(bool status) : isAlive(status){}
        bool getIsALive() { return isAlive; }
        void setIsAlive(bool isALive) { this->isAlive = isALive; }
        void drawCell(sf::RenderWindow& window, auto xPos, auto yPos) {
            sf::Color color = isAlive ? sf::Color::Yellow : sf::Color::Black;
            sf::RectangleShape cell({CELL_SIZE, CELL_SIZE});
            cell.setFillColor(color);
            cell.setPosition({xPos, yPos});
            window.draw(cell);
        }
};

#endif