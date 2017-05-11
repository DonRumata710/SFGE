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
#include "Way.h"


using namespace sfge;


Way Map::getWay (Vector2f departure, Vector2f target) const
{
    WayPointID departure_point;
    WayPointID target_point;

    for (const auto& map : m_sectors)
    {
        if (map.second.checkObjectPosition (departure))
            departure_point = { map.first, map.second.getNearestWayPoint (departure - map.second.getOffset ()) };
    }

    for (const auto& map : m_sectors)
    {
        if (!map.second.checkObjectPosition (target))
            continue;

        departure_point = { map.first, map.second.getNearestWayPoint (target - map.second.getOffset ()) };
    }

    Way way;

    while (true)
    {
        /*
        way.pushPointBack (departure_point->getRoute (target_point));
        WayPointID point_id = departure_point->getNextPoint (target_point);
        target_point = m_sectors.at (point_id.m_map_id).get;
        */
    }

    return way;
}

MapSector* Map::getSector (Vector2f position)
{
    for (auto& map : m_sectors)
    {
        if (map.second.checkObjectPosition (position))
            return &map.second;
    }

    return nullptr;
}

void sfge::Map::draw (sfge::RenderTarget& target) const
{
    for (const auto& sector : m_sectors)
        target.draw (sector.second);
}
