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


#include "MapObject.h"
#include "MapSector.h"

#include <SFGE/ResourceManager.h>


using namespace sfge;


void sfge::MapObject::attachToSector (MapSector* map_sector)
{
    m_map = map_sector;
}

MapSector* sfge::MapObject::getSector () const
{
    return m_map;
}

void MapObject::setPosition (const Vector2f& pos)
{
    m_collision.setPosition (pos);
}

Vector2f sfge::MapObject::getPosition () const
{
    return m_collision.getPosition ();
}

void MapObject::setCollision (const Collision& collision)
{
    m_collision = collision;
}

Collision::State MapObject::detectCollision (const MapObject* object) const
{
    return m_collision.check (object->m_collision);
}

Collision::State sfge::MapObject::detectCollision (const Vector2f p1, const Vector2f p2) const
{
    return m_collision.check (p1, p2);
}
