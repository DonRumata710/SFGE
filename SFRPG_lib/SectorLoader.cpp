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


#include "SectorLoader.h"

#include "SFGE/TextParser.h"
#include "SFGE/Err.h"


using namespace sfge;


enum SectorDescritpion : size_t
{
    MD_NONE, MD_END, MD_NUMBER, MD_STRING, MD_EQUAL,
    MD_OPEN_BLOCK, MD_CLOSE_BLOCK,
    MD_SECTOR,
    MD_NAME, MD_TILE_SIZE, MD_SIZE,
    MD_TILE,
    MD_TEXTURE, MD_X, MD_Y
};


const SemanticsDescription SectorLoader::m_sem_desc = {
    {
        { "=",          MD_EQUAL },
        { "{",          MD_OPEN_BLOCK },
        { "}",          MD_CLOSE_BLOCK },
        { "Sector",     MD_SECTOR },
        { "name",       MD_NAME },
        { "tile_size",  MD_TILE_SIZE },
        { "Tile",       MD_TILE },
        { "texture",    MD_TEXTURE },
        { "x",          MD_X },
        { "y",          MD_Y },
    },
    {
        '_'
    },
    MD_STRING,
    MD_NUMBER,
    MD_END
};


SectorLoader::SectorLoader (iResourceInputStream* stream) : m_stream (stream)
{}

void SectorLoader::loadSectors (const std::vector<MapSectorDesc*>& sectors)
{
    for (MapSectorDesc* sector_desc : sectors)
    {
        if (!m_stream->open (sector_desc->path))
        {
            runtime_message ("Failed loading map sector from file " + sector_desc->path);
            break;
        }

        uint64_t size (m_stream->getSize ());
        char* data = new char[size];
        m_stream->read (data, size);
        data[size - 1] = '\0';

        TextParser* tp = new TextParser (data, m_sem_desc);

        tp->getToken ();
        if (tp->getTokentype () != MD_SECTOR)
        {
            runtime_message ("Wrong map sector description in file " + sector_desc->path);
            return;
        }

        std::unique_ptr<MapSector> sector (std::make_unique<MapSector> (sector_desc->size));
        if (!loadMapSector (tp, sector.get ()))
            runtime_message ("Failed including named " + std::string (tp->tknString ()) + " failed!");
        sector_desc->sector.swap (sector);
        break;
    }
}

bool SectorLoader::loadMapSector (TextParser* tp, MapSector* sector)
{
    if (!sector)
        return false;

    tp->getToken ();
    if (tp->getTokentype () != MD_OPEN_BLOCK)
    {
        runtime_message ("Unexpected identifier instead '{' in line " + std::to_string (tp->getLine ()));
        return false;
    }

    Uint32 sector_width = sector->getSize ().x;

    std::vector<std::pair<uint32_t, std::string>> tiles;

    while (true)
    {
        tp->getToken ();
        size_t token (tp->getTokentype ());

        if (token == MD_CLOSE_BLOCK)
            break;

        switch (token)
        {
        case MD_NAME:
            tp->getToken ();
            tp->getToken ();
            sector->setName (tp->tknString ());
            break;
        case MD_TILE_SIZE:
            tp->getToken ();
            tp->getToken ();
            sector->setTileSize (tp->tknInt ());
            break;
        case MD_TILE:
            tiles.push_back (loadTile (tp, sector_width));
            break;
        default:
            runtime_message ("Unexpected identifier in segment description in line " + std::to_string (tp->getLine ()));
            return false;
        }
    }

    sector->setTiles (tiles);
    return true;
}

std::pair<uint32_t, std::string> SectorLoader::loadTile (TextParser* tp, Uint32 sector_width)
{
    tp->getToken ();

    std::pair<uint32_t, std::string> tile_desc;

    tp->getToken ();
    if (tp->getTokentype () == MD_OPEN_BLOCK)
    {
        while (true)
        {
            tp->getToken ();
            size_t token (tp->getTokentype ());

            if (token == MD_CLOSE_BLOCK)
                break;

            switch (token)
            {
            case MD_TEXTURE:
                tp->getToken ();
                tp->getToken ();
                tile_desc.second = tp->tknString ();
                break;
            case MD_X:
                tp->getToken ();
                tp->getToken ();
                tile_desc.first += tp->tknInt ();
                break;
            case MD_Y:
                tp->getToken ();
                tp->getToken ();
                tile_desc.first += tp->tknInt () * sector_width;
                break;
            default:
                runtime_message ("Unexpected identifier in tile description in line " + std::to_string (tp->getLine ()));
                return std::pair<uint32_t, std::string> ();
            }
        }
    }

    return tile_desc;
}
