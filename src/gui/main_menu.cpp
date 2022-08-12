#include "browars/gui/main_menu.hpp"

#include "browars/init.hpp"

extern unsigned width, height;

extern const std::map<std::string, sf::Font> fonts;

Browars::MainMenuGUI::MainMenuGUI()
{
    const sf::Font& font = fonts.at("Aquire.ttf");

    const sf::Vector2f size(800, 150);

    sf::RectangleShape shape1(size);
    shape1.setPosition(width / 2.0 - size.x / 2.0, height / 2.0 - 200 - size.y / 2.0);

    sf::RectangleShape shape2(size);
    shape2.setPosition(width / 2.0 - size.x / 2.0, height / 2.0 - size.y / 2.0);

    sf::RectangleShape shape3(size);
    shape3.setPosition(width / 2.0 - size.x / 2.0, height / 2.0 + 200 - size.y / 2.0);

    sf::Text txt1("Singleplayer", font, 54);
    txt1.setPosition(width / 2.0 - txt1.getLocalBounds().width / 2.0, height / 2.0 - 200 - txt1.getLocalBounds().height / 2.0 - 10);

    sf::Text txt2("Multiplayer", font, 54);
    txt2.setPosition(width / 2.0 - txt2.getLocalBounds().width / 2.0, height / 2.0 - txt2.getLocalBounds().height / 2.0 - 10);

    sf::Text txt3("Settings", font, 54);
    txt3.setPosition(width / 2.0 - txt3.getLocalBounds().width / 2.0, height / 2.0 + 200 - txt3.getLocalBounds().height / 2.0 - 10);

    buttons = {
        Button(shape1.getPosition(), shape1.getSize(), txt1),
        Button(shape2.getPosition(), shape2.getSize(), txt2),
        Button(shape3.getPosition(), shape3.getSize(), txt3)
    };
}

void Browars::MainMenuGUI::update(const float dt, const sf::RenderWindow& window, GameStage& game_stage)
{
    for (Button& button : buttons) { button.update(dt, window, game_stage); }
}

void Browars::MainMenuGUI::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    for (const Button& button : buttons) { window.draw(button, states); }
}