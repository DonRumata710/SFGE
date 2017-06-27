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


#include "StringTable.h"
#include "TextParser.h"
#include "Err.h"

#include <vector>


using namespace sfge;


enum Token
{
    STRING,
    NUMBER,
    DELIMITER,
    END
};


StringTable::StringTable (File& file)
{
    std::vector<char> data;
    data.assign (file.getSize () + 1, '\0');
    file.read (data.data (), data.size ());
    TextParser tp (data.data (), { { { ":", DELIMITER } }, { '_' }, STRING, NUMBER, END });

    while (true)
    {
        std::string name;
        std::string string;

        if (tp.getToken () == STRING)
            name = tp.tknString ();
        else
        {
            runtime_message ("Illegal syntax in strings description file in line " + std::to_string (tp.getLine ()));
            return;
        }

        if (tp.getToken () != DELIMITER)
        {
            runtime_message ("Illegal syntax in strings description file in line " + std::to_string (tp.getLine ()));
            return;
        }

        if (tp.getToken () == STRING)
            string = tp.tknString ();
        else
        {
            runtime_message ("Illegal syntax in strings description file in line " + std::to_string (tp.getLine ()));
            return;
        }

        m_string_table.insert ({ name, string });
    }
}

StringTable::StringTable (std::unordered_map<std::string, UString>&& string_table) :
    m_string_table (string_table)
{}

void StringTable::addString (const std::string& name, const UString& str)
{
    m_string_table.insert ({ name, str });
}


UString StringTable::getString (const std::string& name)
{
    return m_string_table[name];
}
