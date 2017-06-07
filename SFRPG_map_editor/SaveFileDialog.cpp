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


#include "Common.h"
#include "SaveFileDialog.h"
#include "Application.h"

#include <SFGE/GEDevice.h>
#include <SFGE/Button.h>

#include <filesystem>
#include <deque>


using namespace sfge;
using namespace std::experimental::filesystem::v1;


SaveFileDialog::SaveFileDialog (Application * parent)
{
    auto device (GEDevice::getInstance ());
    manager = std::make_unique<GUIManager> (device);
    manager->setBackground (BACKGROUND_COLOR);

    text_list = std::make_shared<TextList> ();
    text_list->setPosition (iWidget::Position::TOP | iWidget::Position::HCENTER, 0, 10);
    text_list->setSize (380, 270);
    text_list->setView (MAIN_COLOR);
    text_list->attachReaction ([this]() { handleChoise (text_list->getCurrent ()); }, TextList::EventType::ITEM_SELECTED);
    text_list->attachReaction ([this]() { line_edit->setString (text_list->getCurrent ()); }, TextList::EventType::FOCUS_CHANGED);

    line_edit = std::make_shared<LineEdit> ();
    line_edit->setPosition (iWidget::Position::TOP | iWidget::Position::HCENTER, 0, 260);
    line_edit->setSize (380, 20);
    line_edit->setView (sf::Color (32, 32, 32));
    line_edit->attachReaction ([this]() { handleChoise (line_edit->getString ()); }, LineEdit::EventType::INPUT_COMPLETED);

    dirBrowse (".");

    std::shared_ptr<Button> button_cancel (std::make_shared<Button> ());
    button_cancel->setPosition (iWidget::Position::BOTTOM | iWidget::Position::LEFT, 10, 10);
    button_cancel->setSize (120, 50);
    button_cancel->setView (MAIN_COLOR);
    button_cancel->setView (HOVER_COLOR, Button::View::HOVER);
    button_cancel->setView (SECOND_COLOR, Button::View::PRESSED);
    button_cancel->setText ("Cancel");
    button_cancel->attachReaction ([this]() { handleChoise (""); }, Button::EventType::PRESSED);

    std::shared_ptr<Button> button_ok (std::make_shared<Button> ());
    button_ok->setPosition (iWidget::Position::BOTTOM | iWidget::Position::RIGHT, 10, 10);
    button_ok->setSize (120, 50);
    button_ok->setView (MAIN_COLOR, Button::View::RELEASED);
    button_ok->setView (HOVER_COLOR, Button::View::HOVER);
    button_ok->setView (SECOND_COLOR, Button::View::PRESSED);
    button_ok->setText ("OK");
    button_ok->attachReaction ([this]() { handleChoise (text_list->getCurrent ()); }, Button::EventType::PRESSED);

    manager->addBackWidget (text_list);
    manager->addBackWidget (button_cancel);
    manager->addBackWidget (button_ok);

    device->addGuiManager (1, manager);
    device->createWindow (1, "Select file", sfge::VideoMode (400, 380));
}

void SaveFileDialog::dirBrowse (const std::string & dir)
{
    if (!exists (dir)) return;

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

void SaveFileDialog::handleChoise (const std::string & str)
{
}