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
#include "WidgetCollection.h"
#include "WidgetStyle.h"

#include <vector>


namespace sfge
{


    using sf::Vector2u;


    /////////////////////////////////////////////////////////////////////
    /// ItemList - container for widgets
    ///
    /// ItemList place widgets in vertical or horizontal line.
    /////////////////////////////////////////////////////////////////////
    class ItemList : public iWidgetCollection
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
        /// Orientation - orientation of widget
        /////////////////////////////////////////////////////////////////////
        enum Orientation
        {
            VERTICAL,
            HORIZONTAL
        };

        /////////////////////////////////////////////////////////////////////
        /// addWidget - add widget to list
        /// 
        /// @param widget - pointer to widget
        /// @param column - place of widget
        /////////////////////////////////////////////////////////////////////
        void addWidget (std::shared_ptr<iWidget> widget, size_t index);

        /////////////////////////////////////////////////////////////////////
        /// setOrientation - set orientation of widget
        ///
        /// @param orientation - orientation
        /////////////////////////////////////////////////////////////////////
        void setOrientation (Orientation orientation);

        /////////////////////////////////////////////////////////////////////
        /// closeWidget - close widget contained in this grid
        /// 
        /// @param widget - widget to close
        /////////////////////////////////////////////////////////////////////
        virtual void eraseWidget (iWidget* widget) override;

    private:
        virtual bool check_key (const Event::KeyEvent& e, const bool pressed) override;
        virtual void check_wheel (const Event::MouseWheelScrollEvent& e) override;

        virtual void forEach (std::function<bool (iWidget*)> function) const = 0;
        void resizeWidgets ();

    private:
        std::vector<std::shared_ptr<iWidget>> m_widgets;
        WidgetStyle m_style = { Position::LEFT | Position::TOP };

        Panel m_background;

        unsigned m_space = 0;
        unsigned m_border_offset = 0;

        Orientation m_orientation = VERTICAL;

        size_t m_current_item = SIZE_MAX;
    };


}