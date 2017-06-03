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
#include "Widget.h"
#include "Panel.h"
#include "Field.h"


namespace sfge
{


    using sf::Color;
    using sf::Texture;
    using sf::Vector2u;


    /////////////////////////////////////////////////////////////////////
    /// StackedWidget - widget which can contain several other widgets and keep active one of them
    /////////////////////////////////////////////////////////////////////
    class StackedWidget : public iWidget, public Field
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        StackedWidget ();

        /////////////////////////////////////////////////////////////////////
        /// addWidget - this function add widget to stack
        ///
        /// @param widget - pointer to widget
        /// @return return ID of widget
        /////////////////////////////////////////////////////////////////////
        unsigned addWidget (pWidget widget);

        /////////////////////////////////////////////////////////////////////
        /// switchToNext - this function activate widget which is next in stack
        /////////////////////////////////////////////////////////////////////
        void switchToNext ();

        /////////////////////////////////////////////////////////////////////
        /// switchToPrevious - make previous widget active
        /////////////////////////////////////////////////////////////////////
        void switchToPrevious ();

        /////////////////////////////////////////////////////////////////////
        /// setActive - set widget with custom ID active
        ///
        /// @param id - ID of widget
        /////////////////////////////////////////////////////////////////////
        void setActive (unsigned id);

        /////////////////////////////////////////////////////////////////////
        /// closeWidget - remove widget from manager
        ///
        /// @param widget - pointer to widget
        /////////////////////////////////////////////////////////////////////
        void removeWidget (iWidget* widget);

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void enter () override;
        virtual void leave () override;
        virtual bool is_done () override;

        virtual void draw (RenderTarget& target) const override;
        virtual void update (const float delta) override;

        virtual bool check_key (const Event::KeyEvent& e, const bool pressed) override;
        virtual void check_text (const Event::TextEvent& e) override;
        virtual void check_mouse_button (const Event::MouseButtonEvent& e, const bool pressed) override;
        virtual void check_wheel (const Event::MouseWheelScrollEvent& e) override;
        virtual void check_joystick_connect (const Event::JoystickConnectEvent& e, const bool connect) override;
        virtual void check_joystick (const Event::JoystickMoveEvent& e) override;
        virtual void check_joystick_button (const Event::JoystickButtonEvent& e, const bool pressed) override;
        virtual void check_touch (const Event::TouchEvent& e) override;
        virtual void check_sensor (const Event::SensorEvent& e) override;
        virtual void check_click () override;
        virtual bool check_mouse (const int x, const int y) override;


        std::vector<pWidget> m_widgets;
        unsigned m_current_widget = 0;
        bool m_is_enter = false;
    };


}