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


#include "EditField.h"
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"

#include <SFGE/GEDevice.h>
#include <SFGE/ResourceManager.h>


class Application
{
public:
    Application ();
    ~Application ();

    int run ();

    void setChoisedString (const std::string& str);

    void openFileDialog ();
    void saveFileDialog ();

private:
    sfge::GEDevice m_device;
    sfge::ResourceManager m_resource_manager;
    
    std::shared_ptr<EditField> m_editor;

    std::unique_ptr<OpenFileDialog> m_file_select_window;
    std::string m_string;

    enum Action
    {
        NONE,
        OPEN,
        SAVE,
        ADD_RESOURCES
    };

    Action m_last_action = NONE;
};
