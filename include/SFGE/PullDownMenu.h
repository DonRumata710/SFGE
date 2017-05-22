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


#include "Widget.h"
#include "Field.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>
#include <memory>
#include <cstdint>


namespace sfge
{


    using sf::Color;
    using sf::Texture;

    class MenuItem;


    class PullDownMenu : public iWidget, public Field
    {
    public:
        void addItem (std::shared_ptr<MenuItem>);

        void setItemView (Color color, View view);

        void setItemView (std::shared_ptr<const Texture> texture, View view);

        void setAutoHeight (bool auto_size = true);

        void show (const Vector2i position);

        void collapse ();

        bool isShown () const;

    private:
        virtual void setRect (const PositionDesc& desc) override;

        virtual void draw (RenderTarget& target) const override;

        virtual bool check_key (const sf::Event::KeyEvent&, const bool) override;
        virtual void check_mouse_button (const sf::Event::MouseButtonEvent&, const bool) override;
        virtual bool check_mouse (const int x, const int y) override;

    private:
        std::vector<std::shared_ptr<MenuItem>> m_items;

        size_t m_hover_item = SIZE_MAX;
        size_t m_active_item = SIZE_MAX;

        bool m_auto_size = true;
    };


}
