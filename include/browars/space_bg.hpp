#ifndef BROWARS_SPACE_BG
#define BROWARS_SPACE_BG

#include <SFML/Graphics.hpp>

namespace Browars
{
    struct SpaceBG : public sf::Drawable
    {
        sf::Texture star_texture, img;
        std::vector<sf::Sprite> stars;

        inline virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const
        {
            window.draw(sf::Sprite(img), states);
            for (const sf::Sprite& star : stars) { window.draw(star, states); }
        }
    };
}

#endif