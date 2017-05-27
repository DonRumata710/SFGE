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


#include "Slider.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "GuiManager.h"



namespace sfge
{


    Slider::Slider ()
    {}

    Slider::~Slider ()
    {}

    void Slider::setInterval (const float min, const float max)
    {
        m_min = min;
        m_max = max;
        if (m_value < min || m_value > max)
            m_value = min;

        calc_slider_position ();
    }

    void Slider::setMode (Mode mode)
    {
        m_mode = mode;
    }

    void Slider::setOrientation (const Orientation o)
    {
        if (m_orient != o)
        {
            auto size (m_outward_view.getSize ());
            m_outward_view.setSize (size.y, size.x);
            calc_slider_position ();
        }
    }

    void Slider::attachBackground (const std::shared_ptr<const sf::Texture> tex)
    {
        auto size (tex->getSize ());

        if (size.x > size.y)
            m_orient = HORIZONTAL;
        else if (size.x < size.y)
            m_orient = VERTICAL;

        m_outward_view.setTexture (tex);

        if (m_outward_view.getSize ().x == 0)
            m_outward_view.setSize ({ (float) tex->getSize ().x, (float) tex->getSize ().y });
    }

    void Slider::attachBackground (const std::string& tex)
    {
        attachBackground (ResourceManager::getInstance ()->findTexture (tex));
    }

    void Slider::attachSlider (const std::shared_ptr<const sf::Texture> slider, const View view)
    {
        switch (view)
        {
        case View::RELEASED:
            m_released_slider = slider;
            m_slider.setTexture (m_released_slider);
            break;
        case View::HOVER:
            m_focused_slider = slider;
            break;
        case View::PRESSED:
            m_pressed_slider = slider;
            break;
        default:
            break;
        }
    }

    void Slider::attachSlider (const std::string& tex, const View view)
    {
        auto rm (ResourceManager::getInstance ());
        if (rm)
            attachSlider (rm->findTexture (tex), view);
    }

    void Slider::attachReaction (std::function<void ()> func, const EventType event_type)
    {
        switch (event_type)
        {
        case EventType::PRESSED:
            m_pressed = func;
            break;
        case EventType::RELEASED:
            m_released = func;
            break;
        case EventType::VALUE_CHANGED:
            m_value_changed = func;
            break;
        default:
            break;
        }
    }

    void Slider::setValue (const float value)
    {
        if (value == m_value) return;

        m_value = value;

        if (value < m_min)
            m_value = m_min;
        else if (value > m_max)
            m_value = m_max;

        calc_slider_position ();
        m_value_changed ();
    }

    float Slider::getValue () const
    {
        return m_value;
    }

    void Slider::setRect (const PositionDesc & desc)
    {
        m_outward_view.setPosition (static_cast<float> (desc.x), static_cast<float> (desc.y));
        m_outward_view.setSize (static_cast<float> (desc.width), static_cast<float> (desc.height));

        unsigned size (desc.width < desc.height ? desc.width : desc.height);
        m_slider.setSize (static_cast<float> (size), static_cast<float> (size));
    
        calc_slider_position ();
    }

    void Slider::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
    {
        if (pressed)
        {
            set_view (View::PRESSED);
            m_is_pressed = true;
            if (m_pressed) m_pressed ();
        }
        else
        {
            set_view (View::RELEASED);
            m_is_pressed = false;
            if (m_released) m_released ();
        }
    }

    bool Slider::check_mouse (const int x, const int y)
    {
        if (m_slider.contains (static_cast<float> (x), static_cast<float> (y)))
        {
            if (!m_is_pressed)
                set_view (View::HOVER);
            else
            {
                sf::Vector2i delta (x - m_mouse.x, y - m_mouse.y);

                if (m_orient == HORIZONTAL)
                {
                    setValue (
                        float ((int) m_slider.getPosition ().x + delta.x - (int) m_outward_view.getPosition ().x) *
                        (m_max - m_min) / (m_outward_view.getSize ().x - m_outward_view.getSize ().y)
                    );

                    //m_slider.setPosition (m_slider.getPosition ().x + delta.x, m_slider.getPosition ().y);
                }
                else
                {
                    setValue (
                        float ((int) m_slider.getPosition ().y + delta.y - (int) m_outward_view.getPosition ().y) *
                        (m_max - m_min) / (m_outward_view.getSize ().y - m_outward_view.getSize ().x)
                    );

                    //m_slider.setPosition (m_slider.getPosition ().x, m_slider.getPosition ().y + delta.y);
                }

                m_value_changed ();
            }

            m_mouse.x = x;
            m_mouse.y = y;

            return true;
        }
        else
        {
            m_is_pressed = false;
            set_view (View::RELEASED);
            return false;
        }
    }

    void Slider::draw (sf::RenderTarget& target) const
    {
        target.draw (m_outward_view);
        target.draw (m_slider);
    }

    void Slider::calc_slider_position ()
    {
        sf::Vector2u pos (m_outward_view.getPosition ());
        sf::Vector2u slider_pos;

        if (m_orient == VERTICAL)
        {
            slider_pos.x = pos.x;
            slider_pos.y = pos.y + ((int) m_outward_view.getSize ().y - (int) m_outward_view.getSize ().x) * m_value / (m_max - m_min);
        }
        else
        {
            slider_pos.x = pos.x + ((int) m_outward_view.getSize ().x - (int) m_outward_view.getSize ().y) * m_value / (m_max - m_min);
            slider_pos.y = pos.y;
        }

        m_slider.setPosition (slider_pos.x, slider_pos.y);
    }

    void Slider::set_view (const View type)
    {
        switch (type)
        {
        case View::PRESSED:
            if (m_pressed_slider) m_slider.setTexture (m_pressed_slider);
            break;
        case View::HOVER:
            if (m_focused_slider) m_slider.setTexture (m_focused_slider);
            break;
        case View::RELEASED:
            if (m_released_slider) m_slider.setTexture (m_released_slider);
            break;
        default:
            break;
        }
    }


}