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


#include "Animation.h"

#include <SFML/Graphics/Texture.hpp>


namespace sfge
{


    Animation::Animation ()
    {}

    Animation::Animation (const AnimationDesc& desc)
    {
        setTexture (*desc.texture, desc.rows, desc.cols, desc.frames, desc.start);
        setOrigin (desc.hotspot.x, desc.hotspot.y);
        setMode (Animation::Mode (desc.mode));
        setFps (desc.fps);
    }

    void Animation::setFps (float fps)
    {
        m_speed = 1.0f / fps;
    }

    void Animation::setTexture (const sf::Texture& text, unsigned n_row, unsigned n_col, unsigned count, unsigned start)
    {
        m_num_columns = n_col;
        m_num_rows = n_row;
        m_count = count;
        m_start = start;
        m_frame = 0;

        sf::Sprite::setTexture (text);
        setTextureRect (sf::IntRect (
            (m_start % m_num_columns) * text.getSize ().x / m_num_columns,
            (m_start / m_num_columns) * text.getSize ().y / m_num_rows,
            text.getSize ().x / n_col,
            text.getSize ().y / n_row
        ));
    }

    void Animation::setMode (Mode mode)
    {
        m_mode = mode;
        if (mode & REV)
            m_delta = -1;
        else
            m_delta = 1;
    }

    void Animation::setFrame (unsigned frame)
    {
        frame = frame % m_count;

        if (m_frame != frame && frame < m_count + m_start)
        {
            m_frame = frame;
            sf::IntRect rect (getTextureRect ());
            setTextureRect (sf::IntRect (
                ((frame + m_start) % m_num_columns) * rect.width,
                (frame + m_start) / m_num_columns * rect.height,
                rect.width,
                rect.height
            ));
        }
    }

    unsigned Animation::currentFrame () const
    {
        return m_frame;
    }

    unsigned Animation::framesCount () const
    {
        return m_count;
    }

    bool Animation::isPlaying () const
    {
        return m_play;
    }

    void Animation::update (float delta)
    {
        if (!m_play) return;

        if (m_last_frame == -1.0f)
            m_last_frame = 0.0f;
        else
            m_last_frame += delta;

        while (m_last_frame >= m_speed)
        {
            m_last_frame -= m_speed;

            if (m_frame + m_delta == m_count + m_start)
            {
                switch (m_mode)
                {
                case FWD:
                case REV | PINGPONG:
                    m_play = false;
                    break;

                case FWD | PINGPONG:
                case FWD | PINGPONG | LOOP:
                case REV | PINGPONG | LOOP:
                    m_delta = -m_delta;
                    break;
                }
            }
            else if (m_frame + m_delta == 0u - 1)
            {
                switch (m_mode)
                {
                case REV:
                case FWD | PINGPONG:
                    m_play = false;
                    break;

                case REV | PINGPONG:
                case REV | PINGPONG | LOOP:
                case FWD | PINGPONG | LOOP:
                    m_delta = -m_delta;
                    break;
                }
            }

            if (m_play)
                setFrame (m_frame + m_delta);
        }
    }

    void Animation::play ()
    {
        m_play = true;
        m_last_frame = -1.0f;
        if (m_mode & REV)
        {
            m_delta = -1;
            setFrame (m_count - 1);
        }
        else
        {
            m_delta = 1;
            setFrame (0);
        }
    }

    void Animation::stop ()
    {
        m_play = false;
    }

    void Animation::resume ()
    {
        m_play = true;
    }


}
