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


#include "FileOutputStream.h"


using namespace sfge;


FileOutputStream::~FileOutputStream ()
{
    if (m_file)
        fclose (m_file);
}

bool FileOutputStream::open (const std::string& filename)
{
    if (m_file)
        fclose (m_file);

    m_file = fopen (filename.c_str (), "wb");

    return m_file;
}

Int64 FileOutputStream::write (const void* data, Int64 size)
{
    if (m_file)
        return std::fwrite (data, 1, static_cast<std::size_t>(size), m_file);
    else
        return -1;
}

Int64 FileOutputStream::seek (Int64 position)
{
    if (m_file)
        return std::fseek (m_file, position, SEEK_SET);
    else
        return -1;
}

Int64 FileOutputStream::tell ()
{
    if (m_file)
        return std::ftell (m_file);
    else
        return -1;
}

Int64 FileOutputStream::getSize ()
{
    if (m_file)
    {
        Int64 position = tell ();
        std::fseek (m_file, 0, SEEK_END);
        Int64 size = tell ();
        seek (position);
        return size;
    }
    else
    {
        return -1;
    }
}
