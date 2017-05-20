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


#include "Frame.h"
#include "Field.h"


sfge::Frame::Frame ()
{}

sfge::Frame::~Frame ()
{}

void sfge::Frame::setPosition (const int position, const int x_offset, const int y_offset)
{
    m_alignment = (Position) position;
    m_x_offset = x_offset;
    m_y_offset = y_offset;
    set_position ();
}

void sfge::Frame::setPosition (const int position)
{
    m_alignment = (Position) position;
    set_position ();
}

void sfge::Frame::setPosition (const int x_offset, const int y_offset)
{
    m_x_offset = x_offset;
    m_y_offset = y_offset;
    set_position ();
}

void sfge::Frame::setSize (const unsigned x, const unsigned y)
{
    m_width = x;
    m_height = y;
    set_position ();
}

void sfge::Frame::setFieldParam (const PositionDesc& desc)
{
    m_position = { desc.x, desc.y };

    switch ((int) m_alignment & 0b11)
    {
    case Position::LEFT:
        m_position.x += m_x_offset;
        break;
    case Position::RIGHT:
        m_position.x += desc.width - m_width - m_x_offset;
        break;
    case Position::HCENTER:
        m_position.x += desc.width / 2 + m_x_offset - m_width / 2;
        break;
    default:
        m_position.x += m_x_offset;
        m_width = desc.width - m_x_offset * 2;
        break;
    }

    switch ((int) m_alignment & 0b1100)
    {
    case Position::TOP:
        m_position.y += m_y_offset;
        break;
    case Position::BOTTOM:
        m_position.y += desc.height - m_height - m_y_offset;
        break;
    case Position::VCENTER:
        m_position.y += desc.height / 2 + m_y_offset - m_height / 2;
        break;
    default:
        m_position.y += m_y_offset;
        m_height = desc.height - m_y_offset * 2;
        break;
    }

    setRect ({ m_position.x, m_position.y, m_width, m_height });
}

void sfge::Frame::setField (Field* field)
{
    m_field = field;
}

void sfge::Frame::update_frame ()
{
    setRect ({ m_position.x, m_position.y, m_width, m_height });
}

void sfge::Frame::set_position ()
{
    if (!m_field) return;

    PositionDesc size (m_field->getPositionDesc ());

    if (size.width == 0) return;

    setFieldParam (size);
}


