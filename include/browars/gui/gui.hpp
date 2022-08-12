#ifndef SPACESHIPS_GUI
#define SPACESHIPS_GUI

#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

#include <array>
#include <vector>

#include "../gamestage.hpp"
#include "../button.hpp"
#include "../space_bg.hpp"
#include "intro.hpp"
#include "main_menu.hpp"
#include "not_supported.hpp"
#include "singleplayer.hpp"
#include "select_region.hpp"
#include "select_character.hpp"

namespace Browars
{
    class GUI : public sf::Drawable
    {        
        GameStage m_stage;

        SpaceBG m_bg;

        IntroGUI m_gui_intro;
        MainMenuGUI m_gui_main_menu;
        NotSupportedGUI m_gui_not_supported;

        SingleplayerGUI m_gui_singleplayer;

        SelectRegionGUI m_gui_select_region;

        SelectCharacterGUI m_gui_select_character;

    public:
        GUI();

        void update(const float dt, const sf::RenderWindow& window);

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
}

#endif