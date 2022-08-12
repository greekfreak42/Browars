#include "browars/gui/intro.hpp"

#include "browars/init.hpp"

#include <map>

extern unsigned width, height;
extern std::map<sf::Keyboard::Key, bool> pressed_keys;
extern std::map<unsigned, bool> pressed_controller_buttons;

bool Browars::IntroGUI::update(const float dt)
{
    if (pressed_controller_buttons[1] || pressed_controller_buttons[0])
    {
        pressed_controller_buttons[1] = false;
        pressed_controller_buttons[0] = false;
        return true;
    }

    if (pressed_keys[sf::Keyboard::Space]) { return true; }

    m_movie.update();

    m_rem_duration -= dt;

    return m_rem_duration <= .0f;
}

void Browars::IntroGUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_movie);
}