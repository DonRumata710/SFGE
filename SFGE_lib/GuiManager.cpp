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


#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <cstring>

#include "Err.h"



namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    // Time of doubleclick in seconds
    /////////////////////////////////////////////////////////////////////
    const float CLICK_TIME = 0.15f;


    enum
    {
        EXIT = -1
    };

    
    GUIManager::GUIManager (GEDevice* device)
    {
        m_device = device;
        m_background.setColor (sf::Color::Black);
    }

    void GUIManager::addFrontWidget (pWidget widget)
    {
        m_widgets.push_back (widget);
        add_frame (widget.get ());
    }

    void GUIManager::addBackWidget (pWidget widget)
    {
        m_widgets.insert (m_widgets.begin (), widget);
        add_frame (widget.get ());
    }

    void GUIManager::setBackground (std::shared_ptr<const Texture> tex)
    {
        m_background = tex;
    }

    void GUIManager::setBackground (const std::string& texture)
    {
        setBackground (ResourceManager::getInstance ()->findTexture (texture));
    }

    void GUIManager::setBackground (const Color& color)
    {
        m_background.setColor (color);
    }

    void GUIManager::setFocusLocked (bool flag)
    {
        m_focus_locked = flag;
    }

    bool GUIManager::update ()
    {
        if (m_state == State::INACTIVE || !m_window) return false;

        float delta (m_timer.restart ().asSeconds ());

        for (pWidget widget : m_widgets)
            Field::call_update (widget.get (), delta);

        m_click_timer += delta;

        if (m_state != State::ACTIVE)
        {
            bool is_done (true);
            for (pWidget widget : m_widgets)
            {
                if (!Field::call_is_done (widget.get ()))
                    is_done = false;
            }

            if (is_done)
            {
                if (m_state == State::ENTER)
                    m_state = State::ACTIVE;
                if (m_state == State::LEAVE)
                {
                    m_state = State::INACTIVE;
                    return false;
                }
            }
            else return true;
        }

        Event e;
        std::memset (&e, 0, sizeof (Event));

        while (m_window->pollEvent (e))
        {
            if (!handle_event (e))
                return false;
        }

        return true;
    }

    void GUIManager::draw () const
    {
        m_window->clear ();

        m_window->draw (m_background);

        for (pWidget widget : m_widgets)
        {
            if (widget->isVisible ())
                Field::call_draw (widget.get (), *m_window);
        }

        m_window->display ();
    }

    void GUIManager::enter (std::unique_ptr<RenderWindow>& window)
    {
        if (!window) critical_error ("GUI manager has got empty pointer to window!", std::runtime_error);

        m_state = State::ENTER;
        m_timer.restart ();
        m_window.swap (window);
        m_background.setSize (m_window->getSize ().x, m_window->getSize ().y);

        set_size (m_window->getSize ());

        for (pWidget widget : m_widgets)
            Field::call_enter (widget.get ());
    }

    void GUIManager::leave ()
    {
        for (pWidget widget : m_widgets)
            Field::call_leave (widget.get ());
        m_state = State::LEAVE;
    }

    bool GUIManager::isActive () const
    {
        return m_state != State::INACTIVE;
    }

    void GUIManager::setSwitch (int s)
    {
        m_switch = s;
    }

    int GUIManager::getSwitch ()
    {
        return m_switch;
    }

    std::unique_ptr<RenderWindow>& GUIManager::getWindow ()
    {
        return m_window;
    }

    bool GUIManager::handle_event (const Event& e)
    {
        switch (e.type)
        {
        case sf::Event::TextEntered:
            if (m_focused_widget)
                Field::call_check_text (m_focused_widget.get (), e.text);
            break;
        case sf::Event::EventType::KeyPressed:
        case sf::Event::EventType::KeyReleased:
            if (!m_focused_widget ||
                (m_focused_widget && !Field::call_check_key (m_focused_widget.get (), e.key, e.type == sf::Event::EventType::KeyPressed))
            )
                find_focus (e.key);
            break;
        case sf::Event::EventType::MouseMoved:
        {
            m_over_widget = nullptr;
            bool flag (true);
            for (auto widget = m_widgets.rbegin (); widget != m_widgets.rend (); ++widget)
            {
                if (Field::call_check_mouse (widget->get (), e.mouseMove.x, e.mouseMove.y) && flag)
                {
                    m_over_widget = *widget;
                    flag = false;
                }
            }
            break;
        }
        case sf::Event::EventType::MouseWheelScrolled:
            if (m_over_widget && m_over_widget->isEnabled ())
                Field::call_check_wheel (m_over_widget.get (), e.mouseWheelScroll);
            break;
        case sf::Event::EventType::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Button::Left)
                m_click_timer = 0.0f;
            if (m_over_widget && m_over_widget->isEnabled ())
            {
                m_focused_widget = m_over_widget;
                Field::call_check_mouse_button (m_over_widget.get (), e.mouseButton, e.type == sf::Event::EventType::MouseButtonPressed);
            }
            break;
        case sf::Event::EventType::MouseButtonPressed:
            if (m_over_widget && m_over_widget->isEnabled ())
            {
                m_focused_widget = m_over_widget;
                Field::call_check_mouse_button (m_over_widget.get (), e.mouseButton, e.type == sf::Event::EventType::MouseButtonPressed);
            }
            if (e.mouseButton.button == sf::Mouse::Button::Left)
            {
                if (m_click_timer < CLICK_TIME && m_over_widget)
                    Field::call_check_click (m_over_widget.get ());
                m_click_timer = 0.0f;
            }
            break;
        case sf::Event::EventType::Resized:
            m_window->setView (sf::View (sf::FloatRect (0.0f, 0.0f, e.size.width, e.size.height)));
            m_background.setSize (e.size.width, e.size.height);
            set_size (e.size.width, e.size.height);
            break;
        case Event::EventType::Closed:
            setSwitch (EXIT);
            leave ();
            return true;
        default:
            return true;
        }
        return true;
    }

    void GUIManager::find_focus (const Event::KeyEvent& key)
    {
        if (key.control && key.code == sf::Keyboard::Key::Tab && !m_focus_locked)
        {
            if (!m_focused_widget)
            {
                m_focused_widget = *m_widgets.begin ();
                auto it (m_widgets.begin ());
                while (m_focused_widget->isStatic () || !m_focused_widget->isEnabled () || !m_focused_widget->isVisible ())
                {
                    if (it == --m_widgets.end ()) it = m_widgets.begin ();
                    else ++it;
                    if (it == m_widgets.begin ())
                    {
                        m_focused_widget.reset ();
                        return;
                    }
                }
                m_focused_widget = *it;
            }
            else
            {
                auto start (find_widget_iter (m_focused_widget.get ()));
                auto it (start);
                do
                {
                    if (it == m_widgets.begin ()) it = m_widgets.end ();
                    else --it;
                    if (it == start) break;
                }
                while (m_focused_widget->isStatic () || !m_focused_widget->isEnabled () || !m_focused_widget->isVisible ());
                m_focused_widget = *it;
            }
        }
        else if (key.code == sf::Keyboard::Key::Tab && !m_focus_locked)
        {
            if (!m_focused_widget)
            {
                m_focused_widget = *m_widgets.begin ();
                auto it (m_widgets.begin ());
                while (m_focused_widget->isStatic () || !m_focused_widget->isEnabled () || !m_focused_widget->isVisible ())
                {
                    if (it == --m_widgets.end ()) it = m_widgets.begin ();
                    else ++it;
                    if (it == m_widgets.begin ())
                    {
                        m_focused_widget.reset ();
                        return;
                    }
                }
                m_focused_widget = *it;
            }
            else
            {
                auto start (find_widget_iter (m_focused_widget.get ()));
                auto it (start);
                do
                {
                    if (it == --m_widgets.end ()) it = m_widgets.begin ();
                    else ++it;
                    if (it == start) break;
                }
                while ((*it)->isStatic () || !(*it)->isEnabled () || !(*it)->isVisible ());
                m_focused_widget = *it;
            }
        }
    }

    std::vector<pWidget>::iterator GUIManager::find_widget_iter (const iWidget* ptr)
    {
        for (auto it = m_widgets.begin (); it != m_widgets.end (); ++it)
        {
            if ((*it).get () == ptr)
                return it;
        }
        return std::vector<pWidget>::iterator ();
    }



}