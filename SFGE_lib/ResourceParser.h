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

#include <string>


namespace sfge
{


    class ResourceLoader;
    class TextParser;


    class ResourceParser
    {
        enum Resource
        {
            SCRIPT,
            FONT,
            IMAGE,
            TEXTURE,
            SPRITE,
            ANIMATION,
            FILE,
            SOUND,
            MUSIC,
            PARTICLE,
            DISTORT,
            STRTABLE
        };

    public:
        bool parse_script (ResourceLoader* rm, const char* path);

    private:
        char* load_script (const char* path, size_t* size);

        bool scriptSkipToNextParameter (TextParser *tp, bool ignore);

        void parse_font          (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_image         (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_texture       (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_sprite        (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_animation     (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_file_resource (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_effect        (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_music         (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_target        (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_particle      (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_distort       (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
        void parse_string_table  (ResourceLoader *rm, TextParser *tp, const char *name, const char* basename);
    };


}