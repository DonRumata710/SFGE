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


#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>


namespace sf
{
    class Color;
}


namespace sfge
{


    using sf::IntRect;
    using sf::Vector2u;
    using sf::Vertex;
    using sf::RenderTarget;
    using sf::RenderStates;


    class RenderRect : public sf::Drawable
    {
    public:
        RenderRect ();
        RenderRect (Vector2u);

        void setPosition (const unsigned x, const unsigned y);
        void setPosition (const Vector2u pos);
        void setPosition (const IntRect pos);

        void setSize (Vector2u size);
        void setSize (unsigned x, unsigned y);

        IntRect getRect () const;
        Vector2u getPosition () const;
        Vector2u getSize () const;

        bool contains (const float x, const float y);

        virtual void draw (RenderTarget& target, RenderStates states) const override;

        Vertex m_arr[4];
    };


}