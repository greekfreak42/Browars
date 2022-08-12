#include "browars/button.hpp"

#include <map>

extern std::map<unsigned, bool> pressed_controller_buttons;

void Browars::Button::update(const float dt, const sf::RenderWindow& window, GameStage& game_stage)
{
    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    bool is_hovered = mouse_pos.x > m_pos.x
        && mouse_pos.x < m_pos.x + m_size.x
        && mouse_pos.y > m_pos.y
        && mouse_pos.y < m_pos.y + m_size.y;

    if (is_hovered)
    {
        m_anim_time += dt;
    } else 
    {
        m_anim_time -= dt;
    } 

    if (m_anim_time < .0f)
    {
        m_anim_time = .0f;
    } else if (m_anim_time > 1.0f)
    {
        m_anim_time = 1.0f;
    }

    if (is_hovered && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || pressed_controller_buttons[0])) { m_on_click(game_stage); }
}

void Browars::Button::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    sf::RectangleShape shape(m_size);
    shape.setPosition(m_pos);

    shape.setFillColor(sf::Color(m_anim_time * 0xFF, 0, (1.0 - m_anim_time) * 0xFF));

    window.draw(shape);
    window.draw(m_txt);
}