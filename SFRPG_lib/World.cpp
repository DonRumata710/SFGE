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


#include "World.h"
#include "MapLoader.h"
#include "MapSaver.h"

#include <SFGE/FileInputStream.h>
#include <SFGE/FileOutputStream.h>
#include <SFGE/ResourceManager.h>

#include <SFML/Graphics/Sprite.hpp>


using namespace sfge;


World::World ()
{
    m_panel.setColor (sf::Color::Black);
    m_panel.setSize (36.0f, 20.0f);
}

void World::loadMap (const std::string& path)
{
    std::shared_ptr<iResourceInputStream> stream (std::make_shared<FileInputStream> ());
    std::shared_ptr<MapLoader> loader (std::make_shared<MapLoader> (stream.get ()));
    setMap (std::make_shared<MapManager> ());
    if (!loader->loadMap (getMap ().get (), path))
        getMap ().reset ();
}

void World::saveMap (const std::string& path)
{
    FileOutputStream stream;
    MapSaver saver (&stream);
    saver.saveMap (getMap ().get (), path);
}

void World::closeMap ()
{
    m_map.reset ();
    sf::Sprite sprite;
    sprite.setColor (sf::Color::Black);
    m_screen.draw (sprite);
}

void World::setMap (std::shared_ptr<MapManager> map)
{
    m_map = map;
}

std::shared_ptr<MapManager> sfge::World::getMap ()
{
    return m_map;
}

void World::redraw ()
{
    m_screen.setView (m_view);
    m_screen.draw (m_panel);

    if (m_map)
        m_screen.draw (*m_map);

    m_screen.display ();
}

void World::move (Vector2f offset)
{
    m_panel.move (offset);
    m_view.move (offset);
}

Vector2f World::mapPixelToCoords (Vector2i point)
{
    return m_screen.mapPixelToCoords (point);
}

void World::draw (sf::RenderTarget& target) const
{
    target.draw (m_render_rect, &m_screen.getTexture ());
}

void World::update (const float delta)
{
    redraw ();
}

void World::setRect (const PositionDesc& desc)
{
    m_screen.create (desc.width, desc.height);
    m_view.reset (sf::FloatRect (0.0f, 0.0f, static_cast<float> (desc.width / 100), static_cast<float> (desc.height / 100)));
    m_screen.setView (m_view);

    m_render_rect.setPosition (desc.x, desc.y);
    m_render_rect.setSize (desc.width, desc.height);
}

bool World::check_mouse (const int x, const int y)
{
    return true;
}
