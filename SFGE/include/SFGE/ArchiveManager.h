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


#include <SFML/System/InputStream.hpp>

#include <string>


namespace sfge
{

    namespace minizip
    {


        #include <unzip.h>


    }


    using sf::InputStream;
    using sf::Int64;

    class File;


    class ArchiveManager : public InputStream
    {
    public:
        ArchiveManager (const std::string& archive);

        ~ArchiveManager ();

        bool open (const std::string& path, const std::string& password);

        /////////////////////////////////////////////////////////////////////
        /// Read data from the stream
        ///
        /// After reading, the stream's reading position must be
        /// advanced by the amount of bytes read.
        ///
        /// @param data Buffer where to copy the read data
        /// @param size Desired number of bytes to read
        ///
        /// \return The number of bytes actually read, or -1 on error
        /////////////////////////////////////////////////////////////////////
        virtual Int64 read (void* data, Int64 size) override;

        /////////////////////////////////////////////////////////////////////
        /// Change the current reading position
        ///
        /// @param position The position to seek to, from the beginning
        ///
        /// @return The position actually sought to, or -1 on error
        /////////////////////////////////////////////////////////////////////
        virtual Int64 seek (Int64 position) override;

        /////////////////////////////////////////////////////////////////////
        /// Get the current reading position in the stream
        ///
        /// @return The current position, or -1 on error.
        /////////////////////////////////////////////////////////////////////
        virtual Int64 tell () override;

        /////////////////////////////////////////////////////////////////////
        /// Return the size of the stream
        ///
        /// @return The total number of bytes available in the stream, or -1 on error
        /////////////////////////////////////////////////////////////////////
        virtual Int64 getSize () override;

    private:
        struct Implement;
        Implement* m_impl;
    };


}