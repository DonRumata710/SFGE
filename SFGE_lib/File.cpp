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


#include "File.h"

#include <fstream>
#include <sstream>
#include <algorithm>


namespace sfge
{


    File::File (const char* filename) : m_filename (filename)
    {}

    bool File::read ()
    {
        std::ifstream data (m_filename);

        if (!data.is_open ()) return false;

        std::ostringstream buf;
        buf << data.rdbuf ();
        std::string str (buf.str ());

        data.close ();

        m_size = str.size () + 1;
        m_data.reset (new char[m_size]);
        str.copy (m_data.get (), str.size (), 0);
        m_data.get ()[str.size ()] = '\0';

        return true;
    }

    void File::reset ()
    {
        m_data.reset ();
        m_size = 0;
    }

    char* File::getData ()
    {
        return m_data.get ();
    }

    size_t File::getSize ()
    {
        return m_size;
    }

    File::operator bool () const
    {
        return m_size;
    }


}
