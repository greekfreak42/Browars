#include "browars/gui/not_supported.hpp"

extern unsigned width, height;

extern const std::map<std::string, sf::Font> fonts;

Browars::NotSupportedGUI::NotSupportedGUI() : m_txt("This feature is not supported yet", fonts.at("AquireBold.ttf"), 54)
{
    m_txt.setPosition(width / 2.0 - m_txt.getLocalBounds().width / 2, height / 2.0 - m_txt.getLocalBounds().height);
    m_txt.setFillColor(sf::Color::Red);
}

