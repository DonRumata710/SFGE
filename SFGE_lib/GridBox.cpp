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


#include "GridBox.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


void GridBox::setRowsCount (unsigned rows)
{
    m_rows = rows;
}

void GridBox::setColumnsCount (unsigned columns)
{
    m_columns = columns;
}

void GridBox::addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row)
{
    if (column >= m_columns || row >= m_rows)
    {
        runtime_message ("Grid box is out of range");
        return;
    }

    m_widgets[row * m_columns + column] = widget;
    getStyle ().attach (widget.get ());
    add_frame (widget.get ());
}

void GridBox::addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row, unsigned sec_column, unsigned sec_row)
{
    if (column >= m_columns || row >= m_rows || sec_column >= m_columns || sec_row >= m_rows)
        return;

    m_widgets[row * m_columns + column] = widget;
    m_widgets[row * m_columns + column].size = ((column - sec_column) & 0xFFFF) | ((row - sec_row) << 16);
    getStyle ().attach (widget.get ());
    add_frame (widget.get ());
}

void GridBox::eraseWidget (iWidget* widget)
{
    for (auto w : m_widgets)
    {
        if (w.second.widget.get () == widget)
            m_widgets.erase (w.first);
    }
}

void GridBox::forEach (std::function<bool (iWidget*)> function) const
{
    for (auto widget : m_widgets)
    {
        if (!function (widget.second.widget.get ()))
            break;
    }
}

void GridBox::resizeWidgets ()
{
    unsigned width  ((Frame::getSize ().x - getBorederOffset () * 2) / m_columns);
    unsigned height ((Frame::getSize ().y - getBorederOffset () * 2) / m_rows);

    for (unsigned i = 0; i < m_rows; ++i)
    {
        for (unsigned j = 0; j < m_columns; ++j)
        {
            if (m_widgets.find (i * m_columns + j) == m_widgets.end ())
                continue;

            m_widgets[i * m_columns + j].widget->setPosition (
                getSpace () / 2 + Frame::getPosition ().x + getBorederOffset () + width * j,
                getSpace () / 2 + Frame::getPosition ().y + getBorederOffset () + height * i
            );

            m_widgets[i * m_columns + j].widget->setSize (
                width * (m_widgets[i * m_columns + j].size & 0xFFFF) - getSpace (),
                height * (m_widgets[i * m_columns + j].size >> 16) - getSpace ()
            );
        }
    }
}
