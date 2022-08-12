#include "browars/gui/select_region.hpp"

#include <map>
#include <array>

extern unsigned width, height;

extern const std::map<std::string, sf::Font> fonts;

Browars::SelectRegionGUI::SelectRegionGUI() : m_txt_campaign("Campaign", fonts.at("Aquire.ttf"), 50), m_txt_select_region("Select region", fonts.at("Aquire.ttf"), 70)
{
    m_txt_campaign.setFillColor(sf::Color::Red);

    m_txt_select_region.setPosition(width / 2 - m_txt_select_region.getLocalBounds().width / 2, height * 0.1);
}

void Browars::SelectRegionGUI::init_map(const std::string& planet_name)
{
    m_map_texture = load_map_texture(planet_name);

    m_map = sf::Sprite(m_map_texture);
    m_map.setPosition(100, height - 760);
}

void Browars::SelectRegionGUI::update(const sf::RenderWindow& window, GameStage& game_stage)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { return; }

    const sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    const sf::FloatRect map_bounds = m_map.getGlobalBounds();

    const sf::Vector2i mouse_position_relative_to_map = mouse_position - sf::Vector2i(map_bounds.left, map_bounds.top);

    if (mouse_position_relative_to_map.x < 0
        || mouse_position_relative_to_map.y < 0
        || mouse_position_relative_to_map.x > map_bounds.width
        || mouse_position_relative_to_map.y > map_bounds.height
    )
    {
        return;
    }

    constexpr unsigned n_fields_per_row = 10, n_fields_per_column = 3;
    const unsigned field_width = map_bounds.width / n_fields_per_row;
    const unsigned field_height = map_bounds.height / n_fields_per_column;

    const sf::Vector2u selected_field(mouse_position_relative_to_map.x / field_width, mouse_position_relative_to_map.y / field_height);

    printf("%u, %u\n", selected_field.x, selected_field.y);

    game_stage = GameStage::SELECT_CHARACTER;
}

void Browars::SelectRegionGUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_map, states);
    window.draw(m_txt_campaign, states);
    window.draw(m_txt_select_region, states);
}