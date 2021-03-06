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


#include "Collision.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <string>


namespace sfge
{


    using sf::Vector2f;
    using sf::RenderTarget;
    using sf::RenderStates;
    using sf::Drawable;
    
    class MapSector;


    class MapObject : public Drawable
    {
    public:
        MapObject () = default;

        ~MapObject () = default;

        void attachToSector (MapSector*);

        MapSector* getSector () const;

        void setPosition (const Vector2f& pos);

        Vector2f getPosition () const;

        void setCollision (const Collision& collision);

        Collision::State detectCollision (const MapObject* object) const;

        Collision::State detectCollision (const Vector2f p1, const Vector2f p2) const;

    protected:
        Collision m_collision;
        MapSector* m_map = nullptr;
    };


}
