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

#include <SFGE/ResourceManager.h>
#include <SFGE/MemoryInputStream.h>

#include <catch.hpp>


using namespace sfge;


const char map_desc[] = {
    "Sector"
    "{"
    "Model grass"
    "{"
    "    texture = \"grass.bmp\""
    "    width = 1"
    "    height = 1"
    "}"
    "Tile: grass"
    "{"
    "    x = 0"
    "    y = 0"
    "}"
    "Tile: grass"
    "{"
    "    x = 1"
    "    y = 0"
    "}"
    "Tile: grass"
    "{"
    "    x = 2"
    "    y = 0"
    "}"
    "Tile: grass"
    "{"
    "    x = 0"
    "    y = 1"
    "}"
    "Tile: grass"
    "{"
    "    x = 1"
    "    y = 1"
    "}"
    "Tile: grass"
    "{"
    "    x = 2"
    "    y = 1"
    "}"
    "Tile: grass"
    "{"
    "    x = 0"
    "    y = 2"
    "}"
    "Tile: grass"
    "{"
    "    x = 1"
    "    y = 2"
    "}"
    "Tile: grass"
    "{"
    "    x = 2"
    "    y = 2"
    "}"
    "}"
};


template <size_t N> std::vector<char> append_literal (const char (&str)[N])
{
    std::vector<char> v (strlen (str));
    memcpy (v.data (), str, v.capacity ());
    return v;
}


TEST_CASE ("Test loading map")
{
    ResourceManager rm (true);

    std::vector<char> vec_map_desc (append_literal (map_desc));
    std::unordered_map<std::string, std::vector<char>> map_file;
    map_file.insert ({ "test_map.resm", vec_map_desc });

    std::shared_ptr<MemoryInputStream> file_stream (std::make_shared<MemoryInputStream> (map_file));

    std::shared_ptr<MapLoader> loader (std::make_shared<MapLoader> (file_stream));

    auto desc = loader->getSegmentDescriptions ("test_map.resm");

    REQUIRE (desc.size () == 1);

    loader->loadMap ({ &desc[0] });

    REQUIRE (desc[0].sector);

    REQUIRE (desc[0].pos.x == 0);
    REQUIRE (desc[0].pos.y == 0);

    REQUIRE (desc[0].sector);
}
