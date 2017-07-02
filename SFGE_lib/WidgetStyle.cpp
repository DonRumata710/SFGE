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


#include "WidgetStyle.h"
#include "GEDevice.h"
#include "ResourceManager.h"


using namespace sfge;


void WidgetStyle::setView (const std::shared_ptr<const Texture> tex, const iWidget::View e)
{
    m_textures.push_back ({ e, tex });
}

void WidgetStyle::setView (const std::string& texture, const iWidget::View e)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (!rm)
        return;

    m_textures.push_back ({ e, rm->findTexture (texture) });
}

void WidgetStyle::setView (const Color& color, const iWidget::View e)
{
    m_colors.push_back ({ e, color });
}

void WidgetStyle::setCharacterSize (unsigned size)
{
    m_font_size = size;
}

void WidgetStyle::setFont (std::shared_ptr<const Font> font)
{
    m_font = font;
}

void sfge::WidgetStyle::setFont (const std::string & font)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        m_font = rm->findFont (font);
}

void WidgetStyle::setPosition (const int position, const int x_offset, const int y_offset)
{
    m_alignment = (Frame::Position) position;
    m_x_offset = x_offset;
    m_y_offset = y_offset;
    m_position_changed = true;
}

void WidgetStyle::setPosition (const int position, const Vector2i offset)
{
    m_alignment = (Frame::Position) position;
    m_x_offset = offset.x;
    m_y_offset = offset.y;
    m_position_changed = true;
}

void WidgetStyle::setPosition (const int position)
{
    m_alignment = (Frame::Position) position;
    m_position_changed = true;
}

void WidgetStyle::setPosition (const int x_offset, const int y_offset)
{
    m_x_offset = x_offset;
    m_y_offset = y_offset;
    m_position_changed = true;
}

void WidgetStyle::setPosition (const Vector2i offset)
{
    m_x_offset = offset.x;
    m_y_offset = offset.y;
    m_position_changed = true;
}

void WidgetStyle::setSize (const unsigned x, const unsigned y)
{
    m_width = x;
    m_height = y;
}
