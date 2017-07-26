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


#include "ItemList.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


void ItemList::addWidget (std::shared_ptr<iWidget> widget, size_t index)
{
    if (index < m_widgets.size ()) m_widgets.insert (m_widgets.begin () + index, widget);
    else m_widgets.push_back (widget);
}

void ItemList::setOrientation (Orientation orientation)
{
    m_orientation = orientation;
    resizeWidgets ();
}

void ItemList::eraseWidget (iWidget* widget)
{
    m_widgets.erase (std::find_if (m_widgets.begin (), m_widgets.end (), [widget](std::shared_ptr<iWidget> w) { return w.get () == widget; }));
}

bool ItemList::check_key (const Event::KeyEvent& e, const bool pressed)
{
    switch (e.code)
    {
    case sf::Keyboard::Up:
        if (pressed)
        {
            --m_current_item;
            if (m_current_item >= m_widgets.size ())
                m_current_item = m_widgets.size () - 1;
        }
        break;
    case sf::Keyboard::Down:
        if (pressed)
        {
            ++m_current_item;
            if (m_current_item >= m_widgets.size ())
                m_current_item = 0;
        }
        break;
    default:
        call_check_key (getFocusedWidget (), e, pressed);
        break;
    }
    return false;
}

void ItemList::check_wheel (const Event::MouseWheelScrollEvent& e)
{
    if (m_widgets.empty ()) return;

    if (e.wheel > 0)
    {
        ++m_current_item;
        if (m_current_item >= m_widgets.size ())
            m_current_item = 0;
    }
    else
    {
        --m_current_item;
        if (m_current_item >= m_widgets.size ())
            m_current_item = m_widgets.size () - 1;
    }
}

void ItemList::resizeWidgets ()
{
    size_t width (m_background.getSize ().x - m_border_offset * 2);
    size_t height (m_background.getSize ().y - m_border_offset * 2);

    if (m_orientation == VERTICAL)
        height /= m_widgets.size ();
    else
        width /= m_widgets.size ();

    for (size_t i = 0; i < m_widgets.size (); ++i)
    {
        if (m_orientation == VERTICAL)
        {
            m_widgets[i]->setPosition (
                m_space / 2 + m_background.getPosition ().x + m_border_offset + width,
                m_space / 2 + m_background.getPosition ().y + m_border_offset + height * i
            );
        }
        else
        {
            m_widgets[i]->setPosition (
                m_space / 2 + m_background.getPosition ().x + m_border_offset + width * i,
                m_space / 2 + m_background.getPosition ().y + m_border_offset + height
            );
        }

        m_widgets[i]->setSize (width - m_space, height - m_space);
    }
}
