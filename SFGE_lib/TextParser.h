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


namespace sfge
{


    class TextParser
    {
    public:
        enum Token
        {
            TTNONE, TTEND, TTNUMBER, TTSTRING,

            TTBOOL, TTEQUALS, TTBASED, TTSEPARATOR, TTOPENBLOCK, TTCLOSEBLOCK,

            TTRES__FIRST,
            TTRES_INCLUDE, TTRES_FONT, TTRES_IMAGE, TTRES_TEXTURE, TTRES_SPRITE,
            TTRES_ANIMATION, TTRES_FILE, TTRES_SOUND, TTRES_MUSIC,
            TTRES_PARTICLE, TTRES_DISTORT, TTRES_STRTABLE,
            TTRES__LAST,

            TTPAR__FIRST,
            TTPAR_FILENAME, TTPAR_RESGROUP, TTPAR_MIPMAP, TTPAR_AMPLIFY, TTPAR_SIZE, TTPAR_ZBUFFER,
            TTPAR_TEXTURE, TTPAR_RECT, TTPAR_HOTSPOT, TTPAR_BLENDMODE, TTPAR_COLOR,
            TTPAR_ZORDER, TTPAR_FLIP, TTPAR_SCALE, TTPAR_PROPORTION, TTPAR_ROTATION, TTPAR_FRAMES,
            TTPAR_FPS, TTPAR_MODE, TTPAR_TRACKING, TTPAR_SPACING, TTPAR_SPRITE, TTPAR_MESH, TTPAR_COLUMNS, TTPAR_ROWS, TTPAR_START,
            TTPAR__LAST,

            TTCON__FIRST,
            TTCON_COLORMUL, TTCON_COLORADD, TTCON_ALPHABLND, TTCON_ALPHAADD, TTCON_ZWRITE,
            TTCON_NOZWRITE, TTCON_FORWARD, TTCON_REVERSE, TTCON_PINGPONG, TTCON_NOPINGPONG,
            TTCON_LOOP, TTCON_NOLOOP, TTCON_CIRCLE, TTCON_RECT, TTCON_ALPHA,
            TTCON__LAST
        };

        TextParser (const char* script);

        bool scriptSkipToNextParameter (bool bIgnore);

        TextParser::Token get_tokentype () const;

        unsigned	get_token ();
        void	    put_back ();

        int		    get_line ();
        char*	    tkn_string ();
        int		    tkn_int ();
        float	    tkn_float ();
        bool	    tkn_bool ();
        unsigned	tkn_hex ();

    private:
        TextParser::Token tokentype;
        char tokenvalue[128];
        const char* script;
        int line;

        bool strtkcmp (const char *str, const char *mem);
    };


}