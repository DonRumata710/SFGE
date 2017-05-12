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


#include "MapSector.h"

#include <SFGE/Widget.h>

#include "SFML/System/Vector2.hpp"

#include <deque>


namespace sfge
{


    using sf::Vector2f;

    class Way;


    class Map : public sfge::iWidget
    {
    public:
        Way getWay (Vector2f departure, Vector2f target) const;

        MapSector* getSector (Vector2f position);

    private:
        virtual void draw (RenderTarget& target) const override;

        std::deque<Vector2f> findWay (const WayPointID& departure, const WayPointID& target) const;

        static float getDistance (Vector2f p1, Vector2f p2);

        static Vector2f getWayStep (const WayPoint* p1, const WayPoint* p2);

    private:
        std::unordered_map<uint32_t, MapSector> m_sectors;
    };


}
