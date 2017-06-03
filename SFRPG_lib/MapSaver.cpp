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


#include "MapSaver.h"
#include "MapManager.h"
#include "MapSectorDesc.h"

#include <SFGE/Err.h>


using namespace sfge;


MapSaver::MapSaver (iDataOutputStream* output_stream) :
    m_output_stream (output_stream)
{}

bool MapSaver::saveMap (MapManager* manager, const std::string& path)
{
    if (!m_output_stream->open (path))
    {
        runtime_error ("Can not save map to file " + path);
        return false;
    }

    if (!m_output_stream->write ("Map\n{\n", 6))
    {
        debug_message ("Failed writing open block of map " + path);
        return false;
    }

    if (!manager->save (this))
    {
        debug_message ("Failed saving map " + path);
        return false;
    }

    if (!m_output_stream->write ("}\n", 2))
    {
        debug_message ("Failed writing close block of map " + path);
        return false;
    }

    return manager->saveSectors (this);
}

bool MapSaver::saveSectorDescription (Uint32 id, const MapSectorDesc& desc)
{
    if (!m_output_stream->write ("Sector ", 7))
    {
        debug_message ("Failed writing header of sector description " + desc.path);
        return false;
    }

    std::string str_id (std::to_string (id));
    m_output_stream->write (str_id.data (), str_id.size ());

    if(!m_output_stream->write ("\n{\n", 3))
    {
        debug_message ("Failed writing open block of sector description " + desc.path);
        return false;
    }

    save ("path", desc.path);
    save ("x", (Uint64) desc.pos.x);
    save ("y", (Uint64) desc.pos.y);
    save ("width", (Uint64) desc.size.x);
    save ("height", (Uint64) desc.size.y);

    if (!m_output_stream->write ("}\n", 2))
    {
        debug_message ("Failed writing close block of sector description " + desc.path);
        return false;
    }

    return true;
}

bool MapSaver::saveSector (MapSector* sector, const std::string& path)
{
    if (!m_output_stream->open (path))
    {
        runtime_error ("Can not save sector to file " + path);
        return false;
    }

    if (!m_output_stream->write ("Sector\n{\n", 9))
    {
        debug_message ("Failed writing open block of sector " + path);
        return false;
    }

    if (!sector->save (this))
    {
        debug_message ("Failed saving sector " + path);
        return false;
    }

    if (!m_output_stream->write ("}\n", 2))
    {
        debug_message ("Failed writing close block of sector " + path);
        return false;
    }

    return true;
}

bool MapSaver::saveTile (const std::string& texture, const Vector2u pos)
{
    if (!m_output_stream->write ("Tile\n{\n", 6))
    {
        debug_message ("Failed writing header of tile");
        return false;
    }

    save ("x", pos.x);

    save ("y", pos.y);

    save ("texture", texture);

    if (!m_output_stream->write ("}\n", 2))
    {
        debug_message ("Failed writing close block of tile");
        return false;
    }

    return true;
}

bool MapSaver::save (const std::string& name, const std::string& str)
{
    const std::string data = name + "=\"" + str + "\"\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string& name, const Int64 val)
{
    const std::string data = name + "=" + std::to_string (val) + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string & name, const Uint64 val)
{
    const std::string data = name + "=" + std::to_string (val) + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string & name, const Int32 val)
{
    const std::string data = name + "=" + std::to_string (val) + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string & name, const Uint32 val)
{
    const std::string data = name + "=" + std::to_string (val) + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string & name, const double val)
{
    const std::string data = name + "=" + std::to_string (val) + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}

bool MapSaver::save (const std::string & name, const bool val)
{
    const std::string data = name + "=" + std::string (val ? "True" : "False") + "\n";
    return m_output_stream->write (data.data (), data.size ()) > 0;
}
