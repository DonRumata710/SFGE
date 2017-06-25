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


#include "MapSectorDesc.h"

#include <SFML/System/Vector2.hpp>

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>


namespace sfge
{


    using sf::Vector2f;
    using sf::Vector2i;
    typedef sf::Rect<uint32_t> UintRect;

    class MapLoader;
    class MapSaver;
    class SectorLoader;
    class Way;


    /////////////////////////////////////////////////////////////////////
    /// MapManager - store and manage map sectors
    /////////////////////////////////////////////////////////////////////
    class MapManager : public Drawable
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        MapManager ();

        /////////////////////////////////////////////////////////////////////
        /// Desctuctor
        /////////////////////////////////////////////////////////////////////
        ~MapManager ();

        /////////////////////////////////////////////////////////////////////
        /// setMapDescription - set description of map
        ///
        /// @param - description of map sectors
        /////////////////////////////////////////////////////////////////////
        void setMapDescription (std::unordered_map<uint32_t, MapSectorDesc>&& sectors);

        /////////////////////////////////////////////////////////////////////
        /// setName - set name of the map
        ///
        /// @param name - name of map
        /////////////////////////////////////////////////////////////////////
        void setName (const std::string& name);

        /////////////////////////////////////////////////////////////////////
        /// getName - get name of map
        ///
        /// @return - name of map
        /////////////////////////////////////////////////////////////////////
        std::string getName () const;

        /////////////////////////////////////////////////////////////////////
        /// setLoader - set loader of map
        ///
        /// This map loader will load all sectors for map manager
        ///
        /// @param loader - pointer to loader
        /////////////////////////////////////////////////////////////////////
        void setLoader (std::unique_ptr<SectorLoader>&& loader);

        /////////////////////////////////////////////////////////////////////
        /// lookMap - load all sectors which contain current areas
        ///
        /// This method describe the manager what sectors should be loaded to
        /// the memory from resource files.
        ///
        /// @param areas - areas on the  map
        /////////////////////////////////////////////////////////////////////
        void lookMap (const std::vector<UintRect>& areas);

        /////////////////////////////////////////////////////////////////////
        /// save - save map
        ///
        /// @param saver - saver
        /////////////////////////////////////////////////////////////////////
        bool save (MapSaver* saver);

        /////////////////////////////////////////////////////////////////////
        /// saveSectors - save sectors
        ///
        /// @param saver - saver
        /////////////////////////////////////////////////////////////////////
        bool saveSectors (MapSaver* saver);

        /////////////////////////////////////////////////////////////////////
        /// getWay - find way from one point to another
        ///
        /// @param departure - departure point
        /// @param target - target point
        ///
        /// @return way from one point to another
        /////////////////////////////////////////////////////////////////////
        Way getWay (Vector2f departure, Vector2f target) const;

        /////////////////////////////////////////////////////////////////////
        /// getSector - get sector of current point
        ///
        /// @param position - current point
        ///
        /// @return current sector
        /////////////////////////////////////////////////////////////////////
        MapSector* getSector (Vector2f position);

    private:
        void setOffset (int32_t x, int32_t y);

        void findWayPointsEdges (MapSector* sector);

        std::deque<Vector2f> findWay (const WayPointID& departure, const WayPointID& target) const;

        static float getDistance (Vector2f p1, Vector2f p2);

        static Vector2f getWayStep (const WayPoint* p1, const WayPoint* p2);

        virtual void draw (RenderTarget& target, RenderStates states) const override;

    private:
        std::string m_name;
        std::unique_ptr<SectorLoader> m_loader;
        std::unordered_map<uint32_t, MapSectorDesc> m_sectors;
        std::string m_map_path;
        Vector2i m_offset;
    };


}
