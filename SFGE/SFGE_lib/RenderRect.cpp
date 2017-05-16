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


#include "RenderRect.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



namespace sfge
{


    RenderRect::RenderRect ()
    {}

    RenderRect::RenderRect (sf::Vector2u size)
    {
        m_arr[0].texCoords = sf::Vector2f (0.0, 0.0);
        m_arr[1].texCoords = sf::Vector2f (size.x, 0.0);
        m_arr[2].texCoords = sf::Vector2f (0.0, size.y);
        m_arr[3].texCoords = sf::Vector2f (size.x, size.y);

        m_arr[1].texCoords.x = size.x;
        m_arr[2].texCoords.y = size.y;
        m_arr[3].texCoords = sf::Vector2f (size.x, size.y);
    }

    void RenderRect::setPosition (const int x, const int y)
    {
        sf::Vector2i size (m_arr[1].position.x - m_arr[0].position.x, m_arr[2].position.y - m_arr[0].position.y);

        m_arr[0].position = sf::Vector2f (x, y);
        m_arr[1].position = sf::Vector2f (x + size.x, y);
        m_arr[2].position = sf::Vector2f (x, y + size.y);
        m_arr[3].position = sf::Vector2f (x + size.x, y + size.y);
    }

    void RenderRect::setPosition (const Vector2i pos)
    {
        sf::Vector2i size (m_arr[1].position.x - m_arr[0].position.x, m_arr[2].position.y - m_arr[0].position.y);

        m_arr[0].position = sf::Vector2f (pos.x, pos.y);
        m_arr[1].position = sf::Vector2f (pos.x + size.x, pos.y);
        m_arr[2].position = sf::Vector2f (pos.x, pos.y + size.y);
        m_arr[3].position = sf::Vector2f (pos.x + size.x, pos.y + size.y);
    }

    void RenderRect::setPosition (const IntRect pos)
    {
        m_arr[0].position = sf::Vector2f (pos.left, pos.top);
        m_arr[1].position = sf::Vector2f (pos.left + pos.width, pos.top);
        m_arr[2].position = sf::Vector2f (pos.left, pos.top + pos.height);
        m_arr[3].position = sf::Vector2f (pos.left + pos.width, pos.top + pos.height);
    }

    void RenderRect::setSize (const sf::Vector2u size)
    {
        m_arr[1].position.x = m_arr[0].position.x + size.x;
        m_arr[2].position.y = m_arr[0].position.y + size.y;
        m_arr[3].position = sf::Vector2f (m_arr[0].position.x + size.x, m_arr[0].position.y + size.y);

        m_arr[1].texCoords.x = size.x;
        m_arr[2].texCoords.y = size.y;
        m_arr[3].texCoords = sf::Vector2f (size.x, size.y);
    }

    void RenderRect::setSize (unsigned x, unsigned y)
    {
        m_arr[1].position.x = m_arr[0].position.x + x;
        m_arr[2].position.y = m_arr[0].position.y + y;
        m_arr[3].position = sf::Vector2f (m_arr[0].position.x + x, m_arr[0].position.y + y);

        m_arr[1].texCoords.x = x;
        m_arr[2].texCoords.y = y;
        m_arr[3].texCoords = sf::Vector2f (x, y);
    }

    sf::IntRect RenderRect::getRect () const
    {
        return sf::IntRect (
            m_arr[0].position.x,
            m_arr[0].position.y,
            m_arr[1].position.x - m_arr[0].position.x,
            m_arr[2].position.y - m_arr[0].position.y
        );
    }

    sf::Vector2i RenderRect::getPosition () const
    {
        return sf::Vector2i (
            m_arr[0].position.x,
            m_arr[0].position.y
        );
    }

    sf::Vector2u RenderRect::getSize () const
    {
        return sf::Vector2u (m_arr[1].position.x - m_arr[0].position.x,
            m_arr[2].position.y - m_arr[0].position.y
        );
    }

    bool RenderRect::contains (const float x, const float y)
    {
        if (x >= m_arr[0].position.x && x <= m_arr[1].position.x &&
            y >= m_arr[0].position.y && y <= m_arr[2].position.y
            )
            return true;

        return false;
    }

    void RenderRect::draw (sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw (m_arr, 4, sf::PrimitiveType::TriangleStrip, states);
    }


}
