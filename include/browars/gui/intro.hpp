#ifndef BROWARS_GUI_INTRO
#define BROWARS_GUI_INTRO

#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

#include "../init.hpp"

namespace Browars
{
    class IntroGUI : public sf::Drawable
    {
        sfe::Movie m_movie;
        float m_rem_duration;

        public:
            inline IntroGUI() : m_movie(load_intro_movie()), m_rem_duration(m_movie.getDuration().asSeconds()) { m_movie.play(); }

            bool update(const float dt);
            
            virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    };
}

#endif