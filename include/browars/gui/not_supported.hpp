#ifndef BROWARS_GUI_NOT_SUPPORTED
#define BROWARS_GUI_NOT_SUPPORTED

#include <SFML/Graphics.hpp>

namespace Browars
{
    class NotSupportedGUI : public sf::Drawable
    {
        sf::Text m_txt;

    public:
        NotSupportedGUI();
        
        inline virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const { window.draw(m_txt, states); }
    };
}

#endif