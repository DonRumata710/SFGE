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


#include "Label.h"
#include "GuiManager.h"

#include <SFML/Graphics/RenderTexture.hpp>



sfge::Label::Label ()
{
    m_text.setFillColor (Color::White);
    m_text.setCharacterSize (14);
}

void sfge::Label::setString (const UString& text)
{
    m_text.setString (text);
    update_frame ();
}

void sfge::Label::setFont (std::shared_ptr<const Font> font)
{
    m_text.setFont (*font);
    update_frame ();
}

void sfge::Label::setCharacterSize (unsigned size)
{
    m_text.setCharacterSize (size);
    update_frame ();
}

void sfge::Label::setTextColor (Color color)
{
    m_text.setFillColor (color);
}

void sfge::Label::setAlign (Align align)
{
    m_align = align;
}

void sfge::Label::setRect (const PositionDesc& desc)
{
    sf::Vector2f pos;

    switch ((int) m_align & 0b11)
    {
    case Position::LEFT:
        pos.x = float (desc.x);
        break;
    case Position::RIGHT:
        pos.x = float (desc.width - m_text.getLocalBounds ().width);
        break;
    default:
        pos.x = float (desc.width / 2 - m_text.getLocalBounds ().width / 2);
        break;
    }

    switch ((int) m_align & 0b1100)
    {
    case Position::TOP:
        pos.y = float (desc.y);
        break;
    case Position::BOTTOM:
        pos.y = float (desc.height - m_text.getLocalBounds ().height);
        break;
    default:
        pos.y = float (desc.height / 2 - m_text.getLocalBounds ().height / 2);
        break;
    }

    m_text.setPosition (pos);
}

bool sfge::Label::check_mouse (const int x, const int y)
{
    return false;
}

void sfge::Label::draw (sf::RenderTarget& target) const
{
    target.draw (m_text);
}
