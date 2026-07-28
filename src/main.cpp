
#include <SFML/Graphics.hpp>
#include "grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Hello SFML");
    sf::Clock clock;


    Grid grid; 
    grid.getCell(10, 10).setIsAlive(true);
    grid.getCell(10, 11).setIsAlive(true);
    grid.getCell(11, 11).setIsAlive(true);

    grid.getCell(13, 12).setIsAlive(true);
    int count = grid.getNeighbors(10, 10);
    cout << "Count is: " << count << endl;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                cout << "mouse clicked!!!!" << endl;
            }
        }

        window.clear(sf::Color::Black);

        // draw stuff here
        if (clock.getElapsedTime().asMilliseconds() >= 200) {
            grid.playGame();
            clock.restart();
        }
        grid.drawGrid(window);
        window.display();
        
        
    }

    return 0;
}
