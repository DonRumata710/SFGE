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


#include "TileDescription.h"

#include <unordered_map>
#include <string>


namespace sfge
{


    class MapSector;
    class Panel;
    class TextParser;


    enum MapDescritpion : size_t
    {
        MD_NONE, MD_END, MD_NUMBER, MD_STRING, MD_BASE, MD_EQUAL,
        MD_OPEN_BLOCK, MD_CLOSE_BLOCK,
        MD_MAP,
        MD_NAME,
        MD_SECTOR,
        MD_ID, MD_PATH, MD_POSITION, MD_SIZE,
        MD_TILE,
        MD_TEXTURE, MD_X, MD_Y, MD_WIDTH, MD_HEIGHT,
        MD_MODEL
    };


    class MapParser
    {
    public:
        MapParser (const std::unordered_map<std::string, TileDesc>&);

        bool loadMapSector (TextParser* tp, MapSector* sector);

        bool loadTileModel (TextParser* tp);

        Panel loadTile (TextParser* tp);

    private:
        std::unordered_map<std::string, TileDesc> m_models;
    };


}
