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


#include "MemoryOutputStream.h"

#include <cstring>


using namespace sfge;


bool MemoryOutputStream::open (const std::string& filename)
{
    m_current = filename;
    m_offset = 0;
    return true;
}

Int64 MemoryOutputStream::write (const void* data, Int64 size)
{
    if (m_current.empty ())
        return -1;

    m_source_data[m_current].insert (m_source_data[m_current].begin () + m_offset, size, '\0');

    std::memcpy (m_source_data[m_current].data () + m_offset, data, static_cast<std::size_t>(size));
    m_offset += size;

    return size;
}

Int64 MemoryOutputStream::seek (Int64 position)
{
    if (m_current.empty ())
        return -1;

    m_offset = position < m_source_data[m_current].size () ? position : m_source_data[m_current].size ();
    return m_offset;
}

Int64 MemoryOutputStream::tell ()
{
    if (m_current.empty ())
        return -1;

    return m_offset;
}

Int64 MemoryOutputStream::getSize ()
{
    if (m_current.empty ())
        return -1;

    return m_source_data[m_current].size ();
}

std::vector<char>& sfge::MemoryOutputStream::getMemory (const std::string& filename)
{
    return m_source_data[filename];
}

std::shared_ptr<MemoryInputStream> MemoryOutputStream::getFullData () const
{
    return std::make_shared<MemoryInputStream> (m_source_data);
}
