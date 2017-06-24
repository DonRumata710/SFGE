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
#include <SFRPG/MapLoader.h>
#include <SFRPG/MapSaver.h>

#include <SFGE/ResourceManager.h>
#include <SFGE/MemoryInputStream.h>
#include <SFGE/MemoryOutputStream.h>

#include <catch.hpp>


using namespace sfge;


template <size_t N> std::vector<char> append_literal (const char (&str)[N])
{
    std::vector<char> v (strlen (str) + 1, '\0');
    memcpy (v.data (), str, v.capacity ());
    return v;
}


TEST_CASE ("Test saving and loading map")
{
    std::shared_ptr<ResourceManager> rm (ResourceManager::createInstance ( "", true));

    size_t size = 100;

    std::vector<std::pair<Uint32, std::string>> tiles (size * size, { 0, "tile.grass" });

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
            tiles[i * size + j].first = static_cast<Uint32> (i + j * size);
    }

    std::unique_ptr<MapSector> map_sector (std::make_unique<MapSector> (Vector2u (size, size)));
    map_sector->setName ("test sector");
    map_sector->setTiles (tiles);

    std::unordered_map<uint32_t, MapSectorDesc> sectors;
    sectors[0].sector.swap (map_sector);
    sectors[0].size = sectors[0].sector->getSize ();

    MemoryOutputStream stream;
    MapSaver saver (&stream);

    {
        MapManager map;
        map.setName ("test map");
        map.setMapDescription (std::move (sectors));

        REQUIRE (saver.saveMap (&map, "test1_map.resm"));
    }

    std::shared_ptr<MemoryInputStream> file_stream (stream.getFullData ());
    auto sector1 = stream.getMemory ("test sector.ress");
    
    std::shared_ptr<MapLoader> loader (std::make_shared<MapLoader> (file_stream.get ()));

    {
        MapManager new_map;

        REQUIRE (loader->loadMap (&new_map, "test1_map.resm"));

        REQUIRE (saver.saveMap (&new_map, "test2_map.resm"));
    }

    auto data1 = stream.getMemory ("test1_map.resm");
    auto data2 = stream.getMemory ("test2_map.resm");

    REQUIRE (data1 == data2);

    auto sector2 = stream.getMemory ("test sector.ress");

    REQUIRE (sector1 == sector2);
}
