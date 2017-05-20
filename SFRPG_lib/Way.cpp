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


#include "Way.h"


using namespace sfge;


sfge::Way::Way (const WayPoints& points) :
    m_points (points),
    m_current_point (m_points.begin ())
{}

sfge::Way::Way (WayPoints&& points) :
    m_points (std::move (points)),
    m_current_point (m_points.begin ())
{}

void sfge::Way::clear ()
{
    m_points.clear ();
}

void sfge::Way::pushPointFront (Vector2f point)
{
    m_points.push_front (point);
    m_current_point = m_points.begin ();
}

void sfge::Way::pushPointBack (Vector2f point)
{
    m_points.push_back (point);
    m_current_point = m_points.begin ();
}

Vector2f Way::getMovingVector (Vector2f position, float step)
{
    if (m_current_point == m_points.end ())
        return Vector2f ();

    auto rest_vec (*m_current_point - position);
    float rest_dist (sqrt (rest_vec.x * rest_vec.x + rest_vec.y * rest_vec.y));

    if (step < rest_dist)
    {
        float relation (step / rest_dist);
        return rest_vec * relation;
    }
    else
    {
        step -= rest_dist;
        if (m_current_point != m_points.end ())
            return rest_vec + getMovingVector (*m_current_point++, step);
        else
            return rest_vec;
    }
}

float Way::getLength () const
{
    float sum (0.0f);

    for (size_t i = 0; i < m_points.size () - 1; ++i)
    {
        Vector2f dist (m_points[i] - m_points[i + 1]);
        sum += sqrt (dist.x * dist.x + dist.y * dist.y);
    }

    return sum;
}

size_t Way::getPoints () const
{
    return m_points.size ();
}
