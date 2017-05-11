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


#include "MapObject.h"
#include "Action.h"

#include <SFGE\Animation.h>

#include <functional>
#include <unordered_map>


namespace sfge
{


    class InteractiveObject : public MapObject
    {
    public:
        void setAnimation (std::unique_ptr<Animation> animation);

        void setAnimation (const std::string& animation);

        virtual void draw (RenderTarget& target, RenderStates states) const override;

        template<class Action, typename ...Args> void runAction (InteractiveObject* target, Args ...args)
        {
            Action action (this, args...);
            action.doAction (target);
        }

        void doAction (const iAction* action);

        template<class Action, typename ...Args> void attachReaction (iAction::ActionID id_action, Args ...args)
        {
            std::shared_ptr<iAction> action (new Action (this, args));
            m_reactions[id_action] = action;
        }

        void move (Vector2f vector);

    private:
        std::unique_ptr<Animation> m_animation;
        std::unordered_map<iAction::ActionID, std::shared_ptr<iAction>> m_reactions;
    };


}
