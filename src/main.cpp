
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <algorithm>
#include <memory>
#include <vector>
#include "grid.h"
#include "macos_window.h"

int main() {
    const std::size_t displayCount = std::max<std::size_t>(1, getDisplayCount());
    std::vector<std::unique_ptr<sf::RenderWindow>> windows;
    windows.reserve(displayCount);

    for (std::size_t displayIndex = 0; displayIndex < displayCount; ++displayIndex) {
        const sf::Vector2u displaySize = getDisplaySize(displayIndex);
        auto window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(displaySize),
            "Cellular Automata",
            sf::Style::None);

        window->setFramerateLimit(15);
        configureWindowForDisplay(window->getNativeHandle(), displayIndex);
        window->setView(sf::View(sf::FloatRect(
            {0.f, 0.f},
            {static_cast<float>(WINDOW_WIDTH),
             static_cast<float>(WINDOW_HEIGHT)})));
        if (!ImGui::SFML::Init(*window)) {
            return 1;
        }
        windows.push_back(std::move(window));
    }

    sf::Clock clock;
    sf::Clock imguiClock;


    Grid grid(CONWAY_GAME);
    grid.randomize(0.10f);

    bool playing = true;
    bool painterMode = false;

    while (std::ranges::any_of(windows, [](const auto& window) {
               return window->isOpen();
           })) {
        if (consumePainterToggleShortcut()) {
            painterMode = !painterMode;
            playing = !painterMode;
            for (auto& window : windows) {
                setWindowPainterMode(window->getNativeHandle(), painterMode);
            }
        }

        for (auto& window : windows) {
            while (const auto event = window->pollEvent()) {
                ImGui::SFML::ProcessEvent(*window, *event);
                if (event->is<sf::Event::Closed>()) {
                    window->close();
                }

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Space) {
                        playing = !playing;
                    }
                }
            }
        }

        if (playing && clock.getElapsedTime().asMilliseconds() >= 200)
        {
            grid.playGame();
            clock.restart();
        }

        const sf::Time imguiDelta = imguiClock.restart();

        for (auto& window : windows) {
            if (!window->isOpen()) {
                continue;
            }

            window->clear(sf::Color::Black);
            grid.drawByMouse(*window);
            grid.drawGrid(*window);

            ImGui::SFML::SetCurrentWindow(*window);
            ImGui::SFML::Update(*window, imguiDelta);
            if (painterMode) {
                ImGui::Begin("Cellular Automata");
                ImGui::TextUnformatted("Painter mode");
                ImGui::TextUnformatted("Press Escape to return to wallpaper mode.");
                ImGui::End();
            }
            ImGui::SFML::Render(*window);
            window->display();
        }
    }

    for (auto& window : windows) {
        ImGui::SFML::Shutdown(*window);
    }

    return 0;
}
