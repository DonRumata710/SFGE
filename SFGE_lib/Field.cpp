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


using namespace sfge;


Field::Field ()
{}

Field::~Field ()
{}

Vector2i Field::getPosition () const
{
    return { m_position.x, m_position.y };
}

Vector2u Field::getSize () const
{
    return { m_position.width, m_position.height };
}

const PositionDesc& Field::getPositionDesc () const
{
    return m_position;
}

void Field::add_frame (Frame* frame)
{
    m_frames.push_back (frame);
    frame->setField (this);
    if (m_position.width)
        frame->setFieldParam (m_position);
}

void Field::remove_frame (Frame* frame)
{
    m_frames.erase (std::remove (m_frames.begin (), m_frames.end (), frame));
}

void Field::set_size (Vector2u size)
{
    m_position.width = size.x;
    m_position.height = size.y;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void Field::set_size (unsigned width, unsigned height)
{
    m_position.width = width;
    m_position.height = height;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void Field::set_position (Vector2i position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}

void Field::set_position_desc (const PositionDesc& desc)
{
    m_position = desc;
    for (Frame* frame : m_frames)
        frame->setFieldParam (m_position);
}



void Field::call_enter (iWidget* widget)
{
    widget->enter ();
}

void Field::call_leave (iWidget * widget)
{
    widget->leave ();
}

bool Field::call_is_done (iWidget * widget)
{
    return widget->is_done ();
}

void Field::call_draw (iWidget * widget, RenderTarget & target) const
{
    widget->draw (target);
}

void Field::call_update (iWidget * widget, const float delta)
{
    widget->update (delta);
}

bool Field::call_check_key (iWidget * widget, const Event::KeyEvent & e, const bool pressed)
{
    return widget->check_key (e, pressed);
}

void Field::call_check_text (iWidget * widget, const Event::TextEvent & e)
{
    widget->check_text (e);
}

void Field::call_check_mouse_button (iWidget * widget, const Event::MouseButtonEvent & e, const bool pressed)
{
    widget->check_mouse_button (e, pressed);
}

void Field::call_check_wheel (iWidget * widget, const Event::MouseWheelScrollEvent & e)
{
    widget->check_wheel (e);
}

void Field::call_check_joystick_connect (iWidget * widget, const Event::JoystickConnectEvent & e, const bool connect)
{
    widget->check_joystick_connect (e, connect);
}

void Field::call_check_joystick (iWidget * widget, const Event::JoystickMoveEvent & e)
{
    widget->check_joystick (e);
}

void Field::call_check_joystick_button (iWidget * widget, const Event::JoystickButtonEvent & e, const bool pressed)
{
    widget->check_joystick_button (e, pressed);
}

void Field::call_check_touch (iWidget * widget, const Event::TouchEvent & e)
{
    widget->check_touch (e);
}

void Field::call_check_sensor (iWidget * widget, const Event::SensorEvent & e)
{
    widget->check_sensor (e);
}

void Field::call_check_click (iWidget * widget)
{
    widget->check_click ();
}

bool Field::call_check_mouse (iWidget * widget, const int x, const int y)
{
    return widget->check_mouse (x, y);
}
