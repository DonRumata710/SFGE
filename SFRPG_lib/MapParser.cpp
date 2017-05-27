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


#include "MapParser.h"
#include "MapSector.h"

#include <SFGE/Panel.h>
#include <SFGE/TextParser.h>
#include <SFGE/Err.h>


using namespace sfge;


MapParser::MapParser (const std::unordered_map<std::string, TileDesc>& ext_models) :
    m_models (ext_models)
{}

bool MapParser::loadMapSector (TextParser* tp, MapSector* sector)
{
    if (!sector)
        return false;

    tp->getToken ();
    if (tp->getTokentype () != MD_OPEN_BLOCK)
    {
        runtime_error ("Unexpected identifier instead '{' in line " + std::to_string (tp->getLine ()));
        return false;
    }

    std::vector<Panel> tiles;

    while (true)
    {
        tp->getToken ();
        size_t token (tp->getTokentype ());

        if (token == MD_CLOSE_BLOCK)
            break;

        switch (token)
        {
        case MD_TILE_SIZE:
            tp->getToken ();
            tp->getToken ();
            m_tile_size = tp->tknFloat ();
            break;
        case MD_NAME:
            tp->getToken ();
            tp->getToken ();
            sector->setName (tp->tknString ());
        case MD_TILE:
            tiles.push_back (loadTile (tp));
            break;
        case MD_MODEL:
            if (!loadTileModel (tp))
                runtime_error ("Failed parsing tile model in line " + std::to_string (tp->getLine ()));
            break;
        default:
            runtime_error ("Unexpected identifier in segment description in line " + std::to_string(tp->getLine ()));
            return false;
        }
    }

    sector->setTiles (tiles);
    return true;
}

bool MapParser::loadTileModel (TextParser* tp)
{
    tp->getToken ();
    std::string name = tp->tknString ();
    TileDesc* tile (&m_models[name]);

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
                tile->texture = tp->tknString ();
                break;
            case MD_WIDTH:
                tp->getToken ();
                tp->getToken ();
                tile->width = tp->tknInt () * m_tile_size;
                break;
            case MD_HEIGHT:
                tp->getToken ();
                tp->getToken ();
                tile->height = tp->tknInt () * m_tile_size;
                break;
            default:
                runtime_error ("Unexpected identifier in tile model description in line " + std::to_string (tp->getLine ()));
                return false;
            }
        }
    }

    return true;
}

Panel MapParser::loadTile (TextParser* tp)
{
    Panel tile;
    tp->getToken ();

    sfge::Vector2f pos;
    sfge::Vector2f size;

    if (tp->getTokentype () == MD_BASE)
    {
        tp->getToken ();
        std::string base_model (tp->tknString ());
        auto model (m_models[base_model]);
        tile.setTexture (model.texture);
        size.x = model.width;
        size.y = model.height;
    }

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
                tile.setTexture (tp->tknString ());
                break;
            case MD_X:
                tp->getToken ();
                tp->getToken ();
                pos.x = tp->tknInt () * m_tile_size;
                break;
            case MD_Y:
                tp->getToken ();
                tp->getToken ();
                pos.y = tp->tknInt () * m_tile_size;
                break;
            case MD_WIDTH:
                tp->getToken ();
                tp->getToken ();
                size.x = tp->tknInt () * m_tile_size;
                break;
            case MD_HEIGHT:
                tp->getToken ();
                tp->getToken ();
                size.y = tp->tknInt () * m_tile_size;
                break;
            default:
                runtime_error ("Unexpected identifier in tile description in line " + std::to_string (tp->getLine ()));
                return false;
            }
        }
    }
    
    tile.setPosition (pos);
    tile.setSize (size);
    return tile;
}
