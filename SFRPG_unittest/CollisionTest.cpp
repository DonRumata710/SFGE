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


#include <SFRPG/Collision.h>

#include <catch.hpp>

#include <random>


using namespace sfge;


TEST_CASE ("Test successful collisions")
{
    Collision c1;
    Collision c2;

    Circuit points1;
    Circuit points2;

    SECTION ("1")
    {
        points1.assign ({ { 0.0, 0.0 }, { 0.0, 10.0 }, { 10.0, 0.0 } });
        points2.assign ({ { 0.0, 11.0 }, { 10.0, 1.0 }, { 10.0, 11.0 } });
    }

    SECTION ("2")
    {
        points1.assign ({ { 0.0, 0.0 }, { 0.0, 10.0 }, { 10.0, 0.0 } });
        points2.assign ({ { 0.0, 11.0 }, { 10.0, 1.0 }, { 10.0, 11.0 } });
    }

    SECTION ("3")
    {
        points1.assign ({ { 0.0, 10.0 }, { 10.0, 10.0 }, { 10.0, 0.0 }, { 0.0, 0.0 } });
        points2.assign ({ { 1.0, 9.0 }, { 9.0, 9.0 }, { 9.0, 1.0 }, { 1.0, 1.0 } });
    }

    SECTION ("4")
    {
        points1.assign ({ { 0.0, 0.0 }, { 0.0, 10.0 }, { 10.0, 10.0 } });
        points2.assign ({ { 15.0, 10.0 }, { 25.0, 10.0 }, { 25.0, 25.0 }, { 15.0, 15.0 } });
    }

    c1.setPoints (points1);
    c2.setPoints (points2);

    REQUIRE (c1.check (c2) != Collision::State::INTERSECTION);
}

TEST_CASE ("Test fail collisions")
{
    Collision c1;
    Collision c2;

    Circuit points1;
    Circuit points2;

    SECTION ("1")
    {
        points1.assign ({ { 0.0, 0.0 }, { 0.0, 10.0 }, { 10.0, 0.0 } });
        points2.assign ({ { 0.0, 11.0 }, { 10.0, -1.0 }, { 10.0, 11.0 } });
    }

    SECTION ("2")
    {
        points1.assign ({ { 0.0, 10.0 }, { 10.0, 10.0 }, { 5.0, 0.0 } });
        points2.assign ({ { 0.0, 5.0 }, { 10.0, 5.0 }, { 6.0, 0.0 } });
    }

    c1.setPoints (points1);
    c2.setPoints (points2);

    REQUIRE (c1.check (c2) == Collision::State::INTERSECTION);
}

TEST_CASE ("Test point detecting")
{
    Collision c;
    Circuit points;

    points.assign ({ { 0.0, 10.0 }, { 10.0, 10.0 }, { 10.0, 0.0 }, { 0.0, 0.0 } });

    c.setPoints (points);

    std::random_device rd;
    std::mt19937 mt (rd ());
    std::uniform_real_distribution<float> dist (0.0, 10.0);

    for (size_t i = 0; i < 100; ++i)
    {
        Point p (dist (mt), dist (mt));

        REQUIRE (c.check (p) == Collision::State::INSIDE);
    }
}

TEST_CASE ("Test outside point detecting")
{
    Collision c;
    Circuit points;

    points.assign ({ { 0.0, 10.0 }, { 10.0, 10.0 }, { 10.0, 0.0 }, { 0.0, 0.0 } });

    c.setPoints (points);

    std::random_device rd;
    std::mt19937 mt (rd ());
    std::uniform_real_distribution<float> dist_big (10.0, 20.0);
    std::uniform_real_distribution<float> dist_sml (-10.0, 0.0);

    for (size_t i = 0; i < 25; ++i)
    {
        Point p1 (dist_big (mt), dist_big (mt));
        REQUIRE (c.check (p1) == Collision::State::OUTSIDE);

        Point p2 (dist_big (mt), dist_sml (mt));
        REQUIRE (c.check (p2) == Collision::State::OUTSIDE);

        Point p3 (dist_sml (mt), dist_big (mt));
        REQUIRE (c.check (p3) == Collision::State::OUTSIDE);

        Point p4 (dist_sml (mt), dist_sml (mt));
        REQUIRE (c.check (p4) == Collision::State::OUTSIDE);
    }
}

TEST_CASE ("Test collision movement")
{
    Collision c1;
    Collision c2;

    Circuit points1;
    Circuit points2;
    
    points1.assign ({ { 4.0, 4.0 }, { 4.0, -4.0 }, { -4.0, -4.0 }, { -4.0, 4.0 } });
    points2.assign ({ { 5.0, 5.0 }, { 5.0, -5.0 }, { -5.0, -5.0 }, { -5.0, 5.0 } });

    c1.setPoints (points1);
    c2.setPoints (points2);

    REQUIRE (c1.check (c2) == Collision::State::OUTSIDE);
    REQUIRE (c2.check (c1) == Collision::State::INSIDE);

    SECTION ("1")
    {
        c1.setPosition ({ 10.0, 0.0 });
        REQUIRE (c1.check (c2) == Collision::State::OUTSIDE);
        REQUIRE (c2.check (c1) == Collision::State::OUTSIDE);
    }

    SECTION ("2")
    {
        c2.setPosition ({ 5.0, -5.0 });
        REQUIRE (c1.check (c2) == Collision::State::INTERSECTION);
        REQUIRE (c2.check (c1) == Collision::State::INTERSECTION);
    }

    SECTION ("3")
    {
        c1.setPosition ({ 0.0, 10.0 });
        REQUIRE (c1.check (c2) == Collision::State::OUTSIDE);
        REQUIRE (c2.check (c1) == Collision::State::OUTSIDE);
    }

    SECTION ("4")
    {
        c1.move ({ 10.0, 0.0 });
        REQUIRE (c1.check (c2) == Collision::State::OUTSIDE);
        REQUIRE (c2.check (c1) == Collision::State::OUTSIDE);
    }

    SECTION ("5")
    {
        c2.move ({ -3.0, 3.0 });
        REQUIRE (c1.check (c2) == Collision::State::INTERSECTION);
        REQUIRE (c2.check (c1) == Collision::State::INTERSECTION);
    }

    SECTION ("6")
    {
        c1.move ({ 6.0, 0.0 });
        REQUIRE (c1.check (c2) == Collision::State::INTERSECTION);
        REQUIRE (c2.check (c1) == Collision::State::INTERSECTION);
    }
}