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


Way::Way (const std::vector<const WayPoint*>& points, Vector2f target) :
    m_points (points), m_target (target)
{}

Vector2f Way::getMovingVector (Vector2f position, float step)
{
    Vector2f target;

    if (m_current_point == m_points.size () - 1)
        target = m_target;
    else
        target = m_points[m_current_point]->getRoute (m_points[m_current_point + 1]);

    auto rest_vec (target - position);
    float rest_dist (sqrt (rest_vec.x * rest_vec.x + rest_vec.y * rest_vec.y));

    if (step > rest_dist)
    {
        float relation (step / rest_dist);
        return rest_vec * relation;
    }
    else
    {
        step -= rest_dist;
        return rest_vec + getMovingVector (target, step);
    }
}
