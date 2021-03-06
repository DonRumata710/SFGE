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


#include "Panel.h"
#include "GEDevice.h"
#include "ResourceManager.h"
#include "Err.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using namespace sfge;


Panel::Panel ()
{}

Panel::Panel (const std::shared_ptr<const sf::Texture> tex)
{
    if (!tex)
    {
        debug_message ("Panel got empty texture pointer");
        return;
    }

    setTexture (tex);

    m_arr[1].position.x = m_arr[0].position.x + tex->getSize ().x;
    m_arr[2].position.y = m_arr[0].position.y + tex->getSize ().y;
    m_arr[3].position = sf::Vector2f (m_arr[0].position.x + tex->getSize ().x, m_arr[0].position.y + tex->getSize ().y);
}

void Panel::setTexture (const std::shared_ptr<const sf::Texture> tex)
{
    if (!tex)
    {
        debug_message ("Panel got empty texture pointer");
        return;
    }

    m_texture = tex;
    sf::Vector2f size (tex->getSize ());
    m_arr[0].texCoords = sf::Vector2f (0.0, 0.0);
    m_arr[1].texCoords = sf::Vector2f (size.x, 0.0);
    m_arr[2].texCoords = sf::Vector2f (0.0, size.y);
    m_arr[3].texCoords = sf::Vector2f (size.x, size.y);
    m_arr[0].color = sf::Color (255, 255, 255);
    m_arr[1].color = sf::Color (255, 255, 255);
    m_arr[2].color = sf::Color (255, 255, 255);
    m_arr[3].color = sf::Color (255, 255, 255);
}

void Panel::setTexture (const std::string& tex)
{
    auto rm (GEDevice::getInstance ()->getResourceManager ());
    if (rm)
        setTexture (rm->findTexture (tex));
}

std::shared_ptr<const Texture> Panel::getTexture () const
{
    return m_texture;
}

void Panel::setColor (const sf::Color color)
{
    m_arr[0].color = color;
    m_arr[1].color = color;
    m_arr[2].color = color;
    m_arr[3].color = color;
    m_texture.reset ();
}

void Panel::setPosition (const float x, const float y)
{
    sf::Vector2u size (m_arr[1].position.x - m_arr[0].position.x, m_arr[2].position.y - m_arr[0].position.y);

    m_arr[0].position = sf::Vector2f (x, y);
    m_arr[1].position = sf::Vector2f (x + size.x, y);
    m_arr[2].position = sf::Vector2f (x, y + size.y);
    m_arr[3].position = sf::Vector2f (x + size.x, y + size.y);
}

void Panel::setPosition (const sf::Vector2f pos)
{
    sf::Vector2u size (m_arr[1].position.x - m_arr[0].position.x, m_arr[2].position.y - m_arr[0].position.y);

    m_arr[0].position = sf::Vector2f (pos.x, pos.y);
    m_arr[1].position = sf::Vector2f (pos.x + size.x, pos.y);
    m_arr[2].position = sf::Vector2f (pos.x, pos.y + size.y);
    m_arr[3].position = sf::Vector2f (pos.x + size.x, pos.y + size.y);
}

void Panel::move (const Vector2f vec)
{
    m_arr[0].position += vec;
    m_arr[1].position += vec;
    m_arr[2].position += vec;
    m_arr[3].position += vec;
}

void Panel::setPosition (const FloatRect pos)
{
    m_arr[0].position = Vector2f (pos.left, pos.top);
    m_arr[1].position = Vector2f (pos.left + pos.width, pos.top);
    m_arr[2].position = Vector2f (pos.left, pos.top + pos.height);
    m_arr[3].position = Vector2f (pos.left + pos.width, pos.top + pos.height);
}

void Panel::setSize (const Vector2f size)
{
    m_arr[1].position.x = m_arr[0].position.x + size.x;
    m_arr[2].position.y = m_arr[0].position.y + size.y;
    m_arr[3].position = sf::Vector2f (m_arr[0].position.x + size.x, m_arr[0].position.y + size.y);
}

void Panel::setSize (float x, float y)
{
    m_arr[1].position.x = m_arr[0].position.x + x;
    m_arr[2].position.y = m_arr[0].position.y + y;
    m_arr[3].position = { m_arr[0].position.x + x, m_arr[0].position.y + y };
}

FloatRect Panel::getRect () const
{
    return FloatRect (
        m_arr[0].position.x,
        m_arr[0].position.y,
        m_arr[1].position.x - m_arr[0].position.x,
        m_arr[2].position.y - m_arr[0].position.y
    );
}

sf::Vector2f Panel::getPosition () const
{
    return m_arr[0].position;
}

sf::Vector2f Panel::getSize () const
{
    return sf::Vector2f (m_arr[1].position.x - m_arr[0].position.x,
        m_arr[2].position.y - m_arr[0].position.y
    );
}

bool Panel::contains (const float x, const float y)
{
    if (x >= m_arr[0].position.x && x <= m_arr[1].position.x &&
        y >= m_arr[0].position.y && y <= m_arr[2].position.y
    )
        return true;

    return false;
}

void Panel::setTexCoord (const IntRect & rect)
{
    if (rect.height == 0 && m_texture)
    {
        sf::Vector2f size (m_texture->getSize ());
        m_arr[0].texCoords = sf::Vector2f (0.0, 0.0);
        m_arr[1].texCoords = sf::Vector2f (size.x, 0.0);
        m_arr[2].texCoords = sf::Vector2f (0.0, size.y);
        m_arr[3].texCoords = sf::Vector2f (size.x, size.y);
    }

    m_arr[0].texCoords = sf::Vector2f (rect.left, rect.top);
    m_arr[1].texCoords = sf::Vector2f (rect.left + rect.height, rect.top);
    m_arr[2].texCoords = sf::Vector2f (rect.left, rect.top + rect.height);
    m_arr[3].texCoords = sf::Vector2f (rect.left + rect.height, rect.top + rect.height);
}

void Panel::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_texture)
        target.draw (m_arr, 4, sf::PrimitiveType::TriangleStrip, m_texture.get ());
    else
        target.draw (m_arr, 4, sf::PrimitiveType::TriangleStrip);
}
