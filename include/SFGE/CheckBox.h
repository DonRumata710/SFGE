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
    /// CheckBox - clas of check box
    /////////////////////////////////////////////////////////////////////
    class CheckBox : public iWidget
    {
    public:
      
        /////////////////////////////////////////////////////////////////////
        /// ViewType - enumeration of types of view which widget use
        /////////////////////////////////////////////////////////////////////
        enum ViewType
        {
            BACKGROUND,     // background of widget
            FLAG            // view of toggle
        };

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        CheckBox ();

        /////////////////////////////////////////////////////////////////////
        /// attachReaction - attach reaction to changing value
        /// 
        /// @param func - event handler
        /////////////////////////////////////////////////////////////////////
        void attachReaction (const std::function<void ()> func);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to some view of widget
        /// 
        /// @param tex - new texture
        /// @param view - view which will use texture
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::shared_ptr<const Texture> tex, const ViewType view = ViewType::BACKGROUND);

        /////////////////////////////////////////////////////////////////////
        /// attachView - attach texture to some view of widget
        /// 
        /// @param tex - name of texture loaded to resource manager
        /// @param view - view which will use texture
        /////////////////////////////////////////////////////////////////////
        void attachView (const std::string& tex, const ViewType view = ViewType::BACKGROUND);

        /////////////////////////////////////////////////////////////////////
        /// addCollision - add check box which can't be set on in same time 
        /// as this.
        /// 
        /// @param cb - other check box
        /////////////////////////////////////////////////////////////////////
        void addCollision (std::shared_ptr<CheckBox> cb);


        /////////////////////////////////////////////////////////////////////
        /// setState - set check box on or off
        /// 
        /// @param state - true to turn on, false to turn off
        /////////////////////////////////////////////////////////////////////
        void setState (bool state);

        /////////////////////////////////////////////////////////////////////
        /// getState - check is checkbox turned on or off
        /// 
        /// @return true if turn on, false if turn off
        /////////////////////////////////////////////////////////////////////
        bool getState () const;

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void draw (sf::RenderTarget&) const override;
        virtual bool check_key (const sf::Event::KeyEvent&, const bool) override;
        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool pressed) override;
        virtual bool check_mouse (const int x, const int y) override;


        std::function<void ()> m_state_changed;


        Panel m_background;
        Panel m_flag;

        std::vector<std::shared_ptr<CheckBox>> m_collisions;

        bool m_state = false;
    };


}
