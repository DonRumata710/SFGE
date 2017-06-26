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


#include <SFRPG/MapManager.h>
#include <SFRPG/MapSector.h>
#include <SFRPG/Way.h>
#include <SFRPG/StaticObject.h>

#include <catch.hpp>


using namespace sfge;


TEST_CASE ("Test way finding")
{
    std::unordered_map<uint32_t, MapSectorDesc> sectors;

    std::vector<WayPoint> way_points;

    way_points.assign (10, WayPoint ());

    for (auto& point : way_points)
    {
        point.setRadius (8.0);
    }

    way_points[0].setPosition ({ 10.0, 10.0 });
    way_points[1].setPosition ({ 20.0, 10.0 });
    way_points[2].setPosition ({ 30.0, 10.0 });
    way_points[3].setPosition ({ 40.0, 10.0 });
    way_points[4].setPosition ({ 50.0, 10.0 });
    way_points[5].setPosition ({ 60.0, 10.0 });
    way_points[6].setPosition ({ 60.0, 20.0 });
    way_points[7].setPosition ({ 60.0, 30.0 });
    way_points[8].setPosition ({ 60.0, 40.0 });
    way_points[9].setPosition ({ 60.0, 50.0 });

    sectors[0].sector = std::make_unique<MapSector> (Vector2u (100, 100));
    sectors[0].sector->setWayPoints (way_points);

    std::shared_ptr<MapObject> obj (new StaticObject ());

    Collision c1;

    Circuit points1;
    points1.assign ({ { 20.0, 20.0 }, { 50.0, 20.0 }, { 50.0, 50.0 }, { 20.0, 50.0 } });

    c1.setPoints (points1);

    obj->setCollision (c1);

    sectors[0].sector->attachObject (obj);

    MapManager map;

    map.setMapDescription (std::move (sectors));

    MapSector* sector (map.getSector ({ 1.0, 1.0 }));
    REQUIRE (sector);
    uint32_t id (sector->getNearestWayPoint ({ 11.0, 11.0 }));
    REQUIRE (id == 0);
    const WayPoint* point (sector->getWayPoint (id));
    REQUIRE (point);
    auto edges (point->getEdges ());
    REQUIRE (edges.size () == 6);

    Vector2f position (5.0, 10.0);
    Vector2f target (60.0, 55.0);

    Way way (map.getWay (position, target));

    REQUIRE (way.getPoints () != 0);
    REQUIRE (way.getLength () != 0.0);

    for (size_t i = 0; i < 100; ++i)
        position += way.getMovingVector (position, 1.0);

    REQUIRE (position == target);
}