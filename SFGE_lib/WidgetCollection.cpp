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


#include "WidgetCollection.h"
#include "GuiManager.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"


using namespace sfge;


void iWidgetCollection::setBackground (std::shared_ptr<const sf::Texture> texture)
{
    m_background.setTexture (texture);
}

void iWidgetCollection::setBackground (const std::string& texture)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setBackground (rm->findTexture (texture));
}

void iWidgetCollection::setBackground (const Color& color)
{
    m_background.setColor (color);
}

void iWidgetCollection::setItemStyle (const WidgetStyle& style)
{
    m_style = style;
    m_style.setPosition (Position::LEFT | Position::TOP);
    forEach ([this](iWidget* w) { m_style.attach (w); return true; });
}

void iWidgetCollection::setSpacing (unsigned space)
{
    m_space = space;
    resizeWidgets ();
}

void iWidgetCollection::setBorderOffset (unsigned offset)
{
    m_border_offset = offset;
    resizeWidgets ();
}

const WidgetStyle& iWidgetCollection::getStyle () const
{
    return m_style;
}

uint32_t iWidgetCollection::getSpace () const
{
    return m_space;
}

uint32_t iWidgetCollection::getBorederOffset () const
{
    return m_border_offset;
}

void iWidgetCollection::setFocusedWidget (iWidget* widget)
{
    m_focused_widget = widget;
}

iWidget* iWidgetCollection::getFocusedWidget ()
{
    return m_focused_widget;
}

void iWidgetCollection::setHoveredWidget (iWidget* widget)
{
    m_hovered_widget = widget;
}

iWidget* iWidgetCollection::getHoveredWidget ()
{
    return m_hovered_widget;
}

void iWidgetCollection::setRect (const PositionDesc& desc)
{
    set_position_desc (desc);

    m_background.setPosition (desc.x, desc.y);
    m_background.setSize (desc.width, desc.height);

    resizeWidgets ();
}

void iWidgetCollection::enter ()
{
    forEach ([this](iWidget* w) { call_enter (w); return true; });
}

void iWidgetCollection::leave ()
{
    forEach ([this](iWidget* w) { call_leave (w); return true; });
}

bool iWidgetCollection::is_done ()
{
    bool flag = true;
    forEach ([this, &flag](iWidget* w) {
        if (!call_is_done (w))
        {
            flag = false;
            return false;
        }
        return true;
    });
    return flag;
}

void iWidgetCollection::draw (RenderTarget& target) const
{
    target.draw (m_background);

    forEach ([this, &target](iWidget* w) { if (w->isVisible ()) call_draw (w, target); return true; });
}

void iWidgetCollection::update (const float delta)
{
    forEach ([this, delta](iWidget* w) { call_update (w, delta); return true; });
}

bool iWidgetCollection::check_key (const Event::KeyEvent& e, const bool pressed)
{
    return call_check_key (m_focused_widget, e, pressed);
}

void iWidgetCollection::check_text (const Event::TextEvent& e)
{
    call_check_text (m_focused_widget, e);
}

void iWidgetCollection::check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed)
{
    call_check_mouse_button (m_hovered_widget, e, pressed);
}

void iWidgetCollection::check_wheel (const Event::MouseWheelScrollEvent& e)
{
    call_check_wheel (m_focused_widget, e);
}

void iWidgetCollection::check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect)
{
    call_check_joystick_connect (m_hovered_widget, e, connect);
}

void iWidgetCollection::check_joystick (const Event::JoystickMoveEvent& e)
{
    call_check_joystick (m_hovered_widget, e);
}

void iWidgetCollection::check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed)
{
    call_check_joystick_button (m_hovered_widget, e, pressed);
}

void iWidgetCollection::check_touch (const Event::TouchEvent& e)
{
    call_check_touch (m_hovered_widget, e);
}

void iWidgetCollection::check_sensor (const Event::SensorEvent& e)
{
    call_check_sensor (m_hovered_widget, e);
}

void iWidgetCollection::check_click ()
{
    call_check_click (m_hovered_widget);
    m_focused_widget = m_hovered_widget;
}

bool iWidgetCollection::check_mouse (const int x, const int y)
{
    bool flag = false;
    iWidget* widget (nullptr);
    forEach ([this, &flag, x, y, &widget](iWidget* w) {
        if (call_check_mouse (w, x, y))
        {
            widget = w;
            flag = true;
            return false;
        }
        return true;
    });
    return flag;
}