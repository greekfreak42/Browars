#include "browars/gui/gui.hpp"

#include <map>
#include <vector>
#include <random>

#include "browars/init.hpp"

extern std::mt19937 randint;

extern unsigned width;
extern unsigned height;

extern std::map<sf::Keyboard::Key, bool> pressed_keys;
extern std::map<unsigned, bool> pressed_controller_buttons;
extern std::map<sf::Joystick::Axis, float> controller_axis_states;

Browars::GUI::GUI() : m_stage(GameStage::INTRO)
{
    m_gui_main_menu.buttons[0].set_action([](GameStage& stage){ stage = GameStage::SINGLEPLAYER; });
    m_gui_main_menu.buttons[1].set_action([](GameStage& stage){ stage = GameStage::NOT_SUPPORTED; });
    m_gui_main_menu.buttons[2].set_action([](GameStage& stage){ stage = GameStage::NOT_SUPPORTED; });

    init_space_bg(m_bg.star_texture, m_bg.img, m_bg.stars);
}

void Browars::GUI::update(const float dt, const sf::RenderWindow& window)
{
    sf::Mouse::setPosition(sf::Mouse::getPosition(window) + sf::Vector2i(
        controller_axis_states[sf::Joystick::Axis::X] * dt * 8,
        controller_axis_states[sf::Joystick::Axis::Y] * dt * 8
    ));

    switch (m_stage)
    {
        case GameStage::INTRO:
            if (m_gui_intro.update(dt)) { m_stage = GameStage::MAIN_MENU; }
            return;

        case GameStage::MAIN_MENU:
            m_gui_main_menu.update(dt, window, m_stage);
            return;
        
        case GameStage::SINGLEPLAYER:
            if (pressed_keys[sf::Keyboard::Escape] || pressed_controller_buttons[1])
            {
                pressed_keys[sf::Keyboard::Escape] = false;
                pressed_controller_buttons[1] = false;
                m_stage = GameStage::MAIN_MENU;
                return;
            }

            m_gui_singleplayer.update(m_stage, window, m_gui_select_region);

            return;

        case GameStage::NOT_SUPPORTED:
            if (pressed_keys[sf::Keyboard::Escape] || pressed_controller_buttons[1])
            {
                pressed_controller_buttons[1] = false;
                m_stage = GameStage::MAIN_MENU;
            }
            return;
        
        case GameStage::SELECT_REGION:
            if (pressed_keys[sf::Keyboard::Escape] || pressed_controller_buttons[1])
            {
                pressed_keys[sf::Keyboard::Escape] = false;
                pressed_controller_buttons[1] = false;
                m_stage = GameStage::SINGLEPLAYER;
            }
            m_gui_select_region.update(window, m_stage);
            return;

        case GameStage::SELECT_CHARACTER:
            if (pressed_keys[sf::Keyboard::Escape] || pressed_controller_buttons[1])
            {
                pressed_keys[sf::Keyboard::Escape] = false;
                pressed_controller_buttons[1] = false;
                m_stage = GameStage::SELECT_REGION;
            }
            return;
    
        default: throw std::runtime_error("Invalid game stage: " + std::to_string(m_stage));
    }
}

void Browars::GUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_bg, states);

    switch (m_stage)
    {
        case GameStage::INTRO:
            window.draw(m_gui_intro, states);
            return;

        case GameStage::MAIN_MENU:
            window.draw(m_gui_main_menu, states);
            return;
        
        case GameStage::SINGLEPLAYER:
            window.draw(m_gui_singleplayer, states);
            return;

        case GameStage::NOT_SUPPORTED:
            window.draw(m_gui_not_supported, states);
            return;
        
        case GameStage::SELECT_REGION:
            window.draw(m_gui_select_region, states);
            return;
        
        case GameStage::SELECT_CHARACTER:
            window.draw(m_gui_select_character, states);
            return;
    
        default: throw std::runtime_error("Invalid game stage: " + std::to_string(m_stage));;
    }
}