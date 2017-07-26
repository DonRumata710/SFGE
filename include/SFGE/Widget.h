/////////////////////////////////////////////////////////////////////
//
// SFGE - Simple and Fast Game Engine
//
// Copyright (c) 2016-2017 DonRumata710 
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// 
/////////////////////////////////////////////////////////////////////


#pragma once


#include "Config.h"
#include "GuiElement.h"
#include "Frame.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include <functional>
#include <memory>


namespace sfge
{


    using sf::Texture;
    using sf::Color;
    using sf::Font;
    
    class GUIManager;


    /////////////////////////////////////////////////////////////////////
    /// iWidget - interface for common widgets interface.
    ///
    /// This abstract class should be inherited to realize custom widget.
    /////////////////////////////////////////////////////////////////////
    class iWidget : public iGuiElement
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// View - enumeration of views of the widget
        /////////////////////////////////////////////////////////////////////
        enum class View : uint32_t
        {
            RELEASED,
            HOVER,
            PRESSED
        };

        /////////////////////////////////////////////////////////////////////
        /// Default constructor - do nothing
        /////////////////////////////////////////////////////////////////////
        iWidget () = default;

        /////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////
        virtual ~iWidget () = default;

        /////////////////////////////////////////////////////////////////////
        /// isVisible - check the visibility of widget
        ///
        /// @return True if widget is visible, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isVisible () const;

        /////////////////////////////////////////////////////////////////////
        /// isVisible - check isthe widget static
        /// 
        /// Static widget can't get keyboard events.
        ///
        /// @return True if widget is static, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isStatic () const;

        /////////////////////////////////////////////////////////////////////
        /// isEnabled - check is the widget enabled
        /// 
        /// Widget is disable to handle events if it is displaying some
        /// animation of previous events.
        ///
        /// @return True if widget is enabled, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isEnabled () const;

        /////////////////////////////////////////////////////////////////////
        /// setVisible - set visibility of widget
        /// 
        /// @param flag - describe should widget be visible or not
        /////////////////////////////////////////////////////////////////////
        void setVisible (bool flag);

        /////////////////////////////////////////////////////////////////////
        /// setStatic - set widget static or dinamic
        ///
        /// @param flag - describe status of widget
        /////////////////////////////////////////////////////////////////////
        void setStatic (bool flag);

        /////////////////////////////////////////////////////////////////////
        /// setEnabled - set widget enabled or disabled
        ///
        /// @param flag - describe is widget enabled
        /////////////////////////////////////////////////////////////////////
        void setEnabled (bool flag);

        /////////////////////////////////////////////////////////////////////
        /// setView - attach texture to widget view
        /// 
        /// @param tex - pointer to texture
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        virtual void setView (const std::shared_ptr<const Texture> tex, const View view = View::RELEASED) {}

        /////////////////////////////////////////////////////////////////////
        /// setView - attach texture to widget view
        /// 
        /// @param tex - name of texture loaded to resource manager
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        virtual void setView (const std::string& tex, const View view = View::RELEASED) {}

        /////////////////////////////////////////////////////////////////////
        /// setView - set color to widget view
        /// 
        /// @param color - color of button
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        virtual void setView (const Color& color, const View view = View::RELEASED) {}

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize set size of text
        ///
        /// @parameter size - size of characters in pixels
        /////////////////////////////////////////////////////////////////////
        virtual void setCharacterSize (const unsigned size) {}

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - pointer to font
        /////////////////////////////////////////////////////////////////////
        virtual void setFont (const std::shared_ptr<const Font> font) {}

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - name of font
        /////////////////////////////////////////////////////////////////////
        virtual void setFont (const std::string& font) {}

    private:
        bool m_visible = true;
        bool m_static = false;
        bool m_enabled = true;
    };


    typedef std::shared_ptr<iWidget> pWidget;

    
}