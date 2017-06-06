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
#include "MapSectorDesc.h"
#include "MapManager.h"
#include "SectorLoader.h"

#include <SFGE/TextParser.h>
#include <SFGE/Err.h>


using namespace sfge;


enum MapDescritpion : size_t
{
    MD_NONE, MD_END, MD_NUMBER, MD_STRING, MD_EQUAL,
    MD_OPEN_BLOCK, MD_CLOSE_BLOCK,
    MD_MAP,
    MD_NAME,
    MD_SECTOR,
    MD_TILE_SIZE, MD_PATH, MD_SIZE,
    MD_TILE,
    MD_TEXTURE, MD_X, MD_Y, MD_WIDTH, MD_HEIGHT
};


const SemanticsDescription MapLoader::m_sem_desc = {
    {
        { "=",          MD_EQUAL },
        { "{",          MD_OPEN_BLOCK },
        { "}",          MD_CLOSE_BLOCK },
        { "Map",        MD_MAP },
        { "name",       MD_NAME },
        { "Sector",     MD_SECTOR },
        { "path",       MD_PATH },
        { "x",          MD_X },
        { "y",          MD_Y },
        { "width",      MD_WIDTH },
        { "height",     MD_HEIGHT }
    },
    {
        '_'
    },
    MD_STRING,
    MD_NUMBER,
    MD_END
};


MapLoader::MapLoader (iResourceInputStream* stream)
    : m_file_stream (stream)
{}

bool MapLoader::loadMap (MapManager* manager, const std::string& path)
{
    if (!manager)
    {
        debug_message ("Empty map pointer was received in map loader");
        return false;
    }

    manager->setLoader (std::make_unique<SectorLoader> (m_file_stream));

    TextParser* tp = new TextParser (loadScript (path), m_sem_desc);

    std::unordered_map<uint32_t, MapSectorDesc> sectors;

    tp->getToken ();
    size_t token (tp->getTokentype ());
    if (token != MD_MAP && token != MD_SECTOR)
    {
        runtime_error ("Wrong file in map loading");
        return false;
    }

    tp->getToken ();
    if (tp->getTokentype () != MD_OPEN_BLOCK)
    {
        runtime_error ("Unexpected identifier in map description file " + path);
        return false;
    }

    if (token == MD_MAP)
        manager->setName (parseMap (tp, &sectors));
    else
    {
        sectors[0].path = path;

        do
        {
            tp->getToken ();
            if (tp->getTokentype () == MD_END)
            {
                runtime_error ("Unexpected end of map description file " + path + " in line: " + std::to_string (tp->getLine ()));
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
            case MD_NAME:
                tp->getToken ();
                tp->getToken ();
                manager->setName (tp->tknString ());
                break;
            default:
                break;
            }
        }
    }

    manager->setMapDescription (std::move (sectors));

    return true;
}

const char* MapLoader::loadScript (const std::string& path)
{
    if (!m_file_stream->open (path))
        return nullptr;

    uint64_t size (m_file_stream->getSize ());
    char* data = new char[size];
    m_file_stream->read (data, size);
    data[size - 1] = '\0';

    return data;
}

std::string MapLoader::parseMap (TextParser* tp, std::unordered_map<uint32_t, MapSectorDesc>* sectors)
{
    std::string name;

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
            name = tp->tknString ();
            break;
        case MD_SECTOR:
        {
            Uint32 sector_id (0);

            tp->getToken ();
            if (tp->getTokentype () == MD_NUMBER)
                sector_id = tp->tknInt ();
            else
            {
                runtime_error ("No sector id was found");
                return "";
            }

            do
            {
                tp->getToken ();
                if (tp->getTokentype () == MD_END)
                {
                    runtime_error ("Unexpected end of map description file in line: " + std::to_string (tp->getLine ()));
                    return "";
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
                case MD_PATH:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[sector_id].path = tp->tknString ();
                    break;
                case  MD_X:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[sector_id].pos.x = tp->tknInt ();
                    break;
                case  MD_Y:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[sector_id].pos.y = tp->tknInt ();
                    break;
                case  MD_WIDTH:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[sector_id].size.x = tp->tknInt ();
                    break;
                case  MD_HEIGHT:
                    tp->getToken ();
                    tp->getToken ();
                    (*sectors)[sector_id].size.y = tp->tknInt ();
                    break;
                case MD_END:
                    runtime_error ("Unexpected end of description " + name + " in line " + std::to_string (tp->getLine ()));
                    return "";
                }
            }
            break;
        }
        default:
            runtime_error ("Unexpected identifier in map description file in line: " + std::to_string (tp->getLine ()));
            break;
        }
    }

    return name;
}
