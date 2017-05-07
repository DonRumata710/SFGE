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


#include <SFML\System\Vector2.hpp>

#include <unordered_map>


namespace sfge
{


    using sf::Vector2f;


    class WayPoint
    {
    public:
        WayPoint (uint32_t id, uint32_t map_id);

        void setPosition (Vector2f pos);

        Vector2f getPosition () const;

        void setRadius (float r);

        float getRadius () const;

        Vector2f getRoute (const WayPoint* const target) const;

        const WayPoint* getNextPoint (const WayPoint* const target) const;

        float checkArea (const Vector2f point) const;

    private:
        Vector2f m_position;
        float m_radius = 0.0f;

        std::unordered_map<const WayPoint*, std::pair<Vector2f, const WayPoint*>> m_neighbours;

        uint32_t m_id = UINT32_MAX;
        uint32_t m_map_id = UINT32_MAX;
    };


}
