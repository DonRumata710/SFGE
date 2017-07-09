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
#include "Widget.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>


namespace sfge
{


    using sf::Texture;
    using sf::Font;
    using sf::Color;


    /////////////////////////////////////////////////////////////////////
    /// WidgetStyle - set of styles for widgets
    /////////////////////////////////////////////////////////////////////
    class WidgetStyle final
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        WidgetStyle () = default;

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @paran position - widget position
        /////////////////////////////////////////////////////////////////////
        WidgetStyle (const iWidget::Position position);

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        /////////////////////////////////////////////////////////////////////
        WidgetStyle (const Frame::Position position, const int x_offset, const int y_offset);

        /////////////////////////////////////////////////////////////////////
        /// setView - attach texture to style set
        /// 
        /// @param tex - pointer to texture
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        void setView (const std::shared_ptr<const Texture> tex, const iWidget::View e = iWidget::View::RELEASED);

        /////////////////////////////////////////////////////////////////////
        /// setView - attach texture to style set
        /// 
        /// @param tex - name of texture loaded to resource manager
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        void setView (const std::string& tex, const iWidget::View e = iWidget::View::RELEASED);

        /////////////////////////////////////////////////////////////////////
        /// setView - attach color to style set
        /// 
        /// @param color - color of button
        /// @param e - event type after which texture will be used
        /////////////////////////////////////////////////////////////////////
        void setView (const Color& color, const iWidget::View e = iWidget::View::RELEASED);

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize set size of text
        ///
        /// @parameter size - size of characters in pixels
        /////////////////////////////////////////////////////////////////////
        void setCharacterSize (unsigned size);

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setFont (std::shared_ptr<const Font> font);

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - name of font loaded to resource manager
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::string& font);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position describe alignment of the widget
        /// @param x_offset - axial distance x between alignment object and widget
        /// @param y_offset - axial distance y between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position, const int x_offset, const int y_offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position describe alignment of the widget
        /// @param offset - distance between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position, const Vector2i offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position - alignment of the widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        ///
        /// @param x_offset - axial distance x between alignment object and widget
        /// @param y_offset - axial distance y between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const int x_offset, const int y_offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        ///
        /// @param offset - distance between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Vector2i offset);

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of widget
        /// 
        /// @param x - width od widget
        /// @param y - height of widget
        /////////////////////////////////////////////////////////////////////
        void setSize (const unsigned x, const unsigned y);

        /////////////////////////////////////////////////////////////////////
        /// attach - attach style to widget
        ///
        /// @param widget - pointer to widget
        /////////////////////////////////////////////////////////////////////
        template<class Widget> void attach (Widget* widget) const
        {
            for (auto texture : m_textures)
                widget->setView (texture.second, texture.first);

            for (auto color : m_colors)
                widget->setView (color.second, color.first);

            if (m_font)
                widget->setFont (m_font);

            if (m_font_size)
                widget->setCharacterSize (m_font_size);

            if (m_position_changed)
                widget->setPosition (m_alignment, m_x_offset, m_y_offset);

            if (m_width || m_height)
                widget->setSize (m_width, m_height);
        }

    private:
        std::vector<std::pair<iWidget::View, std::shared_ptr<const Texture>>> m_textures;
        std::vector<std::pair<iWidget::View, Color>> m_colors;
        std::shared_ptr<const Font> m_font;
        unsigned m_font_size = 0;

        Frame::Position m_alignment = Frame::Position::HCENTER | Frame::Position::VCENTER;
        int m_x_offset = 0;
        int m_y_offset = 0;
        Vector2i m_position;
        unsigned m_width = 0;
        unsigned m_height = 0;

        bool m_position_changed = false;
    };


}