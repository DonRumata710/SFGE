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


#include "EditField.h"

#include <SFRPG/MapSector.h>
#include <SFRPG/MapLoader.h>
#include <SFRPG/MapSaver.h>

#include <SFGE/FileInputStream.h>
#include <SFGE/FileOutputStream.h>
#include <SFGE/ResourceManager.h>
#include <SFGE/Panel.h>

#include <vector>


using namespace sfge;


EditField::EditField ()
{}

EditField::~EditField ()
{}

void EditField::createMap (float tile_size, uint32_t width, uint32_t height)
{
    std::vector<std::pair<Uint32, std::string>> tiles (width * height, { 0, "tile.grass" });

    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
            tiles[i * width + j].first = i * width + j;
    }

    std::unique_ptr<MapSector> map_sector (std::make_unique<MapSector> (Vector2u (width, height)));
    map_sector->setTiles (tiles);

    std::unordered_map<uint32_t, MapSectorDesc> sectors;
    sectors.insert ({ 0, MapSectorDesc () });
    sectors[0].sector.swap (map_sector);

    m_map.reset (new MapManager ());
    m_map->setName ("New map");
    m_map->setMapDescription (std::move (sectors));
}

void EditField::loadMap (const std::string& path)
{
    std::shared_ptr<iResourceInputStream> stream (std::make_shared<FileInputStream> ());
    std::shared_ptr<MapLoader> loader (std::make_shared<MapLoader> (stream.get ()));
    m_map.reset (new MapManager ());
    loader->loadMap (m_map.get (), path);
}

void EditField::saveMap (const std::string& path)
{
    FileOutputStream stream;
    MapSaver saver (&stream);
    saver.saveMap (m_map.get (), path);
}

void EditField::closeMap ()
{
    m_map.reset ();
}
