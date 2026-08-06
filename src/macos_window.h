#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <cstddef>

std::size_t getDisplayCount();
sf::Vector2u getDisplaySize(std::size_t displayIndex);
sf::Vector2u configureWindowForDisplay(sf::WindowHandle handle,
                                       std::size_t displayIndex);
sf::Vector2f getNormalizedMousePosition(sf::WindowHandle handle);
bool consumePainterToggleShortcut();
void setWindowPainterMode(sf::WindowHandle handle, bool enabled);
