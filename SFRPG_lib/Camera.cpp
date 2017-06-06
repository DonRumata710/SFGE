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


#include "Camera.h"
#include "MapLoader.h"
#include "MapSaver.h"

#include <SFGE/FileInputStream.h>
#include <SFGE/FileOutputStream.h>
#include <SFGE/ResourceManager.h>


using namespace sfge;


Camera::Camera ()
{
    sf::View view (sf::FloatRect (0, 0, 36, 20));
    m_view.setView (view);
}

void Camera::loadMap (const std::string& path)
{
    std::shared_ptr<iResourceInputStream> stream (std::make_shared<FileInputStream> ());
    std::shared_ptr<MapLoader> loader (std::make_shared<MapLoader> (stream.get ()));
    setMap (std::make_shared<MapManager> ());
    if (!loader->loadMap (getMap ().get (), path))
        getMap ().reset ();
}

void Camera::saveMap (const std::string& path)
{
    FileOutputStream stream;
    MapSaver saver (&stream);
    saver.saveMap (getMap ().get (), path);
}

void Camera::setMap (std::shared_ptr<MapManager> map)
{
    m_map = map;
}

std::shared_ptr<MapManager> sfge::Camera::getMap ()
{
    return m_map;
}

void Camera::redraw ()
{
    m_view.draw (*m_map);
}

void Camera::setRect (const PositionDesc& desc)
{
    m_render_rect.setPosition (desc.x, desc.y);
    m_render_rect.setSize (desc.width, desc.height);
}

bool Camera::check_mouse (const int x, const int y)
{
    return true;
}

void Camera::draw (sf::RenderTarget& target) const
{
    target.draw (m_render_rect, &m_view.getTexture ());
}
