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
#include "Widget.h"
#include "Unicode.h"

#include <SFML/Graphics/Text.hpp>



namespace sfge
{


    using sf::Font;
    using sf::Color;
    using sf::RenderTarget;
    using sf::Text;


    /////////////////////////////////////////////////////////////////////
    /// Label is simple text drawn over the window
    /////////////////////////////////////////////////////////////////////
    class Label : public iWidget
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Position - enum for describing position of widget on the screen
        ///
        /// Values which describe horizontal align and vertial align should 
        /// be mixed for correct positioning. Each value describe one 
        /// alignment object. Location of widget will be measured from this
        /// object.
        /////////////////////////////////////////////////////////////////////
        enum Align : int
        {
            HCENTER = 0,
            LEFT = 1,
            RIGHT = 2,
            WIDTH = 3,
            VCENTER = 0,
            TOP = 4,
            BOTTOM = 8,
            HEIGHT = 12,
        };

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        Label ();

        /////////////////////////////////////////////////////////////////////
        /// setString set string that will be drown on the window
        ///
        /// @parameter string - string to draw
        /////////////////////////////////////////////////////////////////////
        void setString (const UString& string);

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::shared_ptr<const Font> font);

        /////////////////////////////////////////////////////////////////////
        /// setFont set font, which will be drawn text
        ///
        /// @parameter font - loaded font
        /////////////////////////////////////////////////////////////////////
        void setFont (const std::string& font);

        /////////////////////////////////////////////////////////////////////
        /// setCharacterSize set size of text
        ///
        /// @parameter size - size of characters in pixels
        /////////////////////////////////////////////////////////////////////
        void setCharacterSize (const unsigned size);

        /////////////////////////////////////////////////////////////////////
        /// setTextColor - set color of text in widget
        /// 
        /// @param color - new color
        /////////////////////////////////////////////////////////////////////
        void setTextColor (Color color);

        /////////////////////////////////////////////////////////////////////
        /// setAlign - set align of text
        ///
        /// @param align - value of align
        /////////////////////////////////////////////////////////////////////
        void setAlign (Align align);

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual bool check_mouse (const int x, const int y) override;

        virtual void draw (RenderTarget&) const override;

        Text m_text;
        Align m_align = (Align) (LEFT | TOP);
    };


}