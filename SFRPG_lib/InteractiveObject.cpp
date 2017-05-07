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


#include "InteractiveObject.h"
#include "Map.h"

#include <SFGE\ResourceManager.h>


using namespace sfge;


void InteractiveObject::setAnimation (std::unique_ptr<Animation> animation)
{
    m_animation.swap (animation);
}

void InteractiveObject::setAnimation (const std::string& animation)
{
    setAnimation (ResourceManager::getInstance ()->findAnimation (animation));
}

void InteractiveObject::draw (RenderTarget& target) const
{
    target.draw (*m_animation);
}

void InteractiveObject::doAction (const iAction* action)
{
    auto reaction (m_reactions.find (action->getID ()));

    if (reaction != m_reactions.end ())
        reaction->second->doAction (action->getActor ());
}

void InteractiveObject::move (Vector2f vector)
{
    m_collision.move (vector);
    if (!m_map->checkMovement (this))
        m_collision.move (-vector);
}
