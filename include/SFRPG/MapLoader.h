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


#pragma once


#include "MapSector.h"
#include "TileDescription.h"

#include <SFGE/ResourceInputStream.h>

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>


namespace sfge
{


    using sf::Vector2u;

    class Map;
    class TextParser;
    struct MapSegmentDesc;
    struct SemanticsDescription;


    class MapLoader
    {
    public:
        MapLoader (std::shared_ptr<ResourceInputStream> stream);

        std::unordered_map<uint32_t, MapSegmentDesc> getSegmentDescriptions (const std::string& path);

        void loadMap (const std::vector<MapSegmentDesc*>& sectors);

    private:
        const char* loadScript (const std::string& path);

        bool parseMap (TextParser* tp, std::unordered_map<uint32_t, MapSegmentDesc>*);

    private:
        std::string m_map_name;
        std::unordered_map<std::string, TileDesc> m_tile_models;

        float m_tile_size = 1.0f;

        std::shared_ptr<ResourceInputStream> m_file_stream;

        static const SemanticsDescription m_sem_desc;
    };


}
