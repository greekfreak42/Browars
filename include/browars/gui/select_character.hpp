#ifndef BROWARS_SELECT_CHARACTER_GUI
#define BROWARS_SELECT_CHARACTER_GUI

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

namespace Browars
{
    struct Character
    {
        sf::Text name_as_text;
        //sf::RectangleShape figure;
        const sf::Texture *texture_ptr;
        sf::Sprite sprite;

        Character(const sf::Text& name_text, const sf::Texture *texture, const sf::Sprite& sprite) : name_as_text(name_text), texture_ptr(texture), sprite(sprite) {}

        inline ~Character()
        {
            delete texture_ptr;
        }
    };

    class SelectCharacterGUI : public sf::Drawable
    {
        sf::Text m_txt_campaign, m_txt_select_character, m_txt_basic_characters, m_txt_heroes;

        std::vector<Character> m_basic_characters, m_heroes;

    public:
        SelectCharacterGUI();

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
}

#endif