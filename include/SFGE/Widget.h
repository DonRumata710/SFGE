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

#include "GuiElement.h"
#include "Frame.h"

#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>



namespace sfge
{



    class GUIManager;


    /////////////////////////////////////////////////////////////////////
    /// iWidget - interface for common widgets interface.
    ///
    /// This abstract class should be inherited to realize custom widget.
    /////////////////////////////////////////////////////////////////////
    class iWidget : public iGuiElement
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Default constructor - do nothing
        /////////////////////////////////////////////////////////////////////
        iWidget () {}

        /////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////
        virtual ~iWidget () {}

        /////////////////////////////////////////////////////////////////////
        /// isVisible - check the visibility of widget
        ///
        /// @return True if widget is visible, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isVisible () const;

        /////////////////////////////////////////////////////////////////////
        /// isVisible - check isthe widget static
        /// 
        /// Static widget can't get keyboard events.
        ///
        /// @return True if widget is static, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isStatic () const;

        /////////////////////////////////////////////////////////////////////
        /// isEnabled - check is the widget enabled
        /// 
        /// Widget is disable to handle events if it is displaying some
        /// animation of previous events.
        ///
        /// @return True if widget is enabled, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isEnabled () const;

        /////////////////////////////////////////////////////////////////////
        /// setVisible - set visibility of widget
        /// 
        /// @param flag - describe should widget be visible or not
        /////////////////////////////////////////////////////////////////////
        void setVisible (bool flag);

        /////////////////////////////////////////////////////////////////////
        /// setStatic - set widget static or dinamic
        ///
        /// @param flag - describe status of widget
        /////////////////////////////////////////////////////////////////////
        void setStatic (bool flag);

        /////////////////////////////////////////////////////////////////////
        /// setEnabled - set widget enabled or disabled
        ///
        /// @param flag - describe is widget enabled
        /////////////////////////////////////////////////////////////////////
        void setEnabled (bool flag);

    private:
        bool m_visible = true;
        bool m_static = false;
        bool m_enabled = true;
    };


    typedef std::shared_ptr<iWidget> pWidget;

    
}