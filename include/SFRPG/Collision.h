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

#include <vector>
#include <utility>


namespace sfge
{

    
    using sf::Vector2f;

    typedef Vector2f Point;
    typedef std::vector<Point> Circuit;


    class Collision
    {
    public:
        enum class State
        {
            INTERSECTION,
            INSIDE,
            OUTSIDE
        };

        Collision () = default;

        explicit Collision (const Circuit& points);

        ~Collision ();

        void setPosition (const Point pos);

        void move (const Vector2f vector);

        Point getPosition () const;

        void setPoints (const Circuit& points);

        State check (const Collision& collision) const;

        State check (const Point p1, const Point p2) const;

        State check (const Point point) const;

    private:
        bool segmentCollision (const Point a, const Point b, const Point c, const Point d) const;

        bool isPointInside (Point p) const;

        static float sign (Point p1, Point p2, Point p3);

    private:
        Circuit m_points;
        Point m_position;
    };


}
