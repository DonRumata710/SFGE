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
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
/////////////////////////////////////////////////////////////////////


#pragma once


#include "Widget.h"
#include "Panel.h"
#include "Field.h"

#include <unordered_map>



namespace sf
{


    class Color;
    class Texture;


}


namespace sfge
{


    using sf::Color;
    using sf::Texture;
    using sf::Vector2u;


    /////////////////////////////////////////////////////////////////////
    /// GridBox - widget container
    /// 
    /// This widget can contain another widgets.
    /////////////////////////////////////////////////////////////////////
    class GridBox : public iWidget, public Field
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        GridBox ();
        
        /////////////////////////////////////////////////////////////////////
        /// setRowsCount - set count of rows in grid
        /// 
        /// @param rows - count of rows
        /////////////////////////////////////////////////////////////////////
        void setRowsCount (unsigned rows);

        /////////////////////////////////////////////////////////////////////
        /// setColumnsCount - set count of columns in grid
        /// 
        /// @param columns - count of columns
        /////////////////////////////////////////////////////////////////////
        void setColumnsCount (unsigned columns);

        /////////////////////////////////////////////////////////////////////
        /// addWidget - add widget in grid
        /// 
        /// @param widget - pointer to widget
        /// @param column - column where widget should be placed
        /// @param row - row where widget should be placed
        /////////////////////////////////////////////////////////////////////
        void addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row);

        /////////////////////////////////////////////////////////////////////
        /// addWidget - add widget to grid
        /// 
        /// This function place widget to several cells.
        /// 
        /// @param widget - pointer to widget
        /// @param column - column where widget should be placed
        /// @param row - row where widget should be placed
        /// @param sec_column - column where widget ends
        /// @param sec_row - row where widget ends
        /////////////////////////////////////////////////////////////////////
        void addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row, unsigned sec_column, unsigned sec_row);

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set texture of background
        /// 
        /// @param texture - pointer to texture
        /////////////////////////////////////////////////////////////////////
        void setBackground (std::shared_ptr<const Texture> texture);

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set texture of background
        /// 
        /// @param texture - name of texture loaded to resource manager
        /////////////////////////////////////////////////////////////////////
        void setBackground (const std::string& texture);

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set color of background
        /// 
        /// @param color - color of background
        /////////////////////////////////////////////////////////////////////
        void setBackground (sfge::Color color);

        /////////////////////////////////////////////////////////////////////
        /// closeWidget - close widget contained in this grid
        /// 
        /// @param widget - widget to close
        /////////////////////////////////////////////////////////////////////
        void closeWidget (iWidget* widget);

        /////////////////////////////////////////////////////////////////////
        /// setSpacing - set space between widgets
        /// 
        /// @param space - space
        /////////////////////////////////////////////////////////////////////
        void setSpacing (unsigned space);

        /////////////////////////////////////////////////////////////////////
        /// setFrameOffset - set offset between widgets and borders of widget
        /// 
        /// @param offset - space between widgets and borders
        /////////////////////////////////////////////////////////////////////
        void setBorderOffset (unsigned offset);

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void enter () override;
        virtual void leave () override;
        virtual bool is_done () override;

        virtual void draw (RenderTarget& target) const override;
        virtual void update (const float delta) override;

        virtual bool check_key (const Event::KeyEvent& e, const bool pressed) override;
        virtual void check_text (const Event::TextEvent& e) override;
        virtual void check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed) override;
        virtual void check_wheel (const Event::MouseWheelScrollEvent& e) override;
        virtual void check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect) override;
        virtual void check_joystick (const Event::JoystickMoveEvent& e) override;
        virtual void check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed) override;
        virtual void check_touch (const Event::TouchEvent& e) override;
        virtual void check_sensor (const Event::SensorEvent& e) override;
        virtual void check_click () override;
        virtual bool check_mouse (const int x, const int y) override;


        void resize_widgets ();


        struct WidgetDescription
        {
            std::shared_ptr<iWidget> widget;
            uint32_t size = 1 << 16 | 1;

            WidgetDescription () {}

            WidgetDescription (std::shared_ptr<iWidget> w) :
                widget (w)
            {}

            WidgetDescription& operator= (const WidgetDescription& desc)
            {
                widget = desc.widget;
                size = desc.size;
                return *this;
            }
        };

        unsigned m_rows = 0;
        unsigned m_columns = 0;

        std::unordered_map<unsigned, WidgetDescription> m_widgets;

        Panel m_background;

        unsigned m_space = 0;
        unsigned m_border_offset = 0;
    };


}