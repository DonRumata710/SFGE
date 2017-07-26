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


#include "CheckBox.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


void CheckBox::attachReaction (const std::function<void (State)> func)
{
    m_state_changed = func;
}

void CheckBox::setView (const std::shared_ptr<const sf::Texture> tex, const View view)
{
    switch (view)
    {
    case View::RELEASED:
        m_background.setTexture (tex);
        break;
    case View::HOVER:
        m_hover.setTexture (tex);
        break;
    case View::PRESSED:
        m_flag.setTexture (tex);
        break;
    }
}

void CheckBox::setView (const std::string& tex, const View view)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setView (rm->findTexture (tex), view);
}

void CheckBox::setView (const Color& color, const View view)
{
    switch (view)
    {
    case View::RELEASED:
        m_background.setColor (color);
        break;
    case View::HOVER:
        m_hover.setColor (color);
        break;
    case View::PRESSED:
        m_flag.setColor (color);
        break;
    }
}

void CheckBox::addCollision (const std::shared_ptr<CheckBox> cb)
{
    m_collisions.push_back (cb);
}

void CheckBox::setState (const State state)
{
    if (state ==  State::CHECKED)
    {
        for (std::shared_ptr<CheckBox> cb : m_collisions)
            if (cb.get () != this) cb->setState (State::UNCHECKED);
    }

    m_state = state;
    if (m_state_changed) m_state_changed (m_state);
}

CheckBox::State CheckBox::getState () const
{
    return m_state;
}

void CheckBox::setRect (const PositionDesc& desc)
{
    m_background.setPosition (desc.x, desc.y);
    m_hover.setPosition (desc.x, desc.y);
    m_flag.setPosition (desc.x, desc.y);

    m_background.setSize (desc.width, desc.height);
    m_hover.setSize (desc.width, desc.height);
    m_flag.setSize (desc.width, desc.height);
}

void CheckBox::draw (sf::RenderTarget& target) const
{
    target.draw (*m_active);
    if (m_state == State::CHECKED)
        target.draw (m_flag);
}

bool CheckBox::check_key (const sf::Event::KeyEvent& e, const bool pressed)
{
    if (e.code == sf::Keyboard::Return && pressed)
    {
        setState (m_state == State::CHECKED ? State::UNCHECKED : State::CHECKED);
        if (m_state_changed) m_state_changed (m_state);

        return true;
    }
    return false;
}

void CheckBox::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
{
    if (pressed)
    {
        setState (m_state == State::CHECKED ? State::UNCHECKED : State::CHECKED);
        if (m_state_changed) m_state_changed (m_state);
    }
}

bool CheckBox::check_mouse (const int x, const int y)
{
    if (m_background.contains (x, y))
    {
        m_active = &m_hover;
        return true;
    }
    else
    {
        m_active = &m_background;
        return false;
    }
}
