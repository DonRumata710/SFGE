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

#include "Widget.h"
#include "Panel.h"


namespace sfge
{


    using sf::Texture;


    /////////////////////////////////////////////////////////////////////
    /// Slider - class of slider
    /////////////////////////////////////////////////////////////////////
    class Slider : public iWidget
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// Orientation - enumeration for orientation of slider
        /////////////////////////////////////////////////////////////////////
        enum Orientation
        {
            VERTICAL,   // vertical placement 
            HORIZONTAL  // horizontal placement
        };

        /////////////////////////////////////////////////////////////////////
        /// Mode - enumeration for mode of slider
        /// 
        /// Note: currently is useless.
        /////////////////////////////////////////////////////////////////////
        enum class Mode
        {
            BAR,
            SLIDER
        };

        /////////////////////////////////////////////////////////////////////
        /// EventType - enumeration of types of events
        /////////////////////////////////////////////////////////////////////
        enum class EventType
        {
            PRESSED,        // the indicator was pressed
            RELEASED,       // the indicator was released
            VALUE_CHANGED   // the indicator was moved
        };

        /////////////////////////////////////////////////////////////////////
        /// View - enumeration of views of the indicator
        /////////////////////////////////////////////////////////////////////
        enum class View
        {
            RELEASED,
            FOCUSED,
            PRESSED
        };

        Slider ();
        virtual	~Slider ();


        /////////////////////////////////////////////////////////////////////
        /// setInterval - set interval of values slider can return
        /// 
        /// @param min - minimal value
        /// @param max - maximum value
        /////////////////////////////////////////////////////////////////////
        void setInterval (const float min, const float max);

        
        /////////////////////////////////////////////////////////////////////
        /// setMode - set mode of slider
        /// 
        /// Note: currently is useless
        /////////////////////////////////////////////////////////////////////
        void setMode (const Mode);

        /////////////////////////////////////////////////////////////////////
        /// setOrientation - set orientation of slider
        /// 
        /// @param orientation - new orientation
        /////////////////////////////////////////////////////////////////////
        void setOrientation (const Orientation orientation);

        /////////////////////////////////////////////////////////////////////
        /// attachBackground - set background of slider
        /// 
        /// @param tex - new texture
        /////////////////////////////////////////////////////////////////////
        void attachBackground (const std::shared_ptr<const Texture> tex);

        /////////////////////////////////////////////////////////////////////
        /// attachSlider - set texture to some of views of slider indicator
        /// 
        /// @param tex - new texture
        /// @param view - type of indicator view
        /////////////////////////////////////////////////////////////////////
        void attachSlider (const std::shared_ptr<const Texture> tex, const View view = View::RELEASED);

        /////////////////////////////////////////////////////////////////////
        /// attachReaction - attach function to handle some event
        ///
        /// @param func - function wich handle this event
        /// @param e - event description
        /////////////////////////////////////////////////////////////////////
        void attachReaction (const std::function<void ()>, const EventType);

        /////////////////////////////////////////////////////////////////////
        /// setValue - set current value of slider
        /// 
        /// @param value - new value
        /////////////////////////////////////////////////////////////////////
        void setValue (const float value);

        /////////////////////////////////////////////////////////////////////
        /// getValue - get current value of slider
        /// 
        /// @return current value
        /////////////////////////////////////////////////////////////////////
        float getValue () const;

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool) override;
        virtual bool check_mouse (const int x, const int y) override;

        virtual void draw (sf::RenderTarget&) const override;

        void calc_slider_position ();

        void set_view (const View type);

        std::function<void ()> m_pressed;
        std::function<void ()> m_released;
        std::function<void ()> m_value_changed;

        Orientation m_orient = VERTICAL;
        Mode m_mode = Mode::SLIDER;

        std::shared_ptr<const sf::Texture> m_released_slider;
        std::shared_ptr<const sf::Texture> m_focused_slider;
        std::shared_ptr<const sf::Texture> m_pressed_slider;

        Panel m_outward_view;
        Panel m_slider;

        float m_min = 1.0f;
        float m_max = 0.0f;
        float m_value = 0.0f;

        bool m_is_pressed = false;
        sf::Vector2i m_mouse;
    };


}
