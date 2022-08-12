#include "browars/gui/singleplayer.hpp"

#include "browars/init.hpp"

#include <cmath>

extern unsigned width, height;

extern const std::map<std::string, sf::Font> fonts;

static const sf::Font& font = fonts.at("Aquire.ttf");

Browars::SingleplayerGUI::SingleplayerGUI()
: m_planet_textures(load_planet_textures()), m_txt_campaign("Campaign", font, 50), m_txt_select_planet("Select planet", font, 70),
  m_planets(load_planets(font, m_planet_textures))
{
    m_txt_campaign.setFillColor(sf::Color::Red);
    m_txt_select_planet.setPosition(width / 2 - m_txt_select_planet.getLocalBounds().width / 2, height * 0.1);
}

void Browars::SingleplayerGUI::update(GameStage& game_stage, const sf::RenderWindow& window, SelectRegionGUI& select_region_gui)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { return; }
    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    for (const Planet& planet : m_planets)
    {
        const sf::FloatRect planet_bounds = planet.shape.getGlobalBounds();

        if (
            mouse_pos.x > planet_bounds.left && 
            mouse_pos.x < planet_bounds.left + planet_bounds.width &&
            mouse_pos.y > planet_bounds.top &&
            mouse_pos.y < planet_bounds.top + planet_bounds.height
        )
        {
            game_stage = GameStage::SELECT_REGION;

            std::string planet_name = planet.txt.getString();
            planet_name[0] = tolower(planet_name[0]);
            select_region_gui.init_map(planet_name);
            
            return;
        }
    }
}

void Browars::SingleplayerGUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_txt_campaign, states);
    window.draw(m_txt_select_planet, states);
    
    for (const Planet& planet : m_planets)
    {
        window.draw(planet.shape, states);
        window.draw(planet.txt, states);
    }
}