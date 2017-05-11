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


#include "MapSector.h"
#include "InteractiveObject.h"
#include "Way.h"


using namespace sfge;


Vector2f MapSector::getOffset () const
{
    return m_offset;
}

Vector2f MapSector::getSize () const
{
    return m_size;
}

bool MapSector::checkMovement (InteractiveObject* moved_object)
{
    if (moved_object->getPosition ().x < m_offset.x ||
        moved_object->getPosition ().y < m_offset.y ||
        moved_object->getPosition ().x > m_offset.x + m_size.x ||
        moved_object->getPosition ().y > m_offset.y + m_size.y
    )
    {
        moved_object->runAction<SectorLeavingAction> (nullptr);
        m_objects.erase (
            std::remove_if (
                m_objects.begin (),
                m_objects.end (),
                [moved_object](std::shared_ptr<MapObject> object) { return moved_object == object.get (); }
            )
        );
    }

    for (auto object : m_objects)
    {
        if (object->detectCollision (moved_object) != Collision::State::OUTSIDE)
        {
            moved_object->runAction<CollisionAction> (nullptr);
            return false;
        }
    }

    return true;
}

uint32_t MapSector::getNearestWayPoint (Vector2f pos) const
{
    uint32_t nearest_point (0);
    float min_distance (FLT_MAX);

    for (const auto& point : m_way_points)
    {
        float distance (point.second.checkArea (pos));
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest_point = point.first;
        }
    }

    return nearest_point;
}

const WayPoint* MapSector::getPoint (uint32_t id)
{
    return &m_way_points[id];
}

void MapSector::attachObject (std::shared_ptr<MapObject> object)
{
    m_objects.push_back (object);
}

bool sfge::MapSector::checkObjectPosition (Vector2f pos) const
{
    return pos.x > m_offset.x && pos.y > m_offset.y && pos.x < m_offset.x + m_size.x && pos.y < m_offset.y + m_size.y;
}

void MapSector::draw (RenderTarget& target, RenderStates states) const
{
    for (auto& tile : m_tiles)
        target.draw (tile, states);

    for (auto object : m_objects)
        target.draw (*object, states);
}
