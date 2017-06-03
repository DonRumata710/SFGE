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
#include "MapSectorDesc.h"

#include <SFGE/ResourceInputStream.h>

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>


namespace sfge
{


    using sf::Vector2u;

    class MapManager;
    class TextParser;
    struct SemanticsDescription;


    /////////////////////////////////////////////////////////////////////
    /// MapLoader - class for loading map from file
    /////////////////////////////////////////////////////////////////////
    class MapLoader
    {
    public:
      
        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param stream - source for loading file
        /////////////////////////////////////////////////////////////////////
        MapLoader (iResourceInputStream* stream);

        /////////////////////////////////////////////////////////////////////
        /// loadMap - load map
        ///
        /// @param map - map manager
        /// @param path - path where description of map can be found
        /////////////////////////////////////////////////////////////////////
        bool loadMap (MapManager* map, const std::string& path);

    private:
        const char* loadScript (const std::string& path);

        std::string parseMap (TextParser* tp, std::unordered_map<uint32_t, MapSectorDesc>*);

    private:
        std::string m_path;

        float m_tile_size = 1.0f;

        iResourceInputStream* m_file_stream;

    private:
        static const SemanticsDescription m_sem_desc;
    };


}
