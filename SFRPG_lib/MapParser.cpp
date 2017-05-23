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


#include <MapParser.h>


using namespace sfge;


enum MapDescritpion : size_t
{
    MD_NONE, MD_END, MD_NUMBER, MD_STRING, MD_BASE, MD_EQUAL,
    MD_OPEN_BLOCK, MD_CLOSE_BLOCK,
    MD_SECTOR,
    MD_TILE,
    MD_TILE_SIZE,
    MD_TEXTURE,
    MD_WIDTH,
    MD_HEIGHT,
    MD_MODEL
};


const SemanticsDescription MapParser::m_sem_desc = {
    {
        { ":",          MD_BASE },
        { "=",          MD_EQUAL },
        { "{",          MD_OPEN_BLOCK },
        { "}",          MD_CLOSE_BLOCK },
        { "Sector",     MD_SECTOR },
        { "Tile",       MD_TILE },
        { "tile_size",  MD_TILE_SIZE },
        { "texture",    MD_TEXTURE },
        { "width",      MD_WIDTH },
        { "height",     MD_HEIGHT},
        { "TileModel",  MD_MODEL }
    },
    MD_STRING,
    MD_NUMBER,
    MD_END
};


MapSector* MapParser::loadMap (const std::string& path)
{

}

void MapParser::saveMap (const std::string& path, const MapSector& map_sector)
{}
