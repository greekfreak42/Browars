#include "browars/game_loop.hpp"
#include "browars/gui/gui.hpp"

extern bool fullscreen;
extern unsigned width, height;
extern std::map<sf::Keyboard::Key, bool> pressed_keys;
extern std::map<unsigned, bool> pressed_controller_buttons;
extern std::map<sf::Joystick::Axis, float> controller_axis_states;

static void toggle_fullscreen(sf::RenderWindow& window)
{
    if (fullscreen)
    {
        fullscreen = false;
        window.create(sf::VideoMode(width, height), "Browars", sf::Style::Close);
    } else
    {
        fullscreen = true;
        window.create(sf::VideoMode::getFullscreenModes()[0], "Browars", sf::Style::Fullscreen);
    }
}

void Browars::handle_events(sf::RenderWindow& window)
{
    for (sf::Event e; window.pollEvent(e);)
    {
        switch (e.type)
        {
            case sf::Event::Closed:
                window.close();
                return;
            
            case sf::Event::JoystickButtonPressed:
                if (e.joystickButton.button == 10) { toggle_fullscreen(window); }
                pressed_controller_buttons[e.joystickButton.button] = true;
                break;
            
            case sf::Event::JoystickButtonReleased:
                pressed_controller_buttons[e.joystickButton.button] = false;
                break;

            case sf::Event::JoystickMoved:
                controller_axis_states[e.joystickMove.axis] = e.joystickMove.position;
                break;

            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::F11) { toggle_fullscreen(window); }
                pressed_keys[e.key.code] = true;
                break;

            case sf::Event::KeyReleased:
                pressed_keys[e.key.code] = false;
                break;
        
            default: break;
        }
    }
}

void Browars::update(const float dt, GUI& gui, sf::RenderWindow& window)
{
    gui.update(dt, window);
}

void Browars::draw(sf::RenderWindow& window, const GUI& gui)
{
    window.clear();
    window.draw(gui);
    window.display();
}