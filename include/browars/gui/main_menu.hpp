#ifndef BROWARS_GUI_MAIN_MENU
#define BROWARS_GUI_MAIN_MENU

#include <SFML/Graphics.hpp>

#include "../button.hpp"

namespace Browars
{
    class MainMenuGUI : public sf::Drawable
    {
    public:
        std::array<Button, 3> buttons;

    public:
        MainMenuGUI();

        void update(const float dt, const sf::RenderWindow& window, GameStage& game_stage);
        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
            
    };
}

#endif