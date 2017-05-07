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

#include <SFGE/Widget.h>
#include <SFGE/Panel.h>

#include <vector>


namespace sfge
{


    using sf::Vector2f;

    class InteractiveObject;
    class Way;


    class Map final : public sfge::iWidget
    {
    public:
        explicit Map (uint32_t id);

        virtual ~Map ();

        bool checkMovement (InteractiveObject* object) const;

        Way getWay (Vector2f departure, Vector2f target) const;

    private:
        virtual void draw (sfge::RenderTarget& target) const override;

        const WayPoint* getNearestWayPoint (Vector2f pos) const;

    private:
        std::vector<Panel> m_tiles;
        std::vector<WayPoint> m_way_points;
        std::vector<std::shared_ptr<MapObject>> m_objects;

        Vector2f m_size;

        uint32_t m_id = UINT32_MAX;
    };


}
