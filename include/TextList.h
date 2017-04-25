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

#include <vector>



namespace sf
{
    class RenderTexture;
    class Font;
    class Text;
}



namespace sfge
{


    using sf::Color;
    using sf::Font;
    using sf::Texture;


    /////////////////////////////////////////////////////////////////////
    /// TextList - class for TextList
    ///
    /// This widget provide to show several strings and to chose one of
    /// them. User can chose string by clicking or by press enter
    /////////////////////////////////////////////////////////////////////
    class TextList : public iWidget
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// EventType - enumeration of types of events
        /////////////////////////////////////////////////////////////////////
        enum EventType
        {
            FOCUS_CHANGED,
            ITEM_SELECTED
        };

        /////////////////////////////////////////////////////////////////////
        /// default constructor
        /////////////////////////////////////////////////////////////////////
        TextList ();

        /////////////////////////////////////////////////////////////////////
        /// attachReaction - attach function to handle some event
        ///
        /// @param func - function wich handle this event
        /// @param e - event description
        /////////////////////////////////////////////////////////////////////
        void attachReaction (const std::function<void ()> func, const EventType e);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to widget view
        /// 
        /// @param tex - pointer to texture
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::shared_ptr<const Texture> tex);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to widget view
        /// 
        /// @param tex - name texture
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::string& tex);

        /////////////////////////////////////////////////////////////////////
        /// attachView - fill widget background by color
        /// 
        /// @param color - color of background
        /////////////////////////////////////////////////////////////////////
        void attachView (const Color color);

        /////////////////////////////////////////////////////////////////////
        /// setFont - set font of text in widget
        /// 
        /// @param font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::shared_ptr<const Font> font);

        /////////////////////////////////////////////////////////////////////
        /// setFont - set font of text in widget
        /// 
        /// @param font - font name
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::string& font);

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize - set size of characters in widget
        /// 
        /// @param size - size og characters in pixels
        /////////////////////////////////////////////////////////////////////
        void setCharacterSize (const unsigned size);

        /////////////////////////////////////////////////////////////////////
        /// addString - add string to widget
        /// 
        /// @param str - new string
        /////////////////////////////////////////////////////////////////////
        void addString (const UString& str);

        /////////////////////////////////////////////////////////////////////
        /// removeString - find and remove string from widget
        /// 
        /// @param str - string which should be removed
        /////////////////////////////////////////////////////////////////////
        void removeString (const UString& str);

        /////////////////////////////////////////////////////////////////////
        /// getCurrent - get current string
        /// 
        /// @return string 
        /////////////////////////////////////////////////////////////////////
        std::string getCurrent () const;


    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void enter () override;

        virtual bool check_key (const sf::Event::KeyEvent&, const bool) override;
        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool) override;
        virtual void check_wheel (const sf::Event::MouseWheelScrollEvent&) override;
        virtual void check_click () override;
        virtual bool check_mouse (const int x, const int y) override;

        virtual void draw (sf::RenderTarget&) const override;


        unsigned count_index (const unsigned position) const;
        unsigned count_position (const unsigned index) const;

        void set_focus (unsigned line);

        void replace_text ();

        void redraw ();


        std::function<void ()> m_focus_moved;
        std::function<void ()> m_item_selected;

        RenderRect m_outward_view;
        Panel m_background;
        Panel m_focus;

        std::unique_ptr<sf::RenderTexture> m_texture;

        bool m_is_keyboard_mod = false;

        std::vector<std::shared_ptr<sf::Text>> m_string_list;
        unsigned m_current_focus = UINT32_MAX;

        std::shared_ptr<const sf::Font> m_font = nullptr;
        unsigned m_character_size = 14;

        bool m_is_key_pressed = false;

        int m_offset = 0;
    };


}