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
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
/////////////////////////////////////////////////////////////////////


#pragma once


#include "Frame.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>


namespace sf
{
    class RenderTarget;
}


namespace sfge
{


    using sf::Vector2u;
    using sf::Event;
    using sf::RenderTarget;

    typedef sf::Rect<unsigned> UintRect;


    /////////////////////////////////////////////////////////////////////
    /// iGuiElement - interface for handling events from GUI manager
    ///
    /// This class should not be inherited. Use iWidget instead of it.
    /////////////////////////////////////////////////////////////////////
    class iGuiElement : public Frame
    {
        friend class Field;

    protected:

        /////////////////////////////////////////////////////////////////////
        /// Virtual destructor
        /////////////////////////////////////////////////////////////////////
        virtual ~iGuiElement ();
        
    private:

        /////////////////////////////////////////////////////////////////////
        /// enter - send a signal to start work
        /////////////////////////////////////////////////////////////////////
        virtual void enter () {}

        /////////////////////////////////////////////////////////////////////
        /// leave - send a signal to stop work
        /////////////////////////////////////////////////////////////////////
        virtual void leave () {}

        /////////////////////////////////////////////////////////////////////
        /// is_done - check has widget stoped or not
        ///
        /// @return True if widget has stopped, false otherwise
        /////////////////////////////////////////////////////////////////////
        virtual bool is_done () { return true; }

        /////////////////////////////////////////////////////////////////////
        /// draw - draw widget in RenderTarget
        ///
        /// Has to be overridden.
        ///
        /// @param target is pointer to render target where widget should be drawn
        /////////////////////////////////////////////////////////////////////
        virtual void draw (RenderTarget& target) const = 0;

        /////////////////////////////////////////////////////////////////////
        /// update - handle all processes and animations in widget
        ///
        /// This function is actual for widgets which use animations or which
        /// is interface for some complex processes.
        ///
        /// @param delta - time since last loop
        /////////////////////////////////////////////////////////////////////
        virtual void update (const float delta) {};

        /////////////////////////////////////////////////////////////////////
        /// check_key - handle keystroke
        ///
        /// @param e - description of event
        /// @param pressed - parameter show is key pressed or not
        /////////////////////////////////////////////////////////////////////
        virtual bool check_key (const Event::KeyEvent& e, const bool pressed) { return false; }

        /////////////////////////////////////////////////////////////////////
        /// check_text - handle text input
        ///
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        virtual void check_text (const Event::TextEvent& e) {}

        /////////////////////////////////////////////////////////////////////
        /// check_mouse_button - handle mouse ckick
        ///
        /// @param e - description of event
        /// @param pressed - parameter show is button pressed or not
        /////////////////////////////////////////////////////////////////////
        virtual void check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed) {}

        /////////////////////////////////////////////////////////////////////
        /// check_wheel - handle mouse wheel
        ///
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        virtual void check_wheel (const Event::MouseWheelScrollEvent& e) {}

        /////////////////////////////////////////////////////////////////////
        /// check_joystick_connect - handle joystick connection and
        /// disconnection
        ///
        /// @param e - description of event
        /// @param connect - is joystick connected or not
        /////////////////////////////////////////////////////////////////////
        virtual void check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect) {}

        /////////////////////////////////////////////////////////////////////
        /// check_joystick - handle joystick movement
        ///
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        virtual void check_joystick (const Event::JoystickMoveEvent& e) {}

        /////////////////////////////////////////////////////////////////////
        /// check_joystick_button - handle joystick button click
        ///
        /// @param e - description of event
        /// @param pressed - parameter show is button pressed or not
        /////////////////////////////////////////////////////////////////////
        virtual void check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed) {}

        /////////////////////////////////////////////////////////////////////
        /// check_touch - handle touching
        ///
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        virtual void check_touch (const Event::TouchEvent& e) {}

        /////////////////////////////////////////////////////////////////////
        /// check_sensor - handle sensor
        ///
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        virtual void check_sensor (const Event::SensorEvent& e) {}

        /////////////////////////////////////////////////////////////////////
        /// check_sensor - handle double click 
        /////////////////////////////////////////////////////////////////////
        virtual void check_click () {}

        /////////////////////////////////////////////////////////////////////
        /// check_mouse_button - handle mouse position
        ///
        /// Has to be overridden. Should change view of widget in case of 
        /// mouse focus.
        ///
        /// @param x - coordinate of mouse
        /// @param y - coordinate of mouse
        /// 
        /// @return - true if mouse located above the widget, false otherwise
        /////////////////////////////////////////////////////////////////////
        virtual bool check_mouse (const int x, const int y) = 0;
    };


}