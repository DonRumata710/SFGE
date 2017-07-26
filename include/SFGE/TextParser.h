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

#include <unordered_map>
#include <string>
#include <vector>


namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// SemanticsDescription - struct for script semantics description
    /////////////////////////////////////////////////////////////////////
    struct SemanticsDescription
    {
        /////////////////////////////////////////////////////////////////////
        /// keytable - enumeration of keywords in the script
        ///
        /// std::string - pointer to keyword
        /// const size_t - keyword code
        /////////////////////////////////////////////////////////////////////
        std::unordered_map<std::string, const size_t> keytable;

        std::vector<char> string_elements;  /// string_elements - list of elements which can be part of unquoted string

        size_t string;                      /// string - code should be returned if parser found a string value

        size_t number;                      /// code should be returned if parser found a number

        size_t end_of_file;                 /// end_of_file - code should be returned if parser came to the end of script
    };


    /////////////////////////////////////////////////////////////////////
    /// TextParser - class for text parsing
    /////////////////////////////////////////////////////////////////////
    class TextParser
    {
    public:
      
        /////////////////////////////////////////////////////////////////////
        /// constructor - create text parser
        ///
        /// @param script - pointer to script text
        /// @param semantics - description of script semantics
        /////////////////////////////////////////////////////////////////////
        TextParser (const char* script, const SemanticsDescription& semantics);

        /////////////////////////////////////////////////////////////////////
        /// getTokentype - get code of current value
        ///
        /// @return - code of parsed value
        /////////////////////////////////////////////////////////////////////
        size_t getTokentype () const;

        /////////////////////////////////////////////////////////////////////
        /// getToken - parse next token
        ///
        /// @return - code of parsed value
        /////////////////////////////////////////////////////////////////////
        size_t getToken ();

        /////////////////////////////////////////////////////////////////////
        /// putBack - return to start of current token
        /////////////////////////////////////////////////////////////////////
        void putBack ();

        /////////////////////////////////////////////////////////////////////
        /// getLine - get current line
        ///
        /// @return - current line
        /////////////////////////////////////////////////////////////////////
        int getLine () const;

        /////////////////////////////////////////////////////////////////////
        /// tknString parse token as a string
        ///
        /// @return - parsed value
        /////////////////////////////////////////////////////////////////////
        char* tknString ();

        /////////////////////////////////////////////////////////////////////
        /// tknInt - parse token as a number
        ///
        /// @return - parsed value
        /////////////////////////////////////////////////////////////////////
        int tknInt ();

        /////////////////////////////////////////////////////////////////////
        /// tknFloat - parse token as a float
        ///
        /// @return - parsed value
        /////////////////////////////////////////////////////////////////////
        float tknFloat ();

        /////////////////////////////////////////////////////////////////////
        /// tknBool - parse token as a boolean
        ///
        /// @return - parsed value
        /////////////////////////////////////////////////////////////////////
        bool tknBool ();

        /////////////////////////////////////////////////////////////////////
        /// tknHex - parse token as a hex value
        ///
        /// @return - parsed value
        /////////////////////////////////////////////////////////////////////
        unsigned tknHex ();

    private:
        bool isString ();

    private:
        const SemanticsDescription& semantics;
        size_t tokentype;
        char tokenvalue[128];
        const char* script;
        int line;

        static bool strtkcmp (const std::string& str, const char* mem);
    };


}