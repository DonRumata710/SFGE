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


#include "Collision.h"

#include <cstring>


using namespace sfge;


const float EPSILON = 1e-4f;


Collision::Collision (const Circuit& _points) :
    m_points (_points)
{}

Collision::~Collision ()
{}

void Collision::setPosition (const Point newpos)
{
    m_position = newpos;
}

void Collision::move (const Vector2f vector)
{
    m_position += vector;
}

Point sfge::Collision::getPosition () const
{
    return m_position;
}

void Collision::setPoints (const Circuit& new_points)
{
    m_points.assign (new_points.begin (), new_points.end ());
}

Collision::State Collision::check (const Collision& collision) const
{
    for (int i = 0; i < m_points.size (); ++i)
    {
        auto a_point (m_points[i] + m_position);
        auto b_point ((i == 0 ? *m_points.rbegin () : m_points[i - 1]) + m_position);

        for (int i = 0; i < collision.m_points.size (); ++i)
        {
            auto c_point (collision.m_points[i] + collision.m_position);
            auto d_point ((i == 0 ? *collision.m_points.rbegin () : collision.m_points[i - 1]) + collision.m_position);

            if (!segmentCollision (a_point, b_point, c_point, d_point))
                return State::INTERSECTION;
        }
    }

    return isPointInside (collision.m_points[0] + collision.m_position) ? State::INSIDE : State::OUTSIDE;
}

Collision::State Collision::check (const Point p1, const Point p2) const
{
    for (int i = 0; i < m_points.size (); ++i)
    {
        if (!segmentCollision (m_points[i], (i == m_points.size () - 1) ? m_points[0] : m_points[i + 1], p1, p2))
            return State::INTERSECTION;
    }

    return State::OUTSIDE;
}

Collision::State Collision::check (const Point point) const
{
    return isPointInside (point) ? State::INSIDE : State::OUTSIDE;
}

bool Collision::segmentCollision (const Point a, const Point b, const Point c, const Point d) const
{
    float side_a (sign (a, c, d));
    float side_b (sign (b, c, d));

    float side_c (sign (c, a, b));
    float side_d (sign (d, a, b));

    if (((side_a < -EPSILON && side_b > EPSILON) || (side_a > EPSILON && side_b < -EPSILON)) &&
        ((side_c < -EPSILON && side_d > EPSILON) || (side_c > EPSILON && side_d < -EPSILON))
    )
        return false;
    
    return true;
}

bool sfge::Collision::isPointInside (Point p) const
{
    bool flag (sign (p, *m_points.rbegin () + m_position, m_points[0] + m_position) < 0.0f);

    for (size_t i = 0; i < m_points.size () - 1; ++i)
    {
        if (flag != sign (p, m_points[i] + m_position, m_points[i + 1] + m_position) < 0.0f)
            return false;
    }

    return true;
}

float Collision::sign (Point p1, Point p2, Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p1.y - p3.y) * (p2.x - p3.x);
}
