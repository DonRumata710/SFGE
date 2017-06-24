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


#include "FSBrowserDialog.h"
#include "Common.h"
#include "Application.h"

#include <SFGE/GEDevice.h>
#include <SFGE/Button.h>

#include <filesystem>
#include <deque>


using namespace sfge;
using namespace std::experimental::filesystem::v1;

#ifndef WIN32
using namespace std::experimental::filesystem::v1::__cxx11;
#endif


FSBrowserDialog::FSBrowserDialog (Application* parent) :
    m_parent (parent)
{}

void FSBrowserDialog::dirBrowse (const std::string& dir)
{
    if (!exists (dir)) return;

    m_current_dir = dir;

    std::deque<std::string> list;

    for (auto& it : directory_iterator (dir))
    {
        if (is_directory (it.status ()))
            list.push_front (it.path ().filename ().string ());
        else
            list.push_back (it.path ().filename ().string ());
    }

    list.push_front ("..");

    text_list->clear ();
    for (std::string str : list)
        text_list->addString (str);
}

void FSBrowserDialog::handleChoise (const std::string& str)
{
    path choised_path (m_current_dir + "/" + str);
    if (is_directory (choised_path))
        dirBrowse (choised_path.string ());
    else
        m_parent->setChoisedString (choised_path.string ());
}
