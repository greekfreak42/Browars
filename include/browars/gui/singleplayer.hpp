#ifndef BROWARS_GUI_SINGLEPLAYER
#define BROWARS_GUI_SINGLEPLAYER

#include <SFML/Graphics.hpp>

#include <vector>

#include "planet.hpp"
#include "../space_bg.hpp"
#include "../gamestage.hpp"
#include "select_region.hpp"

namespace Browars
{
    class SingleplayerGUI : public sf::Drawable
    {
        std::map<std::string, sf::Texture> m_planet_textures;

        sf::Text m_txt_campaign;
        sf::Text m_txt_select_planet;

        std::vector<Planet> m_planets;

    public:
        SingleplayerGUI();

        void update(GameStage& game_stage, const sf::RenderWindow& window, SelectRegionGUI& select_region_gui);

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
}

#endif