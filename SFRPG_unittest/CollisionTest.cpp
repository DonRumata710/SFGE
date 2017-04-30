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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>


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

    REQUIRE (c1.check (c2));
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

    REQUIRE (!c1.check (c2));
}
