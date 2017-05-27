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
    MapSector map_sector;

    std::vector<Panel> panels (width * height, ResourceManager::getInstance ()->findTexture ("tile.grass"));

    for (size_t i = 0; i < width; ++i)
    {
        for (size_t j = 0; j < height; ++j)
        {
            panels[i * height + j].setPosition (tile_size * i, tile_size * j);
            panels[i * height + j].setSize (tile_size, tile_size);
        }
    }

    map_sector.setTiles (panels);

    std::unordered_map<uint32_t, MapSector> sectors;
    sectors.insert ({ 0,map_sector });

    m_map.reset (new Map (sectors));
}

void EditField::loadMap (const std::string& path)
{
    m_map_manager.loadMap (path);
}

void EditField::saveMap (const std::string& path)
{}

void EditField::closeMap ()
{}
