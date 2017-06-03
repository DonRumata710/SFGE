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


#include "MapLoader.h"
#include "SectorLoader.h"
#include "MapSaver.h"
#include "MapManager.h"
#include "PathDescription.h"
#include "Way.h"

#include <SFGE/Err.h>

#include <map>


using namespace sfge;



struct PathDesc
{
    const WayPoint* point = nullptr;
    const WayPoint* parent = nullptr;
    float passed_dist = 0.0f;

    PathDesc (const WayPoint* _point) :
        point (_point)
    {}

    PathDesc (const WayPoint* _parent, const WayPoint* p) :
        parent (_parent), point (p)
    {}

    PathDesc (const WayPoint* _parent, const WayPoint* p, float dist) :
        parent (_parent), point (p), passed_dist (dist)
    {}
};


MapManager* MapManager::m_instance (nullptr);


MapManager* MapManager::getInstance ()
{
    return m_instance;
}

MapManager::MapManager ()
{
    if (!m_instance)
        m_instance = this;
    else
        debug_message ("Map manager was created few times");
}

MapManager::~MapManager ()
{
    m_instance = nullptr;
}

void MapManager::setMapDescription (std::unordered_map<uint32_t, MapSectorDesc>&& sectors)
{
    m_sectors = std::move (sectors);
}

void MapManager::setName (const std::string& name)
{
    m_name = name;
}

std::string MapManager::getName () const
{
    return m_name;
}

void MapManager::setLoader (std::unique_ptr<SectorLoader>& loader)
{
    m_loader.swap (loader);
}

void MapManager::lookMap (const std::vector<UintRect>& areas)
{
    std::vector<MapSectorDesc*> sectors;
    sf::Vector2<sf::Uint64> offset;
    for (const auto& area : areas)
    {
        offset.x += (Uint64 (area.left) + area.width) / 2;
        offset.y += (area.top + area.height) / 2;

        for (auto& sector : m_sectors)
        {
            if (area.left < sector.second.pos.x + sector.second.size.x &&
                area.top  < sector.second.pos.y + sector.second.size.y &&
                area.left + area.width > sector.second.pos.x &&
                area.top + area.height > sector.second.pos.y &&
                !sector.second.sector
            )
            {
                sectors.push_back (&sector.second);
            }
        }
    }

    setOffset (offset.x / areas.size (), offset.y / areas.size ());

    m_loader->loadSectors (sectors);
}

bool MapManager::save (MapSaver* saver)
{
    saver->save ("name", getName ());
    for (auto& sector : m_sectors)
    {
        if (sector.second.path.empty ())
            sector.second.path = sector.second.sector->getName () + ".ress";
        if (sector.second.path.empty ())
            sector.second.path = "sector-" + std::to_string (sector.first) + ".ress";
        if (!saver->saveSectorDescription (sector.first, sector.second))
        {
            runtime_error ("Failed saving description of sector " + sector.second.sector->getName ());
            return false;
        }
    }

    return true;
}

bool MapManager::saveSectors (MapSaver * saver)
{
    for (const auto& sector : m_sectors)
    {
        if (!sector.second.sector) continue;

        if (!saver->saveSector (sector.second.sector.get (), sector.second.path))
        {
            runtime_error ("Failed saving sector " + sector.second.sector->getName ());
            return false;
        }
    }

    return true;
}

Way MapManager::getWay (Vector2f departure, Vector2f target) const
{
    WayPointID departure_point;
    WayPointID target_point;

    for (const auto& map : m_sectors)
    {
        if (map.second.sector->isObjectInSector (departure))
        {
            departure_point = { map.first, map.second.sector->getNearestWayPoint (departure - map.second.sector->getOffset ()) };
            break;
        }
    }

    for (const auto& map : m_sectors)
    {
        if (map.second.sector->isObjectInSector (target))
        {
            target_point = { map.first, map.second.sector->getNearestWayPoint (target - map.second.sector->getOffset ()) };
            break;
        }
    }

    Way way (findWay (departure_point, target_point));

    way.pushPointBack (target);

    return way;
}

MapSector* MapManager::getSector (Vector2f position)
{
    for (auto& map : m_sectors)
    {
        if (map.second.sector && map.second.sector->isObjectInSector (position))
            return map.second.sector.get ();
    }

    return nullptr;
}

void MapManager::setOffset (unsigned x, unsigned y)
{
    for (auto& map : m_sectors)
    {
        if (map.second.sector)
            map.second.sector->setOffset ({ (float) x, (float) y });
    }

    m_offset.x = x;
    m_offset.y = y;
}

void MapManager::findWayPointsEdges ()
{
    for (auto& i : m_sectors)
    {
        i.second.sector->connectWayPoints ();
        for (auto& j : m_sectors)
        {
            if (&i != &j)
            {
                i.second.sector->connectWayPoints (j.second.sector.get ());
            }
        }
    }
}

std::deque<Vector2f> MapManager::findWay (const WayPointID& departure, const WayPointID& target) const
{
    const WayPoint* departure_point (m_sectors.at (departure.m_map_id).sector->getWayPoint (departure.m_id));
    const WayPoint* target_point (m_sectors.at (target.m_map_id).sector->getWayPoint (target.m_id));

    std::map<float, PathDesc> opened_points;
    opened_points.insert ({ getDistance (departure_point->getPosition (), target_point->getPosition ()), departure_point });

    std::unordered_map<const WayPoint*, const WayPoint*> closed_points;

    while (opened_points.begin ()->second.point != target_point)
    {
        auto point_iterator (opened_points.begin ());
        auto pending_point (point_iterator->second);

        auto edges (pending_point.point->getEdges ());

        for (const WayPoint* current_point : edges)
        {
            if (current_point == target_point)
            {
                opened_points.insert ({ 0.0f, { pending_point.point, current_point } });
                break;
            }

            if (closed_points.find (current_point) == closed_points.end ())
            {
                PathDesc desc (
                    pending_point.point,
                    current_point,
                    pending_point.passed_dist + getDistance (current_point->getPosition (), pending_point.point->getPosition ())
                );
                opened_points.insert ({ getDistance (current_point->getPosition (), target_point->getPosition ()) + desc.passed_dist, desc });
            }
        }

        closed_points.insert ({ pending_point.point, pending_point.parent });
        opened_points.erase (point_iterator);
    }

    std::deque<Vector2f> points;

    const WayPoint* step_departure (opened_points.begin ()->second.parent);
    const WayPoint* step_target (target_point);

    while (step_departure != nullptr)
    {
        points.push_front (getWayStep (step_departure, step_target));

        step_target = step_departure;
        step_departure = closed_points[step_departure];
    }

    return points;
}

float MapManager::getDistance (Vector2f p1, Vector2f p2)
{
    Vector2f dist (p1 - p2);
    return sqrt (dist.x * dist.x + dist.y * dist.y);
}

Vector2f MapManager::getWayStep (const WayPoint* p1, const WayPoint* p2)
{
    Vector2f start (p1->getPosition ());
    Vector2f end (p2->getPosition ());

    Vector2f dist (end - start);

    return start + dist * p2->getRadius () / sqrt (dist.x * dist.x + dist.y * dist.y);
}

void MapManager::draw (RenderTarget& target, RenderStates states) const
{
    for (const auto& sector : m_sectors)
        target.draw (*sector.second.sector);
}
