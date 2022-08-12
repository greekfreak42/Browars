#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

#include <random>
#include <map>
#include <iostream>

#include "browars/game_loop.hpp"
#include "browars/gui/gui.hpp"
#include "browars/init.hpp"

std::mt19937 randint;

bool fullscreen = true;
unsigned width  = 1920;
unsigned height = 1080;

extern const std::map<std::string, sf::Font> fonts = Browars::load_fonts();

std::map<sf::Keyboard::Key, bool> pressed_keys;
std::map<unsigned, bool> pressed_controller_buttons;
std::map<sf::Joystick::Axis, float> controller_axis_states;

int main()
{
    randint.seed(time(nullptr));

    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Browars", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    Browars::GUI gui;

    sf::Clock clock;

    while (window.isOpen())
    {
        const float delta = clock.restart().asSeconds();

        Browars::handle_events(window);

        Browars::update(delta, gui, window);

        Browars::draw(window, gui);
    }
}