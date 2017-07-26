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
#include "GEDevice.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderTexture.hpp>


using namespace sfge;


Label::Label ()
{
    m_text.setFillColor (Color::White);
    m_text.setCharacterSize (14);
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        m_text.setFont (*rm->getFont (ResourceManager::DEFAULT));
}

void Label::setString (const UString& text)
{
    m_text.setString (text);
    update_frame ();
}

void Label::setFont (std::shared_ptr<const Font> font)
{
    m_text.setFont (*font);
    update_frame ();
}

void Label::setFont (const std::string& font)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setFont (rm->findFont (font));
}

void Label::setCharacterSize (unsigned size)
{
    m_text.setCharacterSize (size);
    update_frame ();
}

void Label::setTextColor (Color color)
{
    m_text.setFillColor (color);
}

void Label::setAlign (Align align)
{
    m_align = align;
}

void Label::setRect (const PositionDesc& desc)
{
    m_text.setPosition (desc.x, desc.y);
}

bool Label::check_mouse (const int x, const int y)
{
    return false;
}

void Label::draw (sf::RenderTarget& target) const
{
    target.draw (m_text);
}
