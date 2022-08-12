#ifndef BROWARS_GAME_LOOP
#define BROWARS_GAME_LOOP

#include <SFML/Graphics.hpp>

#include "gui/gui.hpp"

namespace Browars
{
    void handle_events(sf::RenderWindow& window);

    void update(const float dt, GUI& gui, sf::RenderWindow& window);

    void draw(sf::RenderWindow& window, const GUI& gui);
}

#endif