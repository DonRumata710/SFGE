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
#include <memory>


namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// File - class for reading data from file
    /////////////////////////////////////////////////////////////////////
    class File
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// default constructor
        ///
        /// @param filename - path to file
        /////////////////////////////////////////////////////////////////////
        explicit File (const char* filename);

        /////////////////////////////////////////////////////////////////////
        /// open - open file
        ///
        /// @return true if file opened successfully, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool read ();

        /////////////////////////////////////////////////////////////////////
        /// reset - remove all data from memory
        /////////////////////////////////////////////////////////////////////
        void reset ();

        /////////////////////////////////////////////////////////////////////
        /// getData - get the data read from the file
        ///
        /// @return data
        /////////////////////////////////////////////////////////////////////
        char* getData ();

        /////////////////////////////////////////////////////////////////////
        /// getSize - get size of file
        ///
        /// @return size of file
        /////////////////////////////////////////////////////////////////////
        size_t getSize ();

        operator bool () const;

    private:
        std::string m_filename;
        std::unique_ptr<char> m_data;
        size_t m_size;
    };


}