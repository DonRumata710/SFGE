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


#include "MapLoader.h"
#include "MapSegmentDesc.h"
#include "MapParser.h"

#include <SFGE/TextParser.h>
#include <SFGE/Err.h>


using namespace sfge;


const SemanticsDescription MapLoader::m_sem_desc = {
    {
        { ":",          MD_BASE },
        { "=",          MD_EQUAL },
        { "{",          MD_OPEN_BLOCK },
        { "}",          MD_CLOSE_BLOCK },
        { "Map",        MD_MAP },
        { "Name",       MD_NAME },
        { "Sector",     MD_SECTOR },
        { "id",         MD_ID },
        { "path",       MD_PATH },
        { "tile_size",  MD_TILE_SIZE },
        { "Model",      MD_MODEL },
        { "Tile",       MD_TILE },
        { "texture",    MD_TEXTURE },
        { "x",          MD_X },
        { "y",          MD_Y },
        { "width",      MD_WIDTH },
        { "height",     MD_HEIGHT }
    },
    MD_STRING,
    MD_NUMBER,
    MD_END
};


MapLoader::MapLoader (std::shared_ptr<ResourceInputStream> stream)
    : m_file_stream (stream)
{}

std::unordered_map<uint32_t, MapSegmentDesc> MapLoader::getSegmentDescriptions (const std::string& path)
{
    TextParser* tp = new TextParser (loadScript (path), m_sem_desc);

    std::unordered_map<uint32_t, MapSegmentDesc> sectors;

    tp->getToken ();
    size_t token (tp->getTokentype ());
    if (token != MD_MAP && token != MD_SECTOR)
    {
        runtime_error ("Wrong file in map loading");
        return sectors;
    }

    tp->getToken ();
    if (tp->getTokentype () != MD_OPEN_BLOCK)
    {
        runtime_error ("Unexpected identifier in map description file");
        return sectors;
    }

    if (token == MD_MAP)
        parseMap (tp, &sectors);
    else
    {
        sectors[0];
        sectors[0].path = path;
    }

    return sectors;
}

void MapLoader::loadMap (const std::vector<MapSegmentDesc*>& sectors)
{
    for (MapSegmentDesc* sector_desc : sectors)
    {
        TextParser* tp = new TextParser (loadScript (sector_desc->path), m_sem_desc);

        while (true)
        {
            MapParser parser (m_tile_models);

            tp->getToken ();
            size_t token (tp->getTokentype ());
            switch (token)
            {
            case MD_SECTOR:
            {
                std::unique_ptr<MapSector> sector (std::make_unique<MapSector> ());
                if (!parser.loadMapSector (tp, sector.get ()))
                    runtime_error ("Including script named " + std::string (tp->tknString ()) + " failed!");
                sector_desc->sector.swap (sector);
                break;
            }
            case MD_MODEL:
                if (!parser.loadTileModel (tp))
                    runtime_error ("Parsing model " + std::string (tp->tknString ()) + " failed!");
                break;
            case MD_END:
                return;
            default:
                runtime_error ("Error in map description in line " + std::to_string (tp->getLine ()));
                return;
            }
        }
    }
}

const char* MapLoader::loadScript (const std::string& path)
{
    m_file_stream->open (path);

    uint64_t size (m_file_stream->getSize ());
    char* data = new char[size];
    m_file_stream->read (data, size);

    return data;
}

bool MapLoader::parseMap (TextParser* tp, std::unordered_map<uint32_t, MapSegmentDesc>* sectors)
{
    while (true)
    {
        tp->getToken ();
        if (tp->getTokentype () == MD_CLOSE_BLOCK)
        {
            break;
        }

        size_t token (tp->getTokentype ());

        switch (token)
        {
        case MD_NAME:
            tp->getToken ();
            tp->getToken ();
            m_map_name = tp->tknString ();
            break;
        case MD_SECTOR:
        {
            do
            {
                tp->getToken ();
                if (tp->getTokentype () == MD_END)
                {
                    runtime_error ("Unexpected end of map description file in line: " + std::to_string (tp->getLine ()));
                    return false;
                }
            }
            while (tp->getTokentype () != MD_OPEN_BLOCK);

            while (true)
            {
                tp->getToken ();
                size_t token (tp->getTokentype ());

                if (token == MD_CLOSE_BLOCK)
                    break;

                switch (token)
                {
                case MD_ID:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[tp->tknHex ()];
                    break;
                case MD_PATH:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[tp->tknHex ()].path = tp->tknString ();
                    break;
                }
            }
            break;
        }
        case MD_MODEL:
        {
            MapParser parser (m_tile_models);
            if (!parser.loadTileModel (tp))
                runtime_error ("Parsing model " + std::string (tp->tknString ()) + " failed!");
            break;
        }
        default:
            runtime_error ("Unexpected identifier in map description file in line: " + std::to_string (tp->getLine ()));
            break;
        }
    }

    return true;
}
