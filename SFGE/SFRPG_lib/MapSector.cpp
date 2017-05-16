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


void MapSector::setTiles (const std::vector<Panel>& tiles)
{
    m_tiles = tiles;
}

void MapSector::setTiles (std::vector<Panel>&& tiles)
{
    m_tiles = std::move (tiles);
}

void MapSector::setWayPoints (const std::vector<WayPoint>& way_points)
{
    m_way_points = way_points;
}

void MapSector::setWayPoints (std::vector<WayPoint>&& way_points)
{
    m_way_points = std::move (way_points);
}

void sfge::MapSector::setOffset (Vector2f offset)
{
    m_offset = offset;
}

Vector2f MapSector::getOffset () const
{
    return m_offset;
}

void sfge::MapSector::setSize (Vector2f size)
{
    m_size = size;
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
        removeObject (moved_object);
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

    for (size_t i = 0; i < m_way_points.size (); ++i)
    {
        float distance (m_way_points[i].checkArea (pos));
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest_point = static_cast<uint32_t> (i);
        }
    }

    return nearest_point;
}

const WayPoint* MapSector::getWayPoint (uint32_t id) const
{
    return &m_way_points[id];
}

void MapSector::attachObject (std::shared_ptr<MapObject> object)
{
    m_objects.push_back (object);
}

void MapSector::removeObject (const MapObject* object)
{
    m_objects.erase (std::remove_if (
        m_objects.begin (),
        m_objects.end (),
        [object](std::shared_ptr<MapObject> obj) { return object == obj.get (); }
    ));
}

bool MapSector::isObjectInSector (Vector2f pos) const
{
    return pos.x > m_offset.x && pos.y > m_offset.y && pos.x < m_offset.x + m_size.x && pos.y < m_offset.y + m_size.y;
}

void MapSector::connectWayPoints ()
{
    std::vector<WayPoint::EdgeList> neighbours (m_way_points.size ());

    for (size_t i = 0; i < m_way_points.size (); ++i)
    {
        for (size_t j = i + 1; j < m_way_points.size (); ++j)
        {
            if (checkPass (m_way_points[i].getPosition (), m_way_points[j].getPosition ()))
            {
                neighbours[i].push_back (&m_way_points[j]);
                neighbours[j].push_back (&m_way_points[i]);
            }
        }

        m_way_points[i].assignEdges (neighbours[i]);
    }
}

void MapSector::connectWayPoints (MapSector* map_sector)
{
    std::vector<WayPoint::EdgeList> self_neighbours (m_way_points.size ());
    std::vector<WayPoint::EdgeList> neighbours (m_way_points.size ());

    for (size_t i = 0; i < m_way_points.size (); ++i)
    {
        for (size_t j = 0; j < map_sector->m_way_points.size (); ++j)
        {
            if (checkPass (m_way_points[i].getPosition (), map_sector->m_way_points[j].getPosition ()))
            {
                self_neighbours[i].push_back (&map_sector->m_way_points[j]);
                neighbours[j].push_back (&m_way_points[i]);
            }
        }

        m_way_points[i].assignEdges (self_neighbours[i]);
    }

    for (size_t i = 0; i < map_sector->m_way_points.size (); ++i)
    {
        map_sector->m_way_points[i].assignEdges (neighbours[i]);
    }
}

void MapSector::attachNeighbours (WayPoint* way_point) const
{
    WayPoint::EdgeList neighbours;

    for (const WayPoint& point : m_way_points)
    {
        if (checkPass (way_point->getPosition (), point.getPosition ()))
            neighbours.push_back (&point);
    }
}

void MapSector::draw (RenderTarget& target, RenderStates states) const
{
    for (auto& tile : m_tiles)
        target.draw (tile, states);

    for (auto object : m_objects)
        target.draw (*object, states);
}

bool MapSector::checkPass (Vector2f p1, Vector2f p2) const
{
    for (auto object : m_objects)
    {
        if (object->detectCollision (p1, p2) != Collision::State::OUTSIDE)
            return false;
    }

    return true;
}