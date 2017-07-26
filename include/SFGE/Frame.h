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

#include <SFML/System/Vector2.hpp>


namespace sfge
{


    class Field;

    using sf::Vector2i;
    using sf::Vector2u;


    /////////////////////////////////////////////////////////////////////
    /// PositionDesc - description of position and size of fields and widgets
    /////////////////////////////////////////////////////////////////////
    struct PositionDesc
    {
        int32_t x = 0;        // right border of object
        int32_t y = 0;        // top border of object
        uint32_t width = 0;   // width of object
        uint32_t height = 0;  // height of object

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        PositionDesc () {}

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param x - x coord of top left corner
        /// @param y - y coord of top left corner
        /// @param width - width of widget
        /// @param height - height of widget
        /////////////////////////////////////////////////////////////////////
        PositionDesc (int32_t _x, int32_t _y, uint32_t _width, uint32_t _height) :
            x (_x), y (_y), width (_width), height (_height)
        {}

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param pos - position of widget
        /// @param size - size of widget
        /////////////////////////////////////////////////////////////////////
        PositionDesc (const Vector2i& pos, const Vector2u& size) :
            x (pos.x), y (pos.y), width (size.x), height (pos.y)
        {}
    };


    /////////////////////////////////////////////////////////////////////
    /// Frame - object for size control of widgets on the screen
    /////////////////////////////////////////////////////////////////////
    class Frame
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Position - enum for describing position of widget on the screen
        ///
        /// Values which describe horizontal position and vertial position
        /// should be mixed for correct positioning. Each value describe one
        /// alignment object. Location of widget will be measured from this
        /// object.
        /////////////////////////////////////////////////////////////////////
        enum Position : uint32_t
        {
            HCENTER = 0,    // center horizontally
            LEFT = 1,       // bind to the left
            RIGHT = 2,      // bind to the right
            WIDTH = 3,      // stretch in width
            VCENTER = 0,    // center vertically
            TOP = 4,        // bind to the top
            BOTTOM = 8,     // bind to the bottom
            HEIGHT = 12,    // stretch in height
        };


        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position describe alignment of the widget
        /// @param x_offset - axial distance x between alignment object and widget
        /// @param y_offset - axial distance y between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position, const int32_t x_offset, const int32_t y_offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position describe alignment of the widget
        /// @param offset - distance between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position, const Vector2i offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        /// 
        /// @param position - alignment of the widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Frame::Position position);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        ///
        /// @param x_offset - axial distance x between alignment object and widget
        /// @param y_offset - axial distance y between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const int32_t x_offset, const int32_t y_offset);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position widget on the screen
        ///
        /// @param offset - distance between alignment object and widget
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Vector2i offset);

        /////////////////////////////////////////////////////////////////////
        /// getPosition - get position of widget
        ///
        /// @return - position of widget
        /////////////////////////////////////////////////////////////////////
        Vector2i getPosition () const;

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of widget
        /// 
        /// @param x - width od widget
        /// @param y - height of widget
        /////////////////////////////////////////////////////////////////////
        void setSize (const uint32_t x, const uint32_t y);

        /////////////////////////////////////////////////////////////////////
        /// getSize - get size of widget
        ///
        /// @return - size of widget
        /////////////////////////////////////////////////////////////////////
        Vector2u getSize () const;

        /////////////////////////////////////////////////////////////////////
        /// setFieldParam - set size of window where widget is shown
        ///
        /// @param desc - struct with position, width and height of window
        /////////////////////////////////////////////////////////////////////
        void setFieldParam (const PositionDesc& desc);

        /////////////////////////////////////////////////////////////////////
        /// setField - set field which will control this frame
        /// 
        /// @param field - pointer to field where widget will be drawn
        /////////////////////////////////////////////////////////////////////
        void setField (Field* field);

        /////////////////////////////////////////////////////////////////////
        /// getField - get parent field of this frame
        ///
        /// @return - parent field
        /////////////////////////////////////////////////////////////////////
        Field* getField () const;

    protected:

        /////////////////////////////////////////////////////////////////////
        /// update_frame - function for reset sizes of widget
        ///
        /// This function call setRect with description of widget position
        /////////////////////////////////////////////////////////////////////
        void update_frame ();

        /////////////////////////////////////////////////////////////////////
        /// set_position
        /////////////////////////////////////////////////////////////////////
        void set_position ();

    private:

        /////////////////////////////////////////////////////////////////////
        /// setRect - set position and size of visible objects
        ///
        /// Has to be overridden. Widgets should use this rect for size
        /// settings.
        ///
        /// @param desc - structure with position and size of object
        /////////////////////////////////////////////////////////////////////
        virtual void setRect (const PositionDesc& desc) = 0;

    private:
        Position m_alignment = Position (uint32_t (Position::HCENTER) | uint32_t (Position::VCENTER));
        int32_t m_x_offset = 0;
        int32_t m_y_offset = 0;

        Vector2i m_position;

        uint32_t m_width = 0;
        uint32_t m_height = 0;

        Field* m_field = nullptr;
    };


    Frame::Position operator| (const Frame::Position p1, const Frame::Position p2);


}