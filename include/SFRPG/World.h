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


#include <SFGE/Panel.h>
#include <SFGE/RenderRect.h>
#include <SFGE/Widget.h>

#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>


namespace sfge
{


    using sf::Vector2u;
    using sf::Vector2i;
    using sf::Vector2f;

    class MapManager;


    class World : public iWidget
    {
    public:
        World ();

        void loadMap (const std::string& path);

        void saveMap (const std::string& path);

        void closeMap ();

    protected:
        void setMap (std::shared_ptr<MapManager> map);

        std::shared_ptr<MapManager> getMap ();

        void redraw ();

        void move (Vector2f offset);

        Vector2f mapPixelToCoords (Vector2i point);

    private:
        virtual void draw (sf::RenderTarget&) const override final;

        virtual void update (const float delta) override final;

        virtual void setRect (const PositionDesc& desc) override final;

        virtual bool check_mouse (const int x, const int y) override;

        std::string getMapName (const std::string& path) const;

    private:
        std::shared_ptr<MapManager> m_map;

        RenderRect m_render_rect;
        Panel m_panel;
        sf::View m_view;
        sf::RenderTexture m_screen;
    };


}
