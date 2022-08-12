#ifndef BROWARS_BUTTON
#define BROWARS_BUTTON

#include <SFML/Graphics.hpp>

#include "gamestage.hpp"

namespace Browars
{

    class Button : public sf::Drawable
    {
        float m_anim_time = .0f; // Time in seconds representing the animation offset
        bool is_hovered = false;
        sf::Vector2f m_pos;
        sf::Vector2f m_size;
        sf::Text m_txt;
        void (*m_on_click)(GameStage& game_stage) = nullptr;

    public:

        inline Button() = default;

        inline Button(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Text& text)
        : m_pos(pos), m_size(size), m_txt(text) {}

        void update(const float dt, const sf::RenderWindow& window, GameStage& game_stage);

        inline void set_action(void (*on_click)(GameStage&)) { m_on_click = on_click; }

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
    };
}

#endif