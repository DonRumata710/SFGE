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


const float epsilon = 1e-4f;


Position& operator+= (Position& p1, const Position p2)
{
    p1.first += p2.first;
    p1.second += p2.second;
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

void Collision::move (const Position newpos)
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

bool Collision::segmentCollision (const Position a, const Position b, const Position c, const Position d)
{
    float side_a ((a.first - c.first) * (d.second - c.second) - (a.second - c.second) * (d.first - c.first));
    float side_b ((b.first - c.first) * (d.second - c.second) - (b.second - c.second) * (d.first - c.first));

    float side_c ((c.first - a.first) * (b.second - a.second) - (c.second - a.second) * (b.first - a.first));
    float side_d ((d.first - a.first) * (b.second - a.second) - (d.second - a.second) * (b.first - a.first));

    if (((side_a < -epsilon && side_b > epsilon) || (side_a > epsilon && side_b < -epsilon)) &&
        ((side_c < -epsilon && side_d > epsilon) || (side_c > epsilon && side_d < -epsilon))
    )
        return false;
    
    return true;
}
