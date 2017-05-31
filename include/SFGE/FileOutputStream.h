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

#include <string>


namespace sfge
{


    class FileOutputStream final
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////
        ~FileOutputStream ();

        /////////////////////////////////////////////////////////////////////
        /// open - open the stream from a file path
        ///
        /// @param filename Name of the file to open
        ///
        /// @return True on success, false on error
        /////////////////////////////////////////////////////////////////////
        bool open (const std::string& filename);

        /////////////////////////////////////////////////////////////////////
        /// write - write data to the stream
        ///
        /// @param data - buffer to copy the data
        /// @param size - desired number of bytes to write
        ///
        /// @return - the number of bytes successfully written, or -1 on error
        /////////////////////////////////////////////////////////////////////
        Int64 write (const void* data, Int64 size);

        /////////////////////////////////////////////////////////////////////
        /// seek - change the current reading position
        ///
        /// @param position - the position to seek to, from the beginning
        ///
        /// @return - the position actually sought to, or -1 on error
        /////////////////////////////////////////////////////////////////////
        Int64 seek (Int64 position);

        /////////////////////////////////////////////////////////////////////
        /// tell - get the current reading position in the stream
        ///
        /// @return The current position, or -1 on error
        /////////////////////////////////////////////////////////////////////
        Int64 tell ();

        /////////////////////////////////////////////////////////////////////
        /// getSize - return the size of the stream
        ///
        /// @return The total number of bytes available in the stream, or -1 on error
        /////////////////////////////////////////////////////////////////////
        Int64 getSize ();

    private:
        std::FILE* m_file = nullptr;
    };


}