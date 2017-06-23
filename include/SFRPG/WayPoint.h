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
#include <vector>


namespace sfge
{


    using sf::Vector2f;


    struct WayPointID
    {
        uint32_t m_id = UINT32_MAX;
        uint32_t m_map_id = UINT32_MAX;

        WayPointID () = default;
        WayPointID (uint32_t map_id, uint32_t id);
    };


    class WayPoint
    {
    public:
        typedef std::vector<const WayPoint*> EdgeList;

        void assignEdges (const EdgeList& edges);

        const EdgeList& getEdges () const;

        void setPosition (Vector2f pos);

        Vector2f getPosition () const;

        void setRadius (float r);

        float getRadius () const;

        float checkArea (const Vector2f point) const;

    private:
        Vector2f m_position;
        float m_radius = 0.0f;

        EdgeList m_neighbours;
    };


}
