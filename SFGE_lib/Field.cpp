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


#include "Field.h"
#include "Widget.h"


sfge::Field::Field ()
{}

sfge::Field::~Field ()
{}

sfge::Vector2i sfge::Field::getPosition () const
{
    return { m_position.x, m_position.y };
}

sfge::Vector2u sfge::Field::getSize () const
{
    return { m_position.width, m_position.height };
}

const sfge::PositionDesc& sfge::Field::getPositionDesc () const
{
    return m_position;
}

void sfge::Field::add_frame (Frame* frame)
{
    m_frames.push_back (frame);
    if (m_position.width)
        frame->setFieldParam (m_position);
}

void sfge::Field::remove_frame (Frame* frame)
{
    m_frames.erase (std::remove (m_frames.begin (), m_frames.end (), frame));
}

void sfge::Field::set_size (Vector2u size)
{
    m_position.width = size.x;
    m_position.height = size.y;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void sfge::Field::set_size (unsigned width, unsigned height)
{
    m_position.width = width;
    m_position.height = height;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void sfge::Field::set_position (Vector2i position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void sfge::Field::set_position_desc (const PositionDesc& desc)
{
    m_position = desc;
}



void sfge::Field::call_enter (iWidget* widget)
{
    widget->enter ();
}

void sfge::Field::call_leave (iWidget * widget)
{
    widget->leave ();
}

bool sfge::Field::call_is_done (iWidget * widget)
{
    return widget->is_done ();
}

void sfge::Field::call_draw (iWidget * widget, RenderTarget & target) const
{
    widget->draw (target);
}

void sfge::Field::call_update (iWidget * widget, const float delta)
{
    widget->update (delta);
}

bool sfge::Field::call_check_key (iWidget * widget, const Event::KeyEvent & e, const bool pressed)
{
    return widget->check_key (e, pressed);
}

void sfge::Field::call_check_text (iWidget * widget, const Event::TextEvent & e)
{
    widget->check_text (e);
}

void sfge::Field::call_check_mouse_button (iWidget * widget, const Event::MouseButtonEvent & e, const bool pressed)
{
    widget->check_mouse_button (e, pressed);
}

void sfge::Field::call_check_wheel (iWidget * widget, const Event::MouseWheelScrollEvent & e)
{
    widget->check_wheel (e);
}

void sfge::Field::call_check_joystick_connect (iWidget * widget, const Event::JoystickConnectEvent & e, const bool connect)
{
    widget->check_joystick_connect (e, connect);
}

void sfge::Field::call_check_joystick (iWidget * widget, const Event::JoystickMoveEvent & e)
{
    widget->check_joystick (e);
}

void sfge::Field::call_check_joystick_button (iWidget * widget, const Event::JoystickButtonEvent & e, const bool pressed)
{
    widget->check_joystick_button (e, pressed);
}

void sfge::Field::call_check_touch (iWidget * widget, const Event::TouchEvent & e)
{
    widget->check_touch (e);
}

void sfge::Field::call_check_sensor (iWidget * widget, const Event::SensorEvent & e)
{
    widget->check_sensor (e);
}

void sfge::Field::call_check_click (iWidget * widget)
{
    widget->check_click ();
}

bool sfge::Field::call_check_mouse (iWidget * widget, const int x, const int y)
{
    return widget->check_mouse (x, y);
}
