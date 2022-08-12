#ifndef BROWRS_GUI_SELECT_REGION
#define BROWRS_GUI_SELECT_REGION

#include <SFML/Graphics.hpp>

#include "browars/init.hpp"

namespace Browars
{
    class SelectRegionGUI : public sf::Drawable
    {
        sf::Text m_txt_campaign;
        sf::Text m_txt_select_region;

        sf::Texture m_map_texture;
        sf::Sprite m_map;

    public:
        SelectRegionGUI();

        void init_map(const std::string& planet_name);

        void update(const sf::RenderWindow& window, GameStage& game_stage);
        
        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
}

#endif