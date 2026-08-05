
#include <SFML/Graphics.hpp>
#include "grid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_HEIGHT, WINDOW_WIDTH}), "Hello SFML");
    sf::Clock clock;


    Grid grid(HIGH_LIFE); 
    // grid.getCell(10, 10).setIsAlive(true);
    // grid.getCell(10, 11).setIsAlive(true);
    // grid.getCell(11, 11).setIsAlive(true);

    grid.getCell(13, 12).setIsAlive(true);
    int count = grid.getNeighbors(10, 10);
    cout << "Count is: " << count << endl;

    bool playing = false;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    playing = !playing;
                }
            }
        }

        window.clear(sf::Color::Black);

        grid.drawByMouse(window);

        if (playing && clock.getElapsedTime().asMilliseconds() >= 200)
        {
            grid.playGame();
            clock.restart();
        }

        grid.drawGrid(window);
        window.display();
    }

    return 0;
}
