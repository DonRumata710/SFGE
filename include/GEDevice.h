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

#include "GuiManager.h"
#include "Unicode.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <unordered_map>



namespace sfge
{


    class ResourceManager;


    using sf::Window;
    using sf::VideoMode;
    using sf::ContextSettings;


    /////////////////////////////////////////////////////////////////////
    /// Style - namespace for styles of window
    /// 
    /// All styles has taken from SFML.
    /////////////////////////////////////////////////////////////////////
    namespace Style
    {

        using sf::Style::Default;
        using sf::Style::None;
        using sf::Style::Titlebar;
        using sf::Style::Resize;
        using sf::Style::Close;
        using sf::Style::Fullscreen;

    }

    
    /////////////////////////////////////////////////////////////////////
    /// Game Engine Device - main class in game engine
    ///
    /// This class manage windows and GUI.
    /////////////////////////////////////////////////////////////////////
    class GEDevice
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// getInstance - get instance of created device
        /// 
        /// GE device should be created only once. Then you can use this
        /// function to get pointer to it.
        /// 
        /// @return pointer to device or nullptr if device wasn't created
        /////////////////////////////////////////////////////////////////////
        static GEDevice* getInstance ();

        /////////////////////////////////////////////////////////////////////
        /// default constructor - create GE device
        /////////////////////////////////////////////////////////////////////
        GEDevice ();

        ~GEDevice ();

        /////////////////////////////////////////////////////////////////////
        /// setResourceManager - add resource manager to device
        ///
        /// @param resources - pointer to resource manager
        /////////////////////////////////////////////////////////////////////
        void setResourceManager (std::shared_ptr<ResourceManager> resources);

        /////////////////////////////////////////////////////////////////////
        /// getResourceManager - get resource manager of GE device
        /// 
        /// @return pointer to resource manager
        /////////////////////////////////////////////////////////////////////
        std::shared_ptr<ResourceManager> getResourceManager ();

        /////////////////////////////////////////////////////////////////////
        /// createWindow create window and show it
        ///
        /// This constructor creates the window with the size and pixel
        /// depth defined in \a mode. An optional style can be passed to
        /// customize the look and behavior of the window (borders,
        /// title bar, resizable, closable, ...).
        ///
        /// The fourth parameter is an optional structure specifying
        /// advanced OpenGL context settings such as antialiasing,
        /// depth-buffer bits, etc. You shouldn't care about these
        /// parameters for a regular usage of the graphics module.
        ///
        /// @param id - id of GUI manager which will be shown
        /// @param title - title of window
        /// @param vmode - parameters of screen of window
        /// @param style - style of window
        /// @param settings - additional settings for the underlying OpenGL context
        /////////////////////////////////////////////////////////////////////
        bool createWindow (const unsigned id, const UString& title, const VideoMode& vmode, const uint32_t style = Style::Default, const ContextSettings settings = ContextSettings ());
        
        /////////////////////////////////////////////////////////////////////
        /// addGuiManager - add GUI manager to device
        ///
        /// @param id - id of GUI manager
        /// @param gui - pointer to GUI manager
        /////////////////////////////////////////////////////////////////////
        void addGuiManager (unsigned id, pGUIManager& gui);

        /////////////////////////////////////////////////////////////////////
        /// getGuiManager - get pointer to GUI manager
        ///
        /// @param id - id of GUI
        ///
        /// @return - pointer to GUI
        /////////////////////////////////////////////////////////////////////
        GUIManager* getGUIManager (unsigned id);
        
        /////////////////////////////////////////////////////////////////////
        /// run - start main loop of application
        /////////////////////////////////////////////////////////////////////
        int run ();

        /////////////////////////////////////////////////////////////////////
        /// quit - send for all opened windows signal to close themselves
        /////////////////////////////////////////////////////////////////////
        void quit ();

    private:
        std::unordered_map<unsigned, pGUIManager> m_managers;
        std::unordered_map<UString, GUIManager*> m_active;

        std::shared_ptr<ResourceManager> m_resource_manager;

        int m_next;

        static GEDevice* m_device;
    };



}
