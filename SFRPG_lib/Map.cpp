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


#include "Map.h"
#include "InteractiveObject.h"
#include "Way.h"


using namespace sfge;


Map::Map (uint32_t id) :
    m_id (id)
{}

Map::~Map ()
{}

bool Map::checkMovement (InteractiveObject* moved_object) const
{
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

Way Map::getWay (Vector2f departure, Vector2f target) const
{
    const WayPoint* const departure_point (getNearestWayPoint (departure));
    const WayPoint* const target_point (getNearestWayPoint (target));

    std::vector<const WayPoint*> way_points;

    if (departure_point == target_point)
        return Way (way_points, target);

    way_points.push_back (departure_point);

    while (true)
    {
        const WayPoint* next_point (departure_point->getNextPoint (target_point));
        way_points.push_back (next_point);
        if (next_point == target_point)
            break;
    }

    return Way (way_points, target);
}

void Map::draw (sfge::RenderTarget& target) const
{
    for (auto tile : m_tiles)
        target.draw (tile);

    for (auto object : m_objects)
        object->draw (target);
}

const WayPoint* Map::getNearestWayPoint (Vector2f pos) const
{
    const WayPoint* nearest_point (nullptr);
    float min_distance (FLT_MAX);

    for (const WayPoint point : m_way_points)
    {
        float distance (point.checkArea (pos));
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest_point = &point;
        }
    }

    return nearest_point;
}
