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

#include "Field.h"
#include "Frame.h"
#include "Widget.h"
#include "Panel.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <functional>



namespace sfge
{


    using sf::Window;
    using sf::Vector2u;
    using sf::RenderWindow;
    using sf::Texture;

    class GEDevice;


    /////////////////////////////////////////////////////////////////////
    /// GUIManager - class for managing widgets
    /////////////////////////////////////////////////////////////////////
    class GUIManager : public Field
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// constructor - create an instance of class GUIManager
        ///
        /// @param device - pointer to device which will use GUI
        /////////////////////////////////////////////////////////////////////
        GUIManager (GEDevice* device);

        /////////////////////////////////////////////////////////////////////
        /// addFrontWidget - add widget to the front of the screen which is
        /// managed by current manager
        ///
        /// Widget will be shown on top of other widgets.
        ///
        /// @param pWidget - pointer to widget
        /////////////////////////////////////////////////////////////////////
        void addFrontWidget (pWidget);

        /////////////////////////////////////////////////////////////////////
        /// addFrontWidget - add widget to the background of the screen which is
        /// managed by current manager
        ///
        /// Widget will be shown under the other widgets.
        ///
        /// @param pWidget - pointer to widget
        /////////////////////////////////////////////////////////////////////
        void addBackWidget (pWidget);

        /////////////////////////////////////////////////////////////////////
        /// addWidget - add widget to the screen which is managed 
        /// by current object
        ///
        /// @param pWidget - pointer to widget
        /////////////////////////////////////////////////////////////////////
        void setBackground (std::shared_ptr<const Texture>);

        /////////////////////////////////////////////////////////////////////
        /// setFocusLocked - let focus move or not
        ///
        /// If focus is unlocked pressing the tab key move focus on  other
        /// widget by loop.
        ///
        /// @param lock - if true - focus is locked, false - focus is unlocked
        /////////////////////////////////////////////////////////////////////
        void setFocusLocked (bool lock);

        /////////////////////////////////////////////////////////////////////
        /// update - check mouse, keyboard and joystick events
        ///
        /// Should been called in main loop.
        ///
        /// @return return false if gui is inactive, in all other cases return true
        /////////////////////////////////////////////////////////////////////
        bool update ();

        /////////////////////////////////////////////////////////////////////
        /// draw - draw GUI
        ///
        /// Should be called in main loop
        /////////////////////////////////////////////////////////////////////
        void draw () const;

        /////////////////////////////////////////////////////////////////////
        /// enter - start GUI
        ///
        /// Should been called when gui begin active.
        ///
        /// @param window - pointer to window where GUI should be shown
        /////////////////////////////////////////////////////////////////////
        void enter (std::unique_ptr<RenderWindow>& window);

        /////////////////////////////////////////////////////////////////////
        /// leave - send commands for widgets to close themselves
        ///
        /// Should been called when GUI begin inactive.
        /////////////////////////////////////////////////////////////////////
        void leave ();

        /////////////////////////////////////////////////////////////////////
        /// isActive - show is GUI active or not
        ///
        /// Show that GUI is not inactive.
        ///
        /// @return true if GUI is active and false if not
        /////////////////////////////////////////////////////////////////////
        bool isActive () const;

        /////////////////////////////////////////////////////////////////////
        /// setSwitch - set id of next GUI
        ///
        /// @param id - id of GUI
        /////////////////////////////////////////////////////////////////////
        void setSwitch (int id);

        /////////////////////////////////////////////////////////////////////
        /// getSwitch - return next GUI
        ///
        /// @return return id of GUI or negative value for exit
        /////////////////////////////////////////////////////////////////////
        int getSwitch ();

        /////////////////////////////////////////////////////////////////////
        /// getWindow - return window for next GUI
        ///
        /// After calling this function GUI can lose control over window. So this
        /// function shoud be used carefully.
        ///
        /// @return return unique pointer to window
        /////////////////////////////////////////////////////////////////////
        std::unique_ptr<RenderWindow>& getWindow ();


    private:
        enum class State
        {
            ENTER,
            LEAVE,
            INACTIVE,
            ACTIVE
        };


        bool handle_event (const Event& e);

        void find_focus (const Event::KeyEvent& key);

        std::vector<pWidget>::iterator find_widget_iter (const iWidget*);


        std::vector<pWidget> m_widgets;

        std::unique_ptr<RenderWindow> m_window;

        pWidget m_focused_widget = nullptr;
        bool m_focus_locked = false;

        pWidget m_over_widget = nullptr;

        State m_state = State::ACTIVE;

        sf::Clock m_timer;

        int m_switch = 0;

        Panel m_background;

        GEDevice* m_device;

        bool m_release = false;
        float m_click_timer = 0.0f;
    };

    typedef std::unique_ptr<GUIManager> pGUIManager;

}
