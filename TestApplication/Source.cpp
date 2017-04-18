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


#include <Button.h>
#include <Slider.h>
#include <TextList.h>
#include <LineEdit.h>
#include <CheckBox.h>
#include <Label.h>
#include <GuiManager.h>
#include <GEDevice.h>

#include <Panel.h>

#include <ResourceManager.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


using namespace sfge;


int main ()
{
    GEDevice device;
    pGUIManager manager (std::make_unique<GUIManager> (&device));
    pGUIManager child_win (std::make_unique<GUIManager> (&device));


    ResourceManager rm;
    if (!rm.loadScript ("resources.cfg")) return 1;



    std::shared_ptr<Label> text = (std::make_shared<Label> ());
    text->setString (" ");
    text->setFont (rm.getFont ("font.standart"));
    text->setPosition (iWidget::Position::TOP | iWidget::Position::LEFT, 0, 0);
    text->setCharacterSize (14);



    std::shared_ptr<Button> button (std::make_shared<Button> ());
    button->attachReaction ([&device]() { device.createWindow (1, "Select string", VideoMode (400, 400), sf::Style::Default); }, Button::EventType::RELEASED);
    button->attachView (rm.findTexture ("button.released"), Button::RELEASED);
    button->attachView (rm.findTexture ("button.pressed"), Button::PRESSED);
    button->setPosition (iWidget::Position::HCENTER | iWidget::Position::VCENTER, 0, 0);
    button->setText ("Open Window");
    button->setFont (rm.getFont ("font.standart"));
    button->setSize (100, 50);



    std::shared_ptr<LineEdit> line_edit (std::make_shared<LineEdit> ());
    line_edit->setSize (400, 20);
    line_edit->attachView (sf::Color (32, 32, 32));
    line_edit->setString ("Write here...");
    line_edit->setFont (rm.getFont ("font.standart"));
    line_edit->setPosition (iWidget::Position::TOP | iWidget::Position::HCENTER, 0, 120);
    line_edit->attachReaction ([line_edit, text]() {text->setString (line_edit->getString ()); }, LineEdit::EventType::STRING_CHANGED);



    std::shared_ptr<TextList> text_list (std::make_shared<TextList> ());
    text_list->setSize (400, 100);
    text_list->attachView (rm.findTexture ("text_list.background"));
    text_list->addString ("first item");
    text_list->addString ("second item");
    text_list->addString ("third item");
    text_list->addString ("forth item");
    text_list->addString ("fifth item");
    text_list->addString ("sixth item");
    text_list->addString ("seventh item");
    text_list->addString ("eighth item");
    text_list->setFont (rm.getFont ("font.standart"));
    text_list->setPosition (iWidget::Position::TOP | iWidget::Position::HCENTER, 0, 10);
    text_list->attachReaction (
        [text_list, line_edit]() { line_edit->setString (text_list->getCurrent ()); },
        TextList::EventType::ITEM_SELECTED
    );
    text_list->attachReaction (
        [text_list, text]() { text->setString (text_list->getCurrent ()); },
        TextList::EventType::FOCUS_CHANGED
    );



    std::shared_ptr<CheckBox> check_box1 (std::make_shared<CheckBox> ());
    check_box1->attachView (rm.getTexture ("checkbox.background"), CheckBox::BACKGROUND);
    check_box1->attachView (rm.getTexture ("checkbox.flag"), CheckBox::FLAG);
    check_box1->setPosition (iWidget::Position::BOTTOM | iWidget::Position::HCENTER, 0, 0);

    std::shared_ptr<CheckBox> check_box2 (std::make_shared<CheckBox> ());
    check_box2->attachView (rm.getTexture ("checkbox.background"), CheckBox::BACKGROUND);
    check_box2->attachView (rm.getTexture ("checkbox.flag"), CheckBox::FLAG);
    check_box2->setPosition (iWidget::Position::BOTTOM | iWidget::Position::HCENTER, 0, 50);


    check_box1->addCollision (check_box2);
    check_box2->addCollision (check_box1);



    child_win->addBackWidget (text_list);
    child_win->addBackWidget (line_edit);



    manager->addBackWidget (button);
    manager->addBackWidget (text);
    manager->addBackWidget (check_box1);
    manager->addBackWidget (check_box2);
    manager->setBackground (rm.findTexture ("background.menu"));



    device.addGuiManager (0, manager);
    device.addGuiManager (1, child_win);
    device.createWindow (0, "SFML 1", sfge::VideoMode (800, 800));



    return device.run ();
}