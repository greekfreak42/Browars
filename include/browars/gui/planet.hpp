#ifndef BROWARS_GUI_PLANET
#define BROWARS_GUI_PLANET

#include <SFML/Graphics.hpp>

namespace Browars
{
    struct Planet
    {
        sf::Sprite shape;
        sf::Text txt;

        inline Planet(const sf::Sprite& sprite, const sf::Text& text) : shape(sprite), txt(text) {}
    };
}

#endif