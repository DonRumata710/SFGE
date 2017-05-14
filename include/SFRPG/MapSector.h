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


    class MapSector : public Drawable
    {
    public:
        MapSector () = default;

        ~MapSector () = default;

        void setTiles (const std::vector<Panel>& tiles);

        void setTiles (std::vector<Panel>&& tiles);

        void setWayPoints (const std::vector<WayPoint>& way_points);

        void setWayPoints (std::vector<WayPoint>&& way_points);
        
        void setOffset (Vector2f offset);

        Vector2f getOffset () const;

        void setSize (Vector2f size);

        Vector2f getSize () const;

        bool checkMovement (InteractiveObject* object);

        uint32_t getNearestWayPoint (Vector2f pos) const;

        const WayPoint* getWayPoint (uint32_t id) const;

        void attachObject (std::shared_ptr<MapObject> object);

        void removeObject (const MapObject* object);

        bool isObjectInSector (Vector2f pos) const;

        void connectWayPoints ();

        void connectWayPoints (MapSector* map_sector);

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
    };


}
