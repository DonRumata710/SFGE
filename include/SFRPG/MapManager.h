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
    typedef sf::Rect<uint32_t> UintRect;

    class iResourceInputStream;
    class MapLoader;
    class MapSaver;
    class Way;


    /////////////////////////////////////////////////////////////////////
    /// MapManager - store and manage map sectors
    /////////////////////////////////////////////////////////////////////
    class MapManager : public Drawable
    {
    public:
      
        /////////////////////////////////////////////////////////////////////
        /// getInstance - get instance of created map manager
        ///
        /// @return - instance of map manager
        /////////////////////////////////////////////////////////////////////
        static MapManager* getInstance ();

        /////////////////////////////////////////////////////////////////////
        /// Constructor for loading map from file system
        ///
        /// @param loader - map loader
        /// @param path - path to the map
        /////////////////////////////////////////////////////////////////////
        MapManager (std::shared_ptr<MapLoader> loader, const std::string& path);

        /////////////////////////////////////////////////////////////////////
        /// Constructor for created map
        ///
        /// @param sectors - description of sectors
        /////////////////////////////////////////////////////////////////////
        MapManager (std::unordered_map<uint32_t, MapSectorDesc>&& sectors);

        /////////////////////////////////////////////////////////////////////
        /// Desctuctor
        /////////////////////////////////////////////////////////////////////
        ~MapManager ();

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
        /////////////////////////////////////////////////////////////////////
        bool save (MapSaver* saver);

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
        void setOffset (unsigned x, unsigned y);

        void findWayPointsEdges ();

        std::deque<Vector2f> findWay (const WayPointID& departure, const WayPointID& target) const;

        static float getDistance (Vector2f p1, Vector2f p2);

        static Vector2f getWayStep (const WayPoint* p1, const WayPoint* p2);

        virtual void draw (RenderTarget& target, RenderStates states) const override;

    private:
        std::shared_ptr<MapLoader> m_loader;
        std::unordered_map<uint32_t, MapSectorDesc> m_sectors;
        std::string m_map_path;
        Vector2u m_offset;

    private:
        static MapManager* m_instance;
    };


}
