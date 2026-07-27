
#include <SFML/Graphics.hpp>
#include "grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Hello SFML");

    Grid grid; 
    grid.getCell(10, 10).setIsAlive(true);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // draw stuff here
       
        grid.drawCell(10, 10, window);
        
        
        window.display();
    }

    return 0;
}
