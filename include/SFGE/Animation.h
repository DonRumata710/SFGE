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


#include "AnimationDesc.h"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>


namespace sfge
{


    using sf::Texture;
    using sf::Sprite;


    /////////////////////////////////////////////////////////////////////
    /// Animation - some visual object with several views
    /// 
    /// All views of animation should be places on one texture one by
    /// one. Texture should be divided on rows and columns which contain
    /// frames of animation(s).
    /////////////////////////////////////////////////////////////////////
    class Animation : public Sprite
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Mode is enumeration with modes of animation
        /// 
        /// Modes can be overlapped
        /////////////////////////////////////////////////////////////////////
        enum Mode
        {
            FWD = 0,        /// change views from up to down and from left to right on texture
            REV = 1,        /// change views from down to up and from right to left on texture
            PINGPONG = 2,   /// change direction when last view is shown
            LOOP = 4        /// start from first view when last view is shown
        };

        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        Animation ();
	
        /////////////////////////////////////////////////////////////////////
        /// Copy constructor
        /////////////////////////////////////////////////////////////////////
        explicit Animation (const AnimationDesc&);

        /////////////////////////////////////////////////////////////////////
        /// setFps - set frames per second
        /// 
        /// @param fps - number of frames per second
        /////////////////////////////////////////////////////////////////////
        void setFps (float fps);

        /////////////////////////////////////////////////////////////////////
        /// setTexture - set texture which containe views of animation
        /// 
        /// @param t - pointer to texture
        /// @param n_row - number of rows in texture
        /// @param n_col - number of columns in texture
        /// @param count - number of views in animation
        /// @param start - number of view on texture which is first for animation
        /////////////////////////////////////////////////////////////////////
        void setTexture (const Texture& t, unsigned n_row, unsigned n_col, unsigned count, unsigned start = 0);

        /////////////////////////////////////////////////////////////////////
        /// setTexture - set texture which containe views of animation
        /// 
        /// @param t - name of texture
        /// @param n_row - number of rows in texture
        /// @param n_col - number of columns in texture
        /// @param count - number of views in animation
        /// @param start - number of view on texture which is first for animation
        /////////////////////////////////////////////////////////////////////
        void setTexture (const std::string& t, unsigned n_row, unsigned n_col, unsigned count, unsigned start = 0);

        /////////////////////////////////////////////////////////////////////
        /// setMode - set mode of displaying of animation
        /// 
        /// @param mode - mode of displaying
        /////////////////////////////////////////////////////////////////////
        void setMode (Mode mode);

        /////////////////////////////////////////////////////////////////////
        /// setFrame - change frame which animation should show
        /// 
        /// Note: numeration of frames is actual only for frames of animation, not
        /// for all frames of texture!
        /// 
        /// @param frame - number of frame
        /////////////////////////////////////////////////////////////////////
        void setFrame (unsigned frame);

        /////////////////////////////////////////////////////////////////////
        /// update - update animation to change frames in time
        ///
        /// This function should be called in main loop to change frames of 
        /// animation when it is active.
        /// 
        /// @param delta - time since last loop
        /////////////////////////////////////////////////////////////////////
        void update (float delta);

        /////////////////////////////////////////////////////////////////////
        /// play - start animation playing from the begin
        /////////////////////////////////////////////////////////////////////
        void play ();

        /////////////////////////////////////////////////////////////////////
        /// stop - stop animation playing
        /////////////////////////////////////////////////////////////////////
        void stop ();

        /////////////////////////////////////////////////////////////////////
        /// resume - play animation from last frame
        /////////////////////////////////////////////////////////////////////
        void resume ();

        /////////////////////////////////////////////////////////////////////
        /// currentFrame - get frame which animation show now
        /// 
        /// @return number of frame
        /////////////////////////////////////////////////////////////////////
        unsigned currentFrame () const;

        /////////////////////////////////////////////////////////////////////
        /// framesCount - get count of frames in animation
        /// 
        /// @return count of frames
        /////////////////////////////////////////////////////////////////////
        unsigned framesCount () const;

        /////////////////////////////////////////////////////////////////////
        /// isPLaying - check whether or not animation is playing
        ///
        /// @return True if animation is playing, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool isPlaying () const;

    private:
        unsigned m_num_columns = 0;
        unsigned m_num_rows = 0;
        unsigned m_count = 0;
        unsigned m_start = 0;

        unsigned m_frame = 0;

        int m_delta = 1;

        float m_speed = 1.0f;

        float m_last_frame = -1.0f;

        Mode m_mode = FWD;

        bool m_play = false;
    };


}