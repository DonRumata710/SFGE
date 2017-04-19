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


#include "TextParser.h"

#include <cstring>
#include <cstdlib>



namespace sfge
{


    struct Keyword
    {
        char*	            word;
        TextParser::Token	code;
    };

    Keyword keytable[] = {
        { "=",			TextParser::TTEQUALS },
        { ":",			TextParser::TTBASED },
        { ",",			TextParser::TTSEPARATOR },
        { "{",			TextParser::TTOPENBLOCK },
        { "}",			TextParser::TTCLOSEBLOCK },
        { "true",		TextParser::TTBOOL },
        { "false",		TextParser::TTBOOL },

        { "Include",	TextParser::TTRES_INCLUDE },
        { "Resource",	TextParser::TTRES_FILE },
        { "Texture",	TextParser::TTRES_TEXTURE },
        { "Sound",		TextParser::TTRES_SOUND },
        { "Music",		TextParser::TTRES_MUSIC },
        { "Image",      TextParser::TTRES_IMAGE },
        { "Sprite",		TextParser::TTRES_SPRITE },
        { "Animation",	TextParser::TTRES_ANIMATION },
        { "Font",		TextParser::TTRES_FONT },
        { "Particle",	TextParser::TTRES_PARTICLE },
        { "Distortion",	TextParser::TTRES_DISTORT },
        { "StringTable",TextParser::TTRES_STRTABLE },

        { "filename",	TextParser::TTPAR_FILENAME },
        { "resgroup",	TextParser::TTPAR_RESGROUP },
        { "mipmap",		TextParser::TTPAR_MIPMAP },
        { "amplify",	TextParser::TTPAR_AMPLIFY },
        { "size",		TextParser::TTPAR_SIZE },
        { "zbuffer",	TextParser::TTPAR_ZBUFFER },
        { "texture",	TextParser::TTPAR_TEXTURE },
        { "rect",		TextParser::TTPAR_RECT },
        { "hotspot",	TextParser::TTPAR_HOTSPOT },
        { "blendmode",	TextParser::TTPAR_BLENDMODE },
        { "color",		TextParser::TTPAR_COLOR },
        { "zorder",		TextParser::TTPAR_ZORDER },
        { "flip",		TextParser::TTPAR_FLIP },
        { "scale",		TextParser::TTPAR_SCALE },
        { "proportion",	TextParser::TTPAR_PROPORTION },
        { "rotation",	TextParser::TTPAR_ROTATION },
        { "frames",		TextParser::TTPAR_FRAMES },
        { "fps",		TextParser::TTPAR_FPS },
        { "mode",		TextParser::TTPAR_MODE },
        { "tracking",	TextParser::TTPAR_TRACKING },
        { "spacing",	TextParser::TTPAR_SPACING },
        { "sprite",		TextParser::TTPAR_SPRITE },
        { "mesh",		TextParser::TTPAR_MESH },
        { "columns",    TextParser::TTPAR_COLUMNS },
        { "rows",       TextParser::TTPAR_ROWS },
        { "start",      TextParser::TTPAR_START },

        { "COLORMUL",	TextParser::TTCON_COLORMUL },
        { "COLORADD",	TextParser::TTCON_COLORADD },
        { "ALPHABLEND",	TextParser::TTCON_ALPHABLND },
        { "ALPHAADD",	TextParser::TTCON_ALPHAADD },
        { "ZWRITE",		TextParser::TTCON_ZWRITE },
        { "NOZWRITE",	TextParser::TTCON_NOZWRITE },
        { "FORWARD",	TextParser::TTCON_FORWARD },
        { "REVERSE",	TextParser::TTCON_REVERSE },
        { "PINGPONG",	TextParser::TTCON_PINGPONG },
        { "NOPINGPONG",	TextParser::TTCON_NOPINGPONG },
        { "LOOP",		TextParser::TTCON_LOOP },
        { "NOLOOP",		TextParser::TTCON_NOLOOP },
        { "CIRCLE",		TextParser::TTCON_CIRCLE },
        { "RECT",		TextParser::TTCON_RECT },
        { "ALPHA",		TextParser::TTCON_ALPHA },

        { NULL,			TextParser::TTNONE }
    };



    bool TextParser::scriptSkipToNextParameter (bool bIgnore)
    {
        bool bToBeIgnored = bIgnore;
        if (bIgnore)
        {
            put_back ();
        }

        for (;;)
        {
            get_token ();
            if (tokentype == TextParser::TTCLOSEBLOCK)
            {
                if (bIgnore)
                {
                    put_back ();
                    return true;
                }
                return false;
            }
            if ((tokentype > TextParser::TTRES__FIRST &&
                get_tokentype () < TextParser::TTRES__LAST) || tokentype == TextParser::TTEND)
            {
                put_back ();
                if (bIgnore)
                    return true;

                //ScriptPostError ("'}' missed, ", " encountered.");
                return false;
            }
            if ((tokentype <= TextParser::TTPAR__FIRST && tokentype >= TextParser::TTPAR__LAST) || bToBeIgnored)
            {
                bToBeIgnored = false;
                //ScriptPostError ("Unsupported resource parameter ", ".");
                do
                {
                    get_token ();
                }
                while ((tokentype <= TextParser::TTPAR__FIRST || tokentype >= TextParser::TTPAR__LAST) &&
                    (tokentype <= TextParser::TTRES__FIRST || tokentype >= TextParser::TTRES__LAST) &&
                    tokentype != TextParser::TTCLOSEBLOCK && tokentype != TextParser::TTEND);
                put_back ();
            }
            else
            {
                if (bIgnore)
                {
                    put_back ();
                }
                return true;
            }
        }
    }



    TextParser::TextParser (const char* scr)
    {
        script = scr;
        tokenvalue[0] = 0;
        tokentype = TTNONE;
        line = 1;
    }

    unsigned TextParser::get_token ()
    {
        int i;

        // Skip whitespaces and comments

        for (;;)
        {
            while (*script == ' ' || *script == '\t' || *script == '\n' || *script == '\r')
            {
                if (*script == '\n')
                {
                    line++;
                }
                script++;
            }

            if (*script == ';') while (*script && *script != '\n' && *script != '\r')
                script++;
            else
                break;
        }

        // End of script

        if (!*script)
        {
            tokentype = TTEND;
            tokenvalue[0] = 0;
            return tokentype;
        }

        // Number

        if ((*script >= '0' && *script <= '9') || *script == '.' || *script == '-')
        {
            tokentype = TTNUMBER;
            for (i = 0; (*script >= '0' && *script <= '9') || *script == '.' || *script == '-'; i++)
                tokenvalue[i] = *script++;

            // Hexadecimal number starting with decimal digit

            if ((*script >= 'A' && *script <= 'F') || (*script >= 'a' && *script <= 'f'))
            {
                tokentype = TTSTRING;
                for (; (*script >= 'A' && *script <= 'F') || (*script >= 'a' && *script <= 'f'); i++)
                    tokenvalue[i] = *script++;
            }

            tokenvalue[i] = 0;
            return tokentype;
        }

        // Quoted string

        if (*script == '"')
        {
            tokentype = TTSTRING;
            script++;
            for (i = 0; *script && *script != '"' && *script != '\n' && *script != '\r'; i++)
            {
                tokenvalue[i] = *script++;
            }
            tokenvalue[i] = 0;
            if (*script)
            {
                script++;
            }
            return tokentype;
        }

        // Keyword

        for (i = 0; keytable[i].word; i++)
            if (!strtkcmp (keytable[i].word, script))
            {
                tokentype = keytable[i].code;
                std::strcpy (tokenvalue, keytable[i].word);
                script += strlen (keytable[i].word);
                return tokentype;
            }

        // Unquoted string or hexadecimal number

        tokentype = TTSTRING;
        for (i = 0;
            *script && *script != ' ' && *script != '\t' && *script != '\n' && *script != '\r'
            && *script != ',' && *script != '=' && *script != '{' && *script != '}' && *script != ':';
            i++
        )
        {
            tokenvalue[i] = *script++;
        }
        tokenvalue[i] = 0;
        return tokentype;
    }

    TextParser::Token TextParser::get_tokentype () const
    {
        return tokentype;
    }

    void TextParser::put_back ()
    {
        script -= std::strlen (tokenvalue);
    }

    int TextParser::get_line ()
    {
        return line;
    }

    char* TextParser::tkn_string ()
    {
        return tokenvalue;
    }

    int TextParser::tkn_int ()
    {
        return std::atoi (tokenvalue);
    }

    float TextParser::tkn_float ()
    {
        return (float) std::atof (tokenvalue);
    }

    bool TextParser::tkn_bool ()
    {
        return (tokenvalue[0] == 't' || tokenvalue[0] == 'T') ? true : false;
    }

    unsigned TextParser::tkn_hex ()
    {
        int i;
        unsigned dw = 0;
        char chr;
        for (i = 0; tokenvalue[i]; i++)
        {
            chr = tokenvalue[i];
            if (chr >= 'a')
            {
                chr -= 'a' - ':';
            }
            if (chr >= 'A')
            {
                chr -= 'A' - ':';
            }
            chr -= '0';
            if (chr > 0xF)
            {
                chr = 0xF;
            }
            dw = (dw << 4) | chr;
        }
        return dw;
    }

    bool TextParser::strtkcmp (const char * str, const char * mem)
    {
        int i;
        size_t len (std::strlen (str));
        for (i = 0; i < len; i++)
        {
            if (!mem[i])
            {
                return true;
            }
            if (mem[i] != str[i])
            {
                return true;
            }
        }
        return false;
    }


}
