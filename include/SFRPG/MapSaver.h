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


#include <SFGE/DataOutputStream.h>

#include <SFML/System/Vector2.hpp>

#include <string>


namespace sfge
{


    using sf::Vector2u;

    class MapManager;
    class MapSector;
    struct MapSectorDesc;


    class MapSaver
    {
    public:
        MapSaver (iDataOutputStream* output_stream);

        bool saveMap (MapManager* manager, const std::string& path);

        bool saveSectorDescription (Uint32 id, const MapSectorDesc& desc);

        bool saveSector (MapSector*, const std::string& path);

        bool saveTile (const std::string& texture, const Vector2u pos);

        bool save (const std::string& name, const std::string& str);
        bool save (const std::string& name, const Int64 val);
        bool save (const std::string& name, const Uint64 val);
        bool save (const std::string& name, const Int32 val);
        bool save (const std::string& name, const Uint32 val);
        bool save (const std::string& name, const double val);
        bool save (const std::string& name, const bool val);

    private:
        iDataOutputStream* m_output_stream;
    };


}