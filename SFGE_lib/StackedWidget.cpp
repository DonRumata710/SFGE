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


#include "StackedWidget.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>



sfge::StackedWidget::StackedWidget ()
{}

void sfge::StackedWidget::setRect (const PositionDesc& desc)
{
    set_position_desc (desc);
}

unsigned sfge::StackedWidget::addWidget (pWidget widget)
{
    m_widgets.push_back (widget);

    add_frame (widget.get ());

    return uint32_t (m_widgets.size () - 1);
}

void sfge::StackedWidget::switchToNext ()
{
    ++m_current_widget;
    m_current_widget %= m_widgets.size ();

    if (m_is_enter)
        enter ();
}

void sfge::StackedWidget::switchToPrevious ()
{
    m_widgets[m_current_widget]->setEnabled (false);
    --m_current_widget;
    if (m_current_widget > m_widgets.size ())
        m_current_widget = uint32_t (m_widgets.size () - 1);
    m_widgets[m_current_widget]->setEnabled (true);

    if (m_is_enter)
        enter ();
}

void sfge::StackedWidget::setActive (unsigned id)
{
    m_widgets[m_current_widget]->setEnabled (false);
    m_current_widget = id;
    m_widgets[m_current_widget]->setEnabled (true);

    if (m_is_enter)
        enter ();
}

void sfge::StackedWidget::removeWidget (iWidget * widget)
{
    for (auto it = m_widgets.begin (); it != m_widgets.end (); ++it)
    {
        if (it->get () == widget)
        {
            m_widgets.erase (it);
            return;
        }
    }
}

void sfge::StackedWidget::enter ()
{
    m_is_enter = true;
    Field::call_enter (m_widgets[m_current_widget].get ());
}

void sfge::StackedWidget::leave ()
{
    m_is_enter = false;
    Field::call_leave (m_widgets[m_current_widget].get ());
}

bool sfge::StackedWidget::is_done ()
{
    return Field::call_is_done (m_widgets[m_current_widget].get ());
}

void sfge::StackedWidget::draw (RenderTarget& target) const
{
    Field::call_draw (m_widgets[m_current_widget].get (), target);
}

void sfge::StackedWidget::update (const float delta)
{
    Field::call_update (m_widgets[m_current_widget].get (), delta);
}

bool sfge::StackedWidget::check_key (const Event::KeyEvent & e, const bool pressed)
{
    return Field::call_check_key (m_widgets[m_current_widget].get (), e, pressed);
}

void sfge::StackedWidget::check_text (const Event::TextEvent& e)
{
    Field::call_check_text (m_widgets[m_current_widget].get (), e);
}

void sfge::StackedWidget::check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed)
{
    Field::call_check_mouse_button (m_widgets[m_current_widget].get (), e, pressed);
}

void sfge::StackedWidget::check_wheel (const Event::MouseWheelScrollEvent& e)
{
    Field::call_check_wheel (m_widgets[m_current_widget].get (), e);
}

void sfge::StackedWidget::check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect)
{
    Field::call_check_joystick_connect (m_widgets[m_current_widget].get (), e, connect);
}

void sfge::StackedWidget::check_joystick (const Event::JoystickMoveEvent& e)
{
    Field::call_check_joystick (m_widgets[m_current_widget].get (), e);
}

void sfge::StackedWidget::check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed)
{
    Field::call_check_joystick_button (m_widgets[m_current_widget].get (), e, pressed);
}

void sfge::StackedWidget::check_touch (const Event::TouchEvent& e)
{
    Field::call_check_touch (m_widgets[m_current_widget].get (), e);
}

void sfge::StackedWidget::check_sensor (const Event::SensorEvent& e)
{
    Field::call_check_sensor (m_widgets[m_current_widget].get (), e);
}

void sfge::StackedWidget::check_click ()
{
    Field::call_check_click (m_widgets[m_current_widget].get ());
}

bool sfge::StackedWidget::check_mouse (const int x, const int y)
{
    return Field::call_check_mouse (m_widgets[m_current_widget].get (), x, y);
}
