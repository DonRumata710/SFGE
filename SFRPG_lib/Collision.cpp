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


using namespace sfge;


const float epsilon = 1e-4f;


Point& operator+= (Point& p1, const Point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}


Collision::Collision (const Circuit& _points) :
    points (_points)
{}

Collision::~Collision ()
{}

void Collision::setPoints (const Circuit& new_points)
{
    points.assign (new_points.begin (), new_points.end ());
}

void Collision::move (const Point newpos)
{
    for (auto point : points)
    {
        point += newpos;
    }
}

bool Collision::check (const Collision& collision)
{
    for (int i = 0; i < points.size (); ++i)
    {
        auto a_point (points[i]);
        auto b_point (i == 0 ? *points.rbegin () : points[i - 1]);

        for (int i = 0; i < collision.points.size (); ++i)
        {
            auto c_point (collision.points[i]);
            auto d_point (i == 0 ? *collision.points.rbegin () : collision.points[i - 1]);

            if (!segmentCollision (a_point, b_point, c_point, d_point))
                return false;
        }
    }

    return true;
}

bool sfge::Collision::check (Point point)
{
    for (int i = 0; i < points.size (); ++i)
    {
        auto a_point (i == 0 ? *points.rbegin () : points[i - 1]);
        auto b_point (points[i]);
        auto c_point (i == (points.size () - 1) ? points[0] : points[i + 1]);

        if (isPointInTriangle (a_point, b_point, c_point, point))
            return true;
    }

    return false;
}

bool Collision::segmentCollision (const Point a, const Point b, const Point c, const Point d)
{
    float side_a ((a.x - c.x) * (d.y - c.y) - (a.y - c.y) * (d.x - c.x));
    float side_b ((b.x - c.x) * (d.y - c.y) - (b.y - c.y) * (d.x - c.x));

    float side_c ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
    float side_d ((d.x - a.x) * (b.y - a.y) - (d.y - a.y) * (b.x - a.x));

    if (((side_a < -epsilon && side_b > epsilon) || (side_a > epsilon && side_b < -epsilon)) &&
        ((side_c < -epsilon && side_d > epsilon) || (side_c > epsilon && side_d < -epsilon))
    )
        return false;
    
    return true;
}

float Collision::sign (Point p1, Point p2, Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool sfge::Collision::isPointInTriangle (Point triangle_a, Point triangle_b, Point triangle_c, Point point)
{
    bool b1, b2, b3;

    b1 = sign (point, triangle_a, triangle_b) < 0.0f;
    b2 = sign (point, triangle_b, triangle_c) < 0.0f;
    b3 = sign (point, triangle_c, triangle_a) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}
