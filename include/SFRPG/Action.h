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


#include <cstdint>


namespace sfge
{


    class InteractiveObject;


    class iAction
    {
    public:
        typedef uint32_t ActionID;

        enum DefaultAction : ActionID
        {
            INVALID_ACTION_ID = UINT32_MAX,
            COLLISION_ACTION = UINT32_MAX - 1,
            SECTOR_LEAVING_ACTION = UINT32_MAX - 2
        };

        ActionID getID () const;

        InteractiveObject* getActor () const;

        virtual void doAction (InteractiveObject* target = nullptr) = 0;

    protected:
        iAction (InteractiveObject* actor, ActionID id);

    private:
        InteractiveObject* m_actor = nullptr;
        ActionID m_id = INVALID_ACTION_ID;
    };


    class CollisionAction : public iAction
    {
    public:
        CollisionAction (InteractiveObject* actor);

        virtual void doAction (InteractiveObject* target = nullptr) override;
    };


    class SectorLeavingAction : public iAction
    {
    public:
        SectorLeavingAction (InteractiveObject* actor);

        virtual void doAction (InteractiveObject* target = nullptr) override;
    };


}
