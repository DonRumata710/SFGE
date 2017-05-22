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


#include "PullDownMenu.h"
#include "MenuItem.h"


using namespace sfge;


void PullDownMenu::addItem (std::shared_ptr<MenuItem> item)
{
    m_items.push_back (item);
    add_frame (item.get ());
    item->setPosition (TOP | LEFT);
    
    if (Field::getSize().x < item->getTextSize ().x)
        set_size (item->getTextSize ().x, 0);

    unsigned item_height (0);
    if (m_auto_size)
        item_height = m_items[0]->getCharacterSize () + m_items[0]->getCharacterSize () / 2;
    else
        item_height = Frame::getSize ().y / m_items.size ();

    for (auto item : m_items)
        item->setSize (Field::getSize ().x, item_height);
}

void PullDownMenu::setItemView (Color color, View view)
{
    for (auto item : m_items)
        item->setView (color, (Button::EventType) view);
}

void PullDownMenu::setItemView (std::shared_ptr<const Texture> texture, View view)
{
    for (auto item : m_items)
        item->setView (texture, (Button::EventType) view);
}

void PullDownMenu::setAutoHeight (bool auto_size)
{
    m_auto_size = auto_size;
}

void PullDownMenu::show (const Vector2i position)
{
    setPosition (position);
    Vector2i pos;
    for (size_t i = 0; i < m_items.size (); ++i)
    {
        m_items[i]->setPosition (pos);
        pos.y += m_items[i]->getSize ().y;
    }
    setVisible (true);
}

void PullDownMenu::collapse ()
{
    setVisible (false);
    m_hover_item = SIZE_MAX;
    m_active_item = SIZE_MAX;
}

bool PullDownMenu::isShown () const
{
    return isVisible ();
}

void PullDownMenu::setRect (const PositionDesc& desc)
{
    set_position_desc (desc);

    if (m_items.empty ())
        return;

    unsigned item_height (0);
    if (m_auto_size)
    {
        item_height = m_items[0]->getCharacterSize () + m_items[0]->getCharacterSize () / 2;
        for (auto item : m_items)
        {
            if (Field::getSize ().x < item->getTextSize ().x)
                set_size (item->getTextSize ().x, 0);
        }
    }
    else
        item_height = desc.height / m_items.size ();
    
    for (auto item : m_items)
        item->setSize (Field::getSize ().x, item_height);
}

void PullDownMenu::draw (RenderTarget& target) const
{
    for (auto item : m_items)
        call_draw (item.get (), target);
}

bool PullDownMenu::check_key (const sf::Event::KeyEvent& e, const bool pressed)
{
    if (m_items.empty ())
        return false;

    if (e.code == sf::Keyboard::Return && pressed && m_active_item < m_items.size ())
    {
        if (call_check_key (m_items[m_active_item].get (), e, true))
            collapse ();
        return true;
    }
    else if (e.code == sf::Keyboard::Up)
    {
        if (m_active_item >= m_items.size ())
            m_active_item = 0;
        else
            ++m_active_item;

        if (m_active_item >= m_items.size ())
            m_active_item = m_items.size () - 1;

        return true;
    }
    else if (e.code == sf::Keyboard::Down)
    {
        if (m_items.empty ())
            return false;

        if (m_active_item >= m_items.size ())
            m_active_item = m_items.size () - 1;
        else
            --m_active_item;

        if (m_active_item >= m_items.size ())
            m_active_item = 0;

        return true;
    }
    else if (e.code == sf::Keyboard::PageUp)
        m_active_item = 0;
    else if (e.code == sf::Keyboard::PageDown)
        m_active_item = m_items.size () - 1;
    return false;
}

void PullDownMenu::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
{
    if (!pressed && m_hover_item < m_items.size ())
    {
        call_check_mouse_button (m_items[m_hover_item].get (), e, pressed);
        collapse ();
    }
}

bool PullDownMenu::check_mouse (const int x, const int y)
{
    m_hover_item = SIZE_MAX;

    for (size_t i = 0; i < m_items.size (); ++i)
    {
        if (call_check_mouse (m_items[i].get (), x, y))
            m_hover_item = i;
    }

    if (m_hover_item < m_items.size ())
        return true;
    else
        return false;
}
