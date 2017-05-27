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


#include "MapObject.h"
#include "WayPoint.h"

#include <SFGE/Panel.h>

#include <SFML/Graphics/Drawable.hpp>

#include <unordered_set>


namespace sfge
{


    using sf::Vector2f;
    using sf::RenderStates;
    using sf::Drawable;

    class InteractiveObject;
    class Way;


    /////////////////////////////////////////////////////////////////////
    /// MapSector - sector of map
    ///
    /// Big map consist of map sectors which can be loaded to memory or
    /// unloaded from it.
    /////////////////////////////////////////////////////////////////////
    class MapSector : public Drawable
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        MapSector () = default;

        /////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////
        ~MapSector () = default;

        /////////////////////////////////////////////////////////////////////
        /// setTiles - set tiles to sector
        ///
        /// @param tiles - tiles of sector
        /////////////////////////////////////////////////////////////////////
        void setTiles (const std::vector<Panel>& tiles);

        /////////////////////////////////////////////////////////////////////
        /// setTiles - set tiles to sector
        ///
        /// @param tiles - tiles of sector
        /////////////////////////////////////////////////////////////////////
        void setTiles (std::vector<Panel>&& tiles);

        /////////////////////////////////////////////////////////////////////
        /// setName - set name to the sector
        ///
        /// @param name - name of sector
        /////////////////////////////////////////////////////////////////////
        void setName (const std::string&  name);

        /////////////////////////////////////////////////////////////////////
        /// getName - get name of sector
        ///
        /// @return - name of sector
        /////////////////////////////////////////////////////////////////////
        std::string getName () const;

        /////////////////////////////////////////////////////////////////////
        /// setWayPoints - set way points placed on this map sector
        ///
        /// @param way_points - list of way points
        /////////////////////////////////////////////////////////////////////
        void setWayPoints (const std::vector<WayPoint>& way_points);

        /////////////////////////////////////////////////////////////////////
        /// setWayPoints - set way points placed on this map sector
        ///
        /// @param way_points - list of way points
        /////////////////////////////////////////////////////////////////////
        void setWayPoints (std::vector<WayPoint>&& way_points);
        
        void setOffset (Vector2f offset);

        /////////////////////////////////////////////////////////////////////
        /// getOffset - get offset of sector from current orgin
        ///
        /// Origin may be different from origin of using map.
        ///
        /// @return - sector offset
        /////////////////////////////////////////////////////////////////////
        Vector2f getOffset () const;

        void setSize (Vector2f size);

        /////////////////////////////////////////////////////////////////////
        /// getSize - get size of sector
        ///
        /// @return - size of map_sector
        /////////////////////////////////////////////////////////////////////
        Vector2f getSize () const;

        /////////////////////////////////////////////////////////////////////
        /// checkMovement - check can object stay on its new place or not
        ///
        /// @param object - map object
        ///
        /// @return - true if object can stay on its place, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool checkMovement (InteractiveObject* object);

        /////////////////////////////////////////////////////////////////////
        /// getNearestWayPoint - get nearest to position way point
        ///
        /// @param - position on map
        ///
        /// @return - ifd of nearest way point
        /////////////////////////////////////////////////////////////////////
        uint32_t getNearestWayPoint (Vector2f pos) const;

        /////////////////////////////////////////////////////////////////////
        /// getWayPoint - get way point by id
        ///
        /// @param id - id of way point
        ///
        /// @return - pointer to way point
        /////////////////////////////////////////////////////////////////////
        const WayPoint* getWayPoint (uint32_t id) const;

        /////////////////////////////////////////////////////////////////////
        /// attachObject - attach new object to sector
        ///
        /// @param object - map object
        /////////////////////////////////////////////////////////////////////
        void attachObject (std::shared_ptr<MapObject> object);

        /////////////////////////////////////////////////////////////////////
        /// removeObject -  remove object from sector
        ///
        /// Object will not be destructed here.
        ///
        /// @param object - map object
        /////////////////////////////////////////////////////////////////////
        void removeObject (const MapObject* object);

        /////////////////////////////////////////////////////////////////////
        /// isObjectInSector - check is object placed in this sector or not
        ///
        /// @param pos - position of object
        ///
        /// @return - true if object is in sector, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isObjectInSector (Vector2f pos) const;

        /////////////////////////////////////////////////////////////////////
        /// connectWayPoints - create connections between way points of this sector
        /////////////////////////////////////////////////////////////////////
        void connectWayPoints ();

        /////////////////////////////////////////////////////////////////////
        /// connectWayPoints - create connections between way points of two sectors
        ///
        /// @param map_sector - another sector
        /////////////////////////////////////////////////////////////////////
        void connectWayPoints (MapSector* map_sector);

        /////////////////////////////////////////////////////////////////////
        /// attachNeighbours - find way points which has visual contack with current way point
        ///
        /// @param way_point - way point
        /////////////////////////////////////////////////////////////////////
        void attachNeighbours (WayPoint* way_point) const;

    private:
        virtual void draw (RenderTarget& target, RenderStates states) const override;

        bool checkPass (Vector2f p1, Vector2f p2) const;

    private:
        std::vector<Panel> m_tiles;
        std::vector<std::shared_ptr<MapObject>> m_objects;

        std::vector<WayPoint> m_way_points;

        Vector2f m_offset;
        Vector2f m_size;

        std::string m_name;
    };


}
