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


#include "WayPoint.h"


using namespace sfge;


sfge::WayPointID::WayPointID (uint32_t map_id, uint32_t id) :
    m_map_id (map_id), m_id (id)
{}


WayPoint::WayPoint (uint32_t map_id) : m_map_id (map_id)
{}

void WayPoint::setPosition (Vector2f pos)
{
    m_position = pos;
}

Vector2f WayPoint::getPosition () const
{
    return m_position;
}

void WayPoint::setRadius (float r)
{
    m_radius = r;
}

float WayPoint::getRadius () const
{
    return m_radius;
}

float WayPoint::checkArea (const Vector2f point) const
{
    Vector2f vec_dist (m_position - point);
    float distance (sqrt (vec_dist.x * vec_dist.x + vec_dist.y * vec_dist.y));

    if (distance < m_radius)
        return distance;
    else
        return FLT_MAX;
}

const WayPoint::EdgeList& WayPoint::getEdges () const
{
    return m_neighbours;
}
