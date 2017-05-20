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
#include "RenderRect.h"
#include "Unicode.h"

#include <SFML/Graphics/Text.hpp>


namespace sf
{
    class RenderTexture;
    class Font;
    class Vertex;
}



namespace sfge
{


    using sf::Color;
    using sf::Font;
    using sf::Texture;
    using sf::RenderTexture;
    using sf::Vertex;


    /////////////////////////////////////////////////////////////////////
    /// LineEdit - class of one-line text editor
    /////////////////////////////////////////////////////////////////////
    class LineEdit : public iWidget
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// EventType - enumeration of types of events
        /////////////////////////////////////////////////////////////////////
        enum EventType
        {
            STRING_CHANGED,     // string was changed
            INPUT_COMPLETED     // input was completed
        };

        /////////////////////////////////////////////////////////////////////
        /// default constructor - create empty label
        /////////////////////////////////////////////////////////////////////
        LineEdit ();

        /////////////////////////////////////////////////////////////////////
        /// attachView - set texture as background
        /// 
        /// @param tex - pointer to texture
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        void attachReaction (const std::function<void ()> func, const EventType e);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to background
        /// 
        /// @param tex - pointer to texture
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::shared_ptr<const Texture> tex);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to background
        /// 
        /// @param tex - texture name
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::string& tex);

        /////////////////////////////////////////////////////////////////////
        /// attachView - fill bachground by color
        /// 
        /// @param color - new color
        /////////////////////////////////////////////////////////////////////
        void attachView (const Color color);

        /////////////////////////////////////////////////////////////////////
        /// setFont - set font to text in widget
        /// 
        /// @param font - new font
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::shared_ptr<const Font> font);

        /////////////////////////////////////////////////////////////////////
        /// setFont - set font to text in widget
        /// 
        /// @param font - new font
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::string& font);

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize - set size of character in widget
        /// 
        /// @param size - new size in pixels
        /////////////////////////////////////////////////////////////////////
        void setCharacterSize (const unsigned size);
        
        /////////////////////////////////////////////////////////////////////
        /// setTextColor - set color of text in widget
        /// 
        /// @param color - new color
        /////////////////////////////////////////////////////////////////////
        void setTextColor (Color color);

        /////////////////////////////////////////////////////////////////////
        /// setString - set string in widget
        /// 
        /// @param string - new string
        /////////////////////////////////////////////////////////////////////
        void setString (const UString& string);

        /////////////////////////////////////////////////////////////////////
        /// inputString - insert at current caret position string
        /// 
        /// @param string - string for addition
        /////////////////////////////////////////////////////////////////////
        void inputString (const UString& string);

        /////////////////////////////////////////////////////////////////////
        /// deleteChar - delete a char before caret
        /////////////////////////////////////////////////////////////////////
        void deleteChar ();

        /////////////////////////////////////////////////////////////////////
        /// clear - delete line
        /////////////////////////////////////////////////////////////////////
        void clear ();

        /////////////////////////////////////////////////////////////////////
        /// getString - get current string
        /// 
        /// @return - string from line editor
        /////////////////////////////////////////////////////////////////////
        UString getString ();

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void enter () override;

        virtual bool check_key (const sf::Event::KeyEvent&, const bool) override;
        virtual void check_text (const sf::Event::TextEvent&) override;
        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool) override;
        virtual bool check_mouse (const int x, const int y) override;

        virtual void draw (sf::RenderTarget&) const override;

        virtual void update (const float delta) override;

        void redraw ();

        unsigned get_width (const unsigned index) const;

        void set_focus_pos (int x);
        unsigned get_focus_pos () const;

        void add_char (const sf::Uint32);


        std::function<void ()> m_string_changed;
        std::function<void ()> m_input_completed;


        sf::Text m_text;
        UString m_string;
        unsigned m_focused_char = 0;

        RenderRect m_outward_view;
        Panel m_background;
        Panel m_focus;

        Vertex m_line[2];

        std::unique_ptr<RenderTexture> m_texture;

        bool m_is_pressed = false;
        float m_dc_timer = 0.0f;

        unsigned m_offset = 0;
    };


}