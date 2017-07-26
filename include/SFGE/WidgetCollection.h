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


#pragma once


#include "Config.h"
#include "Field.h"
#include "Widget.h"
#include "Panel.h"
#include "WidgetStyle.h"


namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// iWidgetCollection - interface for widget-collection of another widgets
    /////////////////////////////////////////////////////////////////////
    class iWidgetCollection : public iWidget, public Field
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set texture of background
        /// 
        /// @param texture - pointer to texture
        /////////////////////////////////////////////////////////////////////
        void setBackground (std::shared_ptr<const Texture> texture);

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set texture of background
        /// 
        /// @param texture - name of texture loaded to resource manager
        /////////////////////////////////////////////////////////////////////
        void setBackground (const std::string& texture);

        /////////////////////////////////////////////////////////////////////
        /// setBackground - set color of background
        /// 
        /// @param color - color of background
        /////////////////////////////////////////////////////////////////////
        void setBackground (const Color& color);

        /////////////////////////////////////////////////////////////////////
        /// setItemStyle - set style of items in widget
        ///
        /// @param style - style
        /////////////////////////////////////////////////////////////////////
        void setItemStyle (const WidgetStyle& style);

        /////////////////////////////////////////////////////////////////////
        /// setSpacing - set space between widgets
        /// 
        /// @param space - space
        /////////////////////////////////////////////////////////////////////
        void setSpacing (unsigned space);

        /////////////////////////////////////////////////////////////////////
        /// setFrameOffset - set offset between widgets and borders of widget
        /// 
        /// @param offset - space between widgets and borders
        /////////////////////////////////////////////////////////////////////
        void setBorderOffset (unsigned offset);

        /////////////////////////////////////////////////////////////////////
        /// closeWidget - close widget contained in this collection
        /// 
        /// @param widget - widget to close
        /////////////////////////////////////////////////////////////////////
        virtual void eraseWidget (iWidget* widget) = 0;

    protected:
        const WidgetStyle& getStyle () const;

        uint32_t getSpace () const;
        uint32_t getBorederOffset () const;

        void setFocusedWidget (iWidget* widget);
        iWidget* getFocusedWidget ();

        void setHoveredWidget (iWidget* widget);
        iWidget* getHoveredWidget ();

    private:

        /////////////////////////////////////////////////////////////////////
        /// forEach - exec some actions under all widgets
        ///
        /// Should be overridden.
        ///
        /// @param function - function for executing
        /////////////////////////////////////////////////////////////////////
        virtual void forEach (std::function<bool (iWidget*)> function) const = 0;

        /////////////////////////////////////////////////////////////////////
        /// resizeWidget - recalculate size of all widgets
        ///
        /// Should be overridden.
        /////////////////////////////////////////////////////////////////////
        virtual void resizeWidgets () = 0;

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

    private:
        Panel m_background;

        WidgetStyle m_style = { Position::LEFT | Position::TOP };

        uint32_t m_space = 0;
        uint32_t m_border_offset = 0;

        iWidget* m_focused_widget = nullptr;
        iWidget* m_hovered_widget = nullptr;
    };


}