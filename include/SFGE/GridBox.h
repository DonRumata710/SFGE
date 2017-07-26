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


#include "Config.h"
#include "WidgetCollection.h"
#include "WidgetStyle.h"

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
    class GridBox : public iWidgetCollection
    {
    public:

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
        /// closeWidget - close widget contained in this grid
        /// 
        /// @param widget - widget to close
        /////////////////////////////////////////////////////////////////////
        virtual void eraseWidget (iWidget* widget) override;

    private:
        virtual void forEach (std::function<bool (iWidget*)> function) const override;

        virtual void resizeWidgets () override;

    private:
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
    };


}