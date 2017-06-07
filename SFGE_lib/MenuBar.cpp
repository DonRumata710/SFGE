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


#include "MenuBar.h"
#include "PullDownMenu.h"
#include "MenuItem.h"
#include "Err.h"

#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


void MenuBar::addItem (const UString& text, std::shared_ptr<PullDownMenu> menu)
{
    std::shared_ptr<MenuItem> item (std::make_shared<MenuItem> ());
    item->setText (text);
    item->setPosition (Position::TOP | Position::LEFT);

    menu->setPosition (Position::TOP | Position::LEFT);
    menu->collapse ();

    m_items.push_back ({ item, menu });

    add_frame (item.get ());
    add_frame (menu.get ());
}

void MenuBar::setView (std::shared_ptr<const Texture> texture)
{
    m_view.setTexture (texture);
}

void MenuBar::setView (Color color)
{
    m_view.setColor (color);
}

void MenuBar::setItemView (std::shared_ptr<const Texture> texture, View view)
{
    for (auto item : m_items)
    {
        item.first->setView (texture, view);
        item.second->setItemView (texture, view);
    }
}

void MenuBar::setItemView (Color color, View view)
{
    for (auto item : m_items)
    {
        item.first->setView (color, view);
        item.second->setItemView (color, view);
    }
}

void MenuBar::setRect (const PositionDesc& desc)
{
    set_position_desc (desc);

    m_view.setPosition (desc.x, desc.y);
    m_view.setSize (desc.width, desc.height);

    if (m_items.empty ())
        return;

    int32_t offset (0);

    for (auto item : m_items)
    {
        item.first->setPosition (offset, 0);
        int32_t width (item.first->getTextSize ().x + item.first->getCharacterSize ());
        offset += width;
        item.first->setSize (width, desc.height);
    }
}

void MenuBar::draw (RenderTarget& target) const
{
    target.draw (m_view);

    for (auto item : m_items)
        call_draw (item.first.get (), target);

    if (m_active_item < m_items.size ())
        call_draw (m_items[m_active_item].second.get (), target);
    
}

bool MenuBar::check_key (const sf::Event::KeyEvent& e, const bool pressed)
{
    if (m_items.empty () || m_active_item >= m_items.size ())
        return false;

    if (e.code == sf::Keyboard::Return && pressed)
    {
        call_check_key (m_items[m_active_item].second.get (), e, pressed);
        if (!m_items[m_active_item].second->isShown ())
            choise_handle (m_active_item);
        return true;
    }
    else if (e.code == sf::Keyboard::Tab)
    {
        if (m_items.empty ())
            return false;

        if (m_active_item >= m_items.size ())
            choise_handle (0);
        else
            choise_handle (m_active_item + 1);

        if (m_active_item >= m_items.size ())
            choise_handle (0);

        return true;
    }
    else if (e.code == sf::Keyboard::Home)
        choise_handle (0);
    else if (e.code == sf::Keyboard::End)
        choise_handle (m_items.size () - 1);
    else
        call_check_key (m_items[m_active_item].second.get (), e, pressed);

    return false;
}

void MenuBar::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
{
    if (e.button == sf::Mouse::Button::Left)
    {
        if (m_is_mouse_over_menu)
        {
            call_check_mouse_button (m_items[m_active_item].second.get (), e, pressed);
            if (!m_items[m_active_item].second->isShown ())
                choise_handle (m_active_item);
        }

        if (pressed)
            choise_handle (m_hover_item);
    }
}

bool MenuBar::check_mouse (const int x, const int y)
{
    if (m_active_item < m_items.size () && call_check_mouse (m_items[m_active_item].second.get (), x, y))
        m_is_mouse_over_menu = true;
    else
        m_is_mouse_over_menu = false;

    m_hover_item = SIZE_MAX;

    for (size_t i = 0; i < m_items.size (); ++i)
    {
        if (call_check_mouse (m_items[i].first.get (), x, y))
            m_hover_item = i;
    }

    if (m_hover_item != m_active_item && m_active_item < m_items.size ())
        choise_handle (m_hover_item);

    if (m_hover_item < m_items.size () || m_is_mouse_over_menu)
        return true;
    else
        return false;
}

void MenuBar::choise_handle (size_t item)
{
    if (item > m_items.size ())
        return;

    if (m_active_item < m_items.size ())
        m_items[m_active_item].second->collapse ();

    if (item == m_active_item)
    {
        m_items[m_active_item].second->collapse ();
        m_active_item = SIZE_MAX;
        return;
    }

    Vector2i pos (m_items[item].first->getPosition ());
    pos.y += m_items[item].first->getSize ().y;

    if (m_items[item].second)
        m_items[item].second->show (pos);

    m_active_item = item;
}
