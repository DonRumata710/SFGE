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

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <string>


namespace sf
{
    class Text;
    class Color;
}


namespace sfge
{


    using sf::Texture;
    using sf::Vector2u;
    using sf::IntRect;
    using sf::Color;


    /////////////////////////////////////////////////////////////////////
    /// Panel - class for drawing textures in custom coordinates
    /////////////////////////////////////////////////////////////////////
    class Panel : public sf::Drawable
    {
    public:
        Panel ();

        /////////////////////////////////////////////////////////////////////
        /// constructor which automatically set panel size according to 
        /// texture size
        /// 
        /// @param tex - texture of panel
        /////////////////////////////////////////////////////////////////////
        Panel (const std::shared_ptr<const Texture> tex);

        /////////////////////////////////////////////////////////////////////
        /// setTexture - set texture to panel
        /// 
        /// @param tex - new texture
        /////////////////////////////////////////////////////////////////////
        void setTexture (const std::shared_ptr<const Texture> tex);

        /////////////////////////////////////////////////////////////////////
        /// setTexture - set texture to panel
        /// 
        /// @param tex - name of new texture
        /////////////////////////////////////////////////////////////////////
        void setTexture (const std::string& tex);

        /////////////////////////////////////////////////////////////////////
        /// setColor - fill panel by one color
        /// 
        /// @param color - new color
        /////////////////////////////////////////////////////////////////////
        void setColor (const Color color);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set coordinates of top-left corner
        /// 
        /// @param x - X coordinate of new position
        /// @param y - Y coordinate of new position
        /////////////////////////////////////////////////////////////////////
        void setPosition (const unsigned x, const unsigned y);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set coordinates of top-left corner
        /// 
        /// @param pos - point to move
        /////////////////////////////////////////////////////////////////////
        void setPosition (const Vector2u pos);

        /////////////////////////////////////////////////////////////////////
        /// setPosition - set position of top-left corner and size of panel
        /// 
        /// @param pos - new position and size
        /////////////////////////////////////////////////////////////////////
        void setPosition (const IntRect pos);

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of panel
        /// 
        /// @param size - new size of panel
        /////////////////////////////////////////////////////////////////////
        void setSize (Vector2u size);

        /////////////////////////////////////////////////////////////////////
        /// setSize - set size of panel
        /// 
        /// @param x - width of panel
        /// @param y - height of panel
        /////////////////////////////////////////////////////////////////////
        void setSize (unsigned x, unsigned y);

        /////////////////////////////////////////////////////////////////////
        /// getRect - get position of top-left corner and size of panel
        /// 
        /// @return position and size of panel
        /////////////////////////////////////////////////////////////////////
        IntRect getRect () const;

        /////////////////////////////////////////////////////////////////////
        /// getPosition - position of panel
        /// 
        /// @return position of top-left corner
        /////////////////////////////////////////////////////////////////////
        Vector2u getPosition () const;

        /////////////////////////////////////////////////////////////////////
        /// getSize - get size of panel
        /// 
        /// @return size of panel
        /////////////////////////////////////////////////////////////////////
        Vector2u getSize () const;

        /////////////////////////////////////////////////////////////////////
        /// contains - check if point is inside of panel
        /// 
        /// @param x - X coordinate of point
        /// @param y - Y coordinate of point
        /// 
        /// @return true if the point is inside, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool contains (const float x, const float y);

    private:
        virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Vertex m_arr[4];
        std::shared_ptr<const sf::Texture> m_texture;
    };



}