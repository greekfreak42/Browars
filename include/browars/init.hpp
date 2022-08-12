#ifndef BROWARS_INIT
#define BROWARS_INIT

#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

#include <map>
#include <vector>
#include <string>

#include "button.hpp"
#include "gui/planet.hpp"

namespace Browars
{
    void init_space_bg(sf::Texture& star_texture, sf::Texture& bg, std::vector<sf::Sprite>& stars);

    sfe::Movie load_intro_movie();
    std::map<std::string, sf::Font> load_fonts();
    std::map<std::string, sf::Texture> load_space_textures();

    std::map<std::string, sf::Texture> load_planet_textures();
    std::vector<Planet> load_planets(const sf::Font& font, const std::map<std::string, sf::Texture>& planet_textures);

    sf::Texture load_map_texture(const std::string& planet_name);
}

#endif