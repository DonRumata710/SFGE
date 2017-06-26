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


#include "Button.h"
#include "Animation.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


using namespace sfge;


Button::Button ()
{
    m_text.setFillColor (Color::White);
    m_text.setCharacterSize (14);
}

void Button::attachReaction (const std::function<void ()> func, const EventType type)
{
    if (type == PRESSED) m_pressed = func;
    else m_released = func;
}

void Button::setView (const std::shared_ptr<const sf::Texture> view, const View type)
{
    switch (type)
    {
    case View::PRESSED:
        m_pressed_view.setTexture (view);
        break;
    case View::HOVER:
        m_hover_view.setTexture (view);
        break;
    case View::RELEASED:
        m_released_view.setTexture (view);
        break;
    default:
        break;
    }

    if (m_view->getSize ().x == 0)
    {
        m_pressed_view.setSize (view->getSize ().x, view->getSize ().y);
        m_hover_view.setSize (view->getSize ().x, view->getSize ().y);
        m_released_view.setSize (view->getSize ().x, view->getSize ().y);
    }
}

void Button::setView (const std::string& tex, const View e)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setView (rm->findTexture (tex), e);
}

void Button::setView (const Color color, const View e)
{
    switch (e)
    {
    case View::PRESSED:
        m_pressed_view.setColor (color);
        break;
    case View::HOVER:
        m_hover_view.setColor (color);
        break;
    case View::RELEASED:
        m_released_view.setColor (color);
        break;
    default:
        break;
    }
}

void Button::setText (const UString& string)
{
    m_text.setString (string);
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (!m_text.getFont () && rm)
        m_text.setFont (*rm->getFont (ResourceManager::DEFAULT));
}

Vector2f Button::getTextSize () const
{
    return { m_text.getLocalBounds ().width, m_text.getLocalBounds ().height };
}

void Button::setFont (std::shared_ptr<const Font> font)
{
    m_text.setFont (*font);
}

void Button::setFont (const std::string& font)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setFont (rm->findFont (font));
}

void Button::setCharacterSize (unsigned size)
{
    m_text.setCharacterSize (size);
}

unsigned Button::getCharacterSize () const
{
    return m_text.getCharacterSize ();
}

void Button::setTextColor (Color color)
{
    m_text.setFillColor (color);
}

void Button::setRect (const PositionDesc& desc)
{
    m_pressed_view.setPosition (desc.x, desc.y);
    m_pressed_view.setSize (desc.width, desc.height);

    m_hover_view.setPosition (desc.x, desc.y);
    m_hover_view.setSize (desc.width, desc.height);

    m_released_view.setPosition (desc.x, desc.y);
    m_released_view.setSize (desc.width, desc.height);

    sf::Vector2f size (m_text.getGlobalBounds ().width, m_text.getGlobalBounds ().height);

    m_text.setPosition (desc.x + Int32 (m_view->getSize ().x / 2 - size.x / 2), desc.y + Int32 (m_view->getSize ().y / 2 - size.y / 2));
}

void Button::draw (sf::RenderTarget& target) const
{
    target.draw (*m_view);
    target.draw (m_text);
}

bool Button::check_key (const sf::Event::KeyEvent& e, const bool pressed)
{
    if (e.code == sf::Keyboard::Return && pressed && m_pressed)
    {
        m_pressed ();
        return true;
    }
    return false;
}

void Button::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
{
    if (pressed)
    {
        set_view (View::PRESSED);
        if (m_pressed) m_pressed ();
    }
    else
    {
        set_view (View::RELEASED);
        if (m_released) m_released ();
    }
}

bool Button::check_mouse (const int x, const int y)
{
    if (m_view->contains (static_cast<float> (x), static_cast<float> (y)))
    {
        set_view (View::HOVER);
        return true;
    }
    else
    {
        set_view (View::RELEASED);
        return false;
    }
}

void Button::set_view (const View type)
{
    switch (type)
    {
    case View::PRESSED:
        m_view = &m_pressed_view;
        break;
    case View::HOVER:
        if (m_view != &m_pressed_view) m_view = &m_hover_view;
        break;
    case View::RELEASED:
        m_view = &m_released_view;
        break;
    default:
        break;
    }
}
