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


#include "GridBox.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


GridBox::GridBox ()
{}

void GridBox::setRect (const PositionDesc& desc)
{
    set_position_desc (desc);

    m_background.setPosition (desc.x, desc.y);
    m_background.setSize (desc.width, desc.height);

    resize_widgets ();
}

void GridBox::setRowsCount (unsigned rows)
{
    m_rows = rows;
}

void GridBox::setColumnsCount (unsigned columns)
{
    m_columns = columns;
}

void GridBox::addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row)
{
    if (column >= m_columns || row >= m_rows)
    {
        runtime_message ("Grid box is out of range");
        return;
    }

    m_widgets[row * m_columns + column] = widget;
    widget->setPosition (Position::TOP | Position::LEFT);
    add_frame (widget.get ());
}

void GridBox::addWidget (std::shared_ptr<iWidget> widget, unsigned column, unsigned row, unsigned sec_column, unsigned sec_row)
{
    if (column >= m_columns || row >= m_rows || sec_column >= m_columns || sec_row >= m_rows) return;

    m_widgets[row * m_columns + column] = widget;
    m_widgets[row * m_columns + column].size = ((column - sec_column) & 0xFFFF) | ((row - sec_row) << 16);
    widget->setPosition (Position::TOP | Position::LEFT);
    add_frame (widget.get ());
}

void GridBox::setBackground (std::shared_ptr<const sf::Texture> texture)
{
    m_background.setTexture (texture);
}

void GridBox::setBackground (const std::string& texture)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setBackground (rm->findTexture (texture));
}

void GridBox::setBackground (const Color& color)
{
    m_background.setColor (color);
}

void GridBox::closeWidget (iWidget* widget)
{
    for (auto w : m_widgets)
    {
        if (w.second.widget.get () == widget)
        {
            call_leave (widget);
            m_widgets.erase (w.first);
        }
    }
}

void GridBox::setSpacing (unsigned space)
{
    m_space = space;
    resize_widgets ();
}

void GridBox::setBorderOffset (unsigned offset)
{
    m_border_offset = offset;
    resize_widgets ();
}

void GridBox::enter ()
{
    for (auto w : m_widgets)
        call_enter (w.second.widget.get ());
}

void GridBox::leave ()
{
    for (auto w : m_widgets)
        call_leave (w.second.widget.get ());
}

bool GridBox::is_done ()
{
    for (auto w : m_widgets)
    {
        if (!call_is_done (w.second.widget.get ()))
            return false;
    }
    return true;
}

void GridBox::draw (RenderTarget& target) const
{
    target.draw (m_background);

    for (auto w : m_widgets)
    {
        if (w.second.widget->isVisible ())
            call_draw (w.second.widget.get (), target);
    }
}

void GridBox::update (const float delta)
{
    for (auto w : m_widgets)
        call_update (w.second.widget.get (), delta);
}

bool GridBox::check_key (const Event::KeyEvent& e, const bool pressed)
{
    for (auto w : m_widgets)
    {
        if (call_check_key (w.second.widget.get (), e, pressed))
            return true;
    }
    return false;
}

void GridBox::check_text (const Event::TextEvent& e)
{
    for (auto w : m_widgets)
        call_check_text (w.second.widget.get (), e);
}

void GridBox::check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed)
{
    for (auto w : m_widgets)
        call_check_mouse_button (w.second.widget.get (), e, pressed);
}

void GridBox::check_wheel (const Event::MouseWheelScrollEvent& e)
{
    for (auto w : m_widgets)
        call_check_wheel (w.second.widget.get (), e);
}

void GridBox::check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect)
{
    for (auto w : m_widgets)
       call_check_joystick_connect (w.second.widget.get (), e, connect);
}

void GridBox::check_joystick (const Event::JoystickMoveEvent& e)
{
    for (auto w : m_widgets)
        call_check_joystick (w.second.widget.get (), e);
}

void GridBox::check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed)
{
    for (auto w : m_widgets)
        call_check_joystick_button (w.second.widget.get (), e, pressed);
}

void GridBox::check_touch (const Event::TouchEvent& e)
{
    for (auto w : m_widgets)
        call_check_touch (w.second.widget.get (), e);
}

void GridBox::check_sensor (const Event::SensorEvent& e)
{
    for (auto w : m_widgets)
        call_check_sensor (w.second.widget.get (), e);
}

void GridBox::check_click ()
{
    for (auto w : m_widgets)
        call_check_click (w.second.widget.get ());
}

bool GridBox::check_mouse (const int x, const int y)
{
    for (auto w : m_widgets)
    {
        if (call_check_mouse (w.second.widget.get (), x, y))
            return true;
    }
    return false;
}

void GridBox::resize_widgets ()
{
    unsigned width  ((m_background.getSize ().x - m_border_offset * 2) / m_columns);
    unsigned height ((m_background.getSize ().y - m_border_offset * 2) / m_rows);

    for (unsigned i = 0; i < m_rows; ++i)
    {
        for (unsigned j = 0; j < m_columns; ++j)
        {
            if (m_widgets.find (i * m_columns + j) == m_widgets.end ())
                continue;

            m_widgets[i * m_columns + j].widget->setPosition (
                m_space / 2 + m_background.getPosition ().x + m_border_offset + width * j,
                m_space / 2 + m_background.getPosition ().y + m_border_offset + height * i
            );

            m_widgets[i * m_columns + j].widget->setSize (
                width * (m_widgets[i * m_columns + j].size & 0xFFFF) - m_space,
                height * (m_widgets[i * m_columns + j].size >> 16) - m_space
            );
        }
    }
}
