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
#include "Err.h"

#include <cstring>
#include <cstdlib>


namespace sfge
{


    TextParser::TextParser (const char* scr, const SemanticsDescription& semantics) :
        semantics (semantics)
    {
        script = scr;
        tokenvalue[0] = 0;
        tokentype = SIZE_MAX;
        line = 1;
    }

    size_t TextParser::getTokentype () const
    {
        return tokentype;
    }

    size_t TextParser::getToken ()
    {
        int i;

        // Skip whitespaces and comments

        while (true)
        {
            while (*script == ' ' || *script == '\t' || *script == '\n' || *script == '\r')
            {
                if (*script == '\n')
                {
                    line++;
                }
                script++;
            }

            if (*script == ';')
            {
                while (*script && *script != '\n' && *script != '\r')
                    script++;
            }
            else
                break;
        }

        // End of script

        if (!*script)
        {
            tokentype = semantics.end_of_file;
            tokenvalue[0] = '\0';
            return tokentype;
        }

        // Number

        if ((*script >= '0' && *script <= '9') || *script == '.' || *script == '-')
        {
            tokentype = semantics.number;
            for (i = 0; (*script >= '0' && *script <= '9') || *script == '.' || *script == '-'; i++)
                tokenvalue[i] = *script++;

            // Hexadecimal number starting with decimal digit

            if ((*script >= 'A' && *script <= 'F') || (*script >= 'a' && *script <= 'f'))
            {
                tokentype = semantics.string;
                for (; (*script >= 'A' && *script <= 'F') || (*script >= 'a' && *script <= 'f'); i++)
                    tokenvalue[i] = *script++;
            }

            tokenvalue[i] = 0;
            return tokentype;
        }

        // Quoted string

        if (*script == '"')
        {
            tokentype = semantics.string;
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

        for (auto keyword : semantics.keytable)
        {
            if (!strtkcmp (keyword.first, script))
            {
                tokentype = keyword.second;
                std::strcpy (tokenvalue, keyword.first.c_str ());
                script += keyword.first.size ();
                return tokentype;
            }
        }

        // Unquoted string or hexadecimal number

        tokentype = semantics.string;
        for (i = 0;
            *script && (isalnum (*script) || *script == '_');
            i++
        )
        {
            tokenvalue[i] = *script++;
        }
        tokenvalue[i] = 0;
        return tokentype;
    }

    void TextParser::putBack ()
    {
        script -= std::strlen (tokenvalue);
    }

    int TextParser::getLine () const
    {
        return line;
    }

    char* TextParser::tknString ()
    {
        return tokenvalue;
    }

    int TextParser::tknInt ()
    {
        return std::atoi (tokenvalue);
    }

    float TextParser::tknFloat ()
    {
        return (float) std::atof (tokenvalue);
    }

    bool TextParser::tknBool ()
    {
        return (tokenvalue[0] == 't' || tokenvalue[0] == 'T') ? true : false;
    }

    unsigned TextParser::tknHex ()
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

    bool TextParser::strtkcmp (const std::string& str, const char * mem)
    {
        for (int i = 0; i < str.size (); i++)
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
