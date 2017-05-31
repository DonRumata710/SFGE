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


#include "Config.h"
#include "Frame.h"
#include "GuiElement.h"

#include <SFML/System/Vector2.hpp>

#include <vector>



namespace sfge
{


    using sf::Vector2i;
    using sf::Vector2u;

    class iWidget;


    /////////////////////////////////////////////////////////////////////
    /// Field - object which controls size of widgets attached to it
    ///
    /// This class is abstraction for screen and other containers of
    /// widgets. It control widgets by frame interface.
    /////////////////////////////////////////////////////////////////////
    class Field
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Default contructor
        /////////////////////////////////////////////////////////////////////
        Field ();

        /////////////////////////////////////////////////////////////////////
        /// Virtual destructor
        /////////////////////////////////////////////////////////////////////
        virtual ~Field ();

        /////////////////////////////////////////////////////////////////////
        /// getPosition - get position of field on window
        ///
        /// @return - position of field
        /////////////////////////////////////////////////////////////////////
        Vector2i getPosition () const;

        /////////////////////////////////////////////////////////////////////
        /// getSize - get size of field
        ///
        /// @return - size of field
        /////////////////////////////////////////////////////////////////////
        Vector2u getSize () const;

        /////////////////////////////////////////////////////////////////////
        /// getPositionDesc - get description of position and size of field
        ///
        /// @return - position descriptor of field
        /////////////////////////////////////////////////////////////////////
        const PositionDesc& getPositionDesc () const;

    protected:

        /////////////////////////////////////////////////////////////////////
        /// add_frame - place frame into the field
        ///
        /// @param frame - pointer to frame
        /////////////////////////////////////////////////////////////////////
        void add_frame (Frame* frame);

        /////////////////////////////////////////////////////////////////////
        /// remove_frame - remove frame from field
        ///
        /// @param frame - pointer to frame
        /////////////////////////////////////////////////////////////////////
        void remove_frame (Frame* frame);

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of field
        ///
        /// @param size - size of filed
        /////////////////////////////////////////////////////////////////////
        void set_size (Vector2u size);

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of field
        ///
        /// @param size - size of filed
        /////////////////////////////////////////////////////////////////////
        void set_size (unsigned width, unsigned height);

        /////////////////////////////////////////////////////////////////////
        /// set_position - set position of field on window
        ///
        /// @param position - position of field
        /////////////////////////////////////////////////////////////////////
        void set_position (Vector2i position);

        /////////////////////////////////////////////////////////////////////
        /// set_position - set position of field on window
        ///
        /// @param desc - position description
        /////////////////////////////////////////////////////////////////////
        void set_position_desc (const PositionDesc& desc);

    protected:

        /////////////////////////////////////////////////////////////////////
        /// call_enter - send a signal to start work
        ///
        /// @param widget - activated widget
        /////////////////////////////////////////////////////////////////////
        void call_enter (iWidget* widget);

        /////////////////////////////////////////////////////////////////////
        /// call_leave - send a signal to stop work
        ///
        /// @param widget - disactivated widget
        /////////////////////////////////////////////////////////////////////
        void call_leave (iWidget* widget);

        /////////////////////////////////////////////////////////////////////
        /// call_is_done - check has widget stoped or not
        ///
        /// @param widget - widget which state should be checked
        /// 
        /// @return True if widget has stopped, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool call_is_done (iWidget* widget);


        /////////////////////////////////////////////////////////////////////
        /// call_draw - draw widget in RenderTarget
        ///
        /// Has to be overridden.
        ///
        /// @param widget - drawn widget
        /// @param target is pointer to render target where widget should be drawn
        /////////////////////////////////////////////////////////////////////
        void call_draw (iWidget* widget, RenderTarget& target) const;

        /////////////////////////////////////////////////////////////////////
        /// call_update - handle all processes and animations in widget
        ///
        /// This function is actual for widgets which use animations or which
        /// is interface for some complex processes.
        ///
        /// @param widget - updated widget
        /// @param delta - time since last loop
        /////////////////////////////////////////////////////////////////////
        void call_update (iWidget* widget, const float delta);


        /////////////////////////////////////////////////////////////////////
        /// call_check_key - handle keystroke
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /// @param pressed - parameter show is key pressed or not
        /////////////////////////////////////////////////////////////////////
        bool call_check_key (iWidget* widget, const Event::KeyEvent& e, const bool pressed);

        /////////////////////////////////////////////////////////////////////
        /// call_check_text - handle text input
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        void call_check_text (iWidget* widget, const Event::TextEvent& e);

        /////////////////////////////////////////////////////////////////////
        /// call_check_mouse_button - handle mouse ckick
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /// @param pressed - parameter show is button pressed or not
        /////////////////////////////////////////////////////////////////////
        void call_check_mouse_button (iWidget* widget, const Event::MouseButtonEvent& e, const bool pressed);

        /////////////////////////////////////////////////////////////////////
        /// call_check_wheel - handle mouse wheel
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        void call_check_wheel (iWidget* widget, const Event::MouseWheelScrollEvent& e);

        /////////////////////////////////////////////////////////////////////
        /// call_check_joystick_connect - handle joystick connection and
        /// disconnection
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /// @param connect - is joystick connected or not
        /////////////////////////////////////////////////////////////////////
        void call_check_joystick_connect (iWidget* widget, const Event::JoystickConnectEvent& e, const bool connect);

        /////////////////////////////////////////////////////////////////////
        /// call_check_joystick - handle joystick movement
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        void call_check_joystick (iWidget* widget, const Event::JoystickMoveEvent& e);

        /////////////////////////////////////////////////////////////////////
        /// call_check_joystick_button - handle joystick button click
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /// @param pressed - parameter show is button pressed or not
        /////////////////////////////////////////////////////////////////////
        void call_check_joystick_button (iWidget* widget, const Event::JoystickButtonEvent& e, const bool pressed);

        /////////////////////////////////////////////////////////////////////
        /// call_check_touch - handle touching
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        void call_check_touch (iWidget* widget, const Event::TouchEvent& e);

        /////////////////////////////////////////////////////////////////////
        /// call_check_sensor - handle sensor
        ///
        /// @param widget - widget which should be checked
        /// @param e - description of event
        /////////////////////////////////////////////////////////////////////
        void call_check_sensor (iWidget* widget, const Event::SensorEvent& e);

        /////////////////////////////////////////////////////////////////////
        /// call_check_sensor - handle double click 
        ///
        /// @param widget - widget which should be checked
        /////////////////////////////////////////////////////////////////////
        void call_check_click (iWidget* widget);

        /////////////////////////////////////////////////////////////////////
        /// call_check_mouse - handle mouse position
        ///
        /// Has to be overridden. Should change view of widget in case of 
        /// mouse focus.
        ///
        /// @param widget - widget which should be checked
        /// @param x - coordinate of mouse
        /// @param y - coordinate of mouse
        /// 
        /// @return - true if mouse located above the widget, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool call_check_mouse (iWidget* widget, const int x, const int y);

    private:
        std::vector<Frame*> m_frames;
        PositionDesc m_position;
    };


}