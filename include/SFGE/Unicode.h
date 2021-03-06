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


#include "Config.h"

#include <SFML/System/Utf.hpp>
#include <SFML/System/String.hpp>

#include <functional>



namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// UString redefine sf::String which is unicode strings
    /////////////////////////////////////////////////////////////////////
    typedef sf::String UString;

    using sf::Utf32;
    using sf::Utf16;
    using sf::Utf8;


}



namespace std
{


    /////////////////////////////////////////////////////////////////////
    /// hash of UString allows to use UString in unordered arrays
    /////////////////////////////////////////////////////////////////////
    template <> struct hash<sfge::UString>
    {
        size_t operator()(const sfge::UString& k) const
        {
            return hash<string> () ((string) k);
        }
    };


}