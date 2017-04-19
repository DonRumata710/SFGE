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

#include <SFML/Graphics/RenderTarget.hpp>



namespace sfge
{
    

    CheckBox::CheckBox ()
    {}

    void CheckBox::attachReaction (const std::function<void ()> func)
    {
        m_state_changed = func;
    }

    void CheckBox::attachView (const std::shared_ptr<const sf::Texture> tex, const ViewType type)
    {
        if (type == ViewType::BACKGROUND)
            m_background = tex;
        else
            m_flag = tex;
    }

    void CheckBox::addCollision (std::shared_ptr<CheckBox> cb)
    {
        m_collisions.push_back (cb);
    }

    void CheckBox::setState (bool state)
    {
        m_state = state;
        if (m_state_changed) m_state_changed ();

        if (state)
        {
            for (std::shared_ptr<CheckBox> cb : m_collisions)
                cb->setState (false);
        }
    }

    bool CheckBox::getState () const
    {
        return m_state;
    }

    void CheckBox::setRect (const PositionDesc& desc)
    {
        m_background.setPosition (desc.x, desc.y);

        sf::Vector2u pos (desc.x, desc.y);

        pos += m_background.getSize () / (unsigned) 2 - m_flag.getSize () / (unsigned) 2;
        m_flag.setPosition (pos);

        m_background.setSize (desc.width, desc.height);
    }

    void CheckBox::draw (sf::RenderTarget& target) const
    {
        target.draw (m_background);
        if (m_state) target.draw (m_flag);
    }

    bool CheckBox::check_key (const sf::Event::KeyEvent& e, const bool pressed)
    {
        if (e.code == sf::Keyboard::Return && pressed)
        {
            setState (!m_state);
            if (m_state_changed) m_state_changed ();

            return true;
        }
        return false;
    }

    void CheckBox::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
    {
        if (pressed)
        {
            setState (!m_state);
            if (m_state_changed) m_state_changed ();
        }
    }

    bool CheckBox::check_mouse (const int x, const int y)
    {
        return m_background.contains (x, y);
    }


}
