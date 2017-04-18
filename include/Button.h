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

#include "Widget.h"
#include "Panel.h"
#include "Unicode.h"

#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <functional>


namespace sfge
{


    using sf::Texture;
    using sf::Font;
    using sf::Color;


    /////////////////////////////////////////////////////////////////////
    /// Button - class of button
    /////////////////////////////////////////////////////////////////////
    class Button : public iWidget
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// EventType - enumeration of types of events
        /////////////////////////////////////////////////////////////////////
        enum EventType : unsigned
        {
            PRESSED,    // button was pressed
            FOCUSED,    // button was focused
            RELEASED    // button was released
        };

        /////////////////////////////////////////////////////////////////////
        /// Default constructor to create button
        /////////////////////////////////////////////////////////////////////
        Button ();

        /////////////////////////////////////////////////////////////////////
        /// attachReaction - attach function to handle some event
        /// 
        /// @param func - function wich handle this event
        /// @param e - event description
        /////////////////////////////////////////////////////////////////////
        void attachReaction (const std::function<void ()> func, const EventType e);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to button view
        /// 
        /// @param tex - pointer to texture
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::shared_ptr<const Texture> tex, const EventType e = RELEASED);

        /////////////////////////////////////////////////////////////////////
        /// setText - set text to draw on the button
        /// 
        /// @param string - text on button
        /////////////////////////////////////////////////////////////////////
        void setText (UString string);

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setFont (std::shared_ptr<const Font> font);

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize set size of text
        ///
        /// @parameter size - size of characters in pixels
        /////////////////////////////////////////////////////////////////////
        void setCharacterSize (unsigned size);

        /////////////////////////////////////////////////////////////////////
        /// setTextColor - set color of text in widget
        /// 
        /// @param color - new color
        /////////////////////////////////////////////////////////////////////
        void setTextColor (Color color);

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void draw (sf::RenderTarget&) const override;

        virtual bool check_key (const sf::Event::KeyEvent&, const bool) override;
        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool) override;
        virtual bool check_mouse (const int x, const int y) override;

        void set_view (const unsigned type);

        std::function<void ()> m_pressed;
        std::function<void ()> m_released;

        std::shared_ptr<const sf::Texture> m_pressed_view;
        std::shared_ptr<const sf::Texture> m_focused_view;
        std::shared_ptr<const sf::Texture> m_released_view;

        Panel m_view;
        sf::Text m_text;
    };


}