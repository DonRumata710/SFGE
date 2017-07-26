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
#include "Unicode.h"
#include "File.h"

#include <unordered_map>


namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// StringTable - class for manipulating strings
    /////////////////////////////////////////////////////////////////////
    class StringTable
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////
        StringTable () = default;

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param file - file with strings description
        /////////////////////////////////////////////////////////////////////
        StringTable (File& file);

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param string_table - list of strings with their names
        /////////////////////////////////////////////////////////////////////
        StringTable (std::unordered_map<std::string, UString>&& string_table);

        /////////////////////////////////////////////////////////////////////
        /// addString - add string to the table
        ///
        /// @param name - identifier of string
        /// @param str - unicode string
        /////////////////////////////////////////////////////////////////////
        void addString (const std::string& name, const UString& str);

        /////////////////////////////////////////////////////////////////////
        /// getString - get string by name
        ///
        /// @param name - name of string
        ///
        /// @return string
        /////////////////////////////////////////////////////////////////////
        UString getString (const std::string& name);

    private:
        std::unordered_map<std::string, UString> m_string_table;
    };


}
