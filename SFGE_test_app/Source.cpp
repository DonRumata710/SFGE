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


#include <SFGE/Button.h>
#include <SFGE/Slider.h>
#include <SFGE/TextList.h>
#include <SFGE/LineEdit.h>
#include <SFGE/CheckBox.h>
#include <SFGE/Label.h>
#include <SFGE/MenuBar.h>
#include <SFGE/MenuItem.h>
#include <SFGE/PullDownMenu.h>
#include <SFGE/GuiManager.h>
#include <SFGE/GEDevice.h>

#include <SFGE/Panel.h>

#include <SFGE/ResourceManager.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


using namespace sfge;


int main ()
{
    GEDevice device;
    pGUIManager manager (std::make_unique<GUIManager> (&device));
    pGUIManager child_win (std::make_unique<GUIManager> (&device));


    ResourceManager rm (true);
    if (!rm.loadScript ("media\\resources\\resources.cfg")) return 1;

    rm.setDefaultFont (rm.getFont ("font.standart"));



    std::shared_ptr<MenuItem> openWindowItem (std::make_shared<MenuItem> ());
    openWindowItem->attachReaction ([&device]() { device.createWindow (1, "Select string", VideoMode (400, 400), Style::Default); }, Button::EventType::RELEASED);
    openWindowItem->setText ("Open window");
    openWindowItem->setFont (rm.getFont ("font.standart"));

    std::shared_ptr<MenuItem> closeProgramItem (std::make_shared<MenuItem> ());
    closeProgramItem->attachReaction ([&device]() { device.quit (); }, Button::EventType::RELEASED);
    closeProgramItem->setText ("Exit");
    closeProgramItem->setFont (rm.getFont ("font.standart"));


    std::shared_ptr<PullDownMenu> program_control (std::make_shared<PullDownMenu> ());
    program_control->addItem (openWindowItem);
    program_control->addItem (closeProgramItem);


    std::shared_ptr<MenuBar> menu_bar (std::make_shared<MenuBar> ());
    menu_bar->setPosition (iWidget::Position::TOP | iWidget::Position::WIDTH, 0, 0);
    menu_bar->setSize (800, 30);
    menu_bar->addItem ("Program", program_control);
    menu_bar->setView (Color (0x23F85A));
    menu_bar->setItemView (rm.findTexture ("button.released"), iWidget::View::RELEASED);
    menu_bar->setItemView (rm.findTexture ("button.hover"), iWidget::View::HOVER);
    menu_bar->setItemView (rm.findTexture ("button.pressed"), iWidget::View::PRESSED);

    

    std::shared_ptr<Label> text = (std::make_shared<Label> ());
    text->setString (" ");
    text->setFont (rm.getFont ("font.standart"));
    text->setPosition (iWidget::Position::TOP | iWidget::Position::LEFT, 0, 40);
    text->setCharacterSize (14);



    std::shared_ptr<Button> button (std::make_shared<Button> ());
    button->attachReaction ([&device]() { device.createWindow (1, "Select string", VideoMode (400, 400), sf::Style::Default); }, Button::EventType::RELEASED);
    button->setView (rm.findTexture ("button.released"), Button::View::RELEASED);
    button->setView (rm.findTexture ("button.hover"), Button::View::HOVER);
    button->setView (rm.findTexture ("button.pressed"), Button::View::PRESSED);
    button->setPosition (iWidget::Position::HCENTER | iWidget::Position::VCENTER, 0, 0);
    button->setText ("Open window");
    button->setFont (rm.getFont ("font.standart"));
    button->setSize (100, 50);



    std::shared_ptr<LineEdit> line_edit (std::make_shared<LineEdit> ());
    line_edit->setSize (400, 20);
    line_edit->setView (sf::Color (32, 32, 32));
    line_edit->setString ("Write here...");
    line_edit->setFont (rm.getFont ("font.standart"));
    line_edit->setPosition (iWidget::Position::TOP | iWidget::Position::HCENTER, 0, 120);
    line_edit->attachReaction ([line_edit, text]() {text->setString (line_edit->getString ()); }, LineEdit::EventType::STRING_CHANGED);



    std::shared_ptr<TextList> text_list (std::make_shared<TextList> ());
    text_list->setSize (400, 100);
    text_list->setView (rm.findTexture ("text_list.background"));
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
    check_box1->setSize (50, 50);
    check_box1->setView (rm.getTexture ("checkbox.background"), CheckBox::BACKGROUND);
    check_box1->setView (rm.getTexture ("checkbox.flag"), CheckBox::FLAG);
    check_box1->setPosition (iWidget::Position::BOTTOM | iWidget::Position::HCENTER, 0, 0);

    std::shared_ptr<CheckBox> check_box2 (std::make_shared<CheckBox> ());
    check_box2->setSize (50, 50);
    check_box2->setView (rm.getTexture ("checkbox.background"), CheckBox::BACKGROUND);
    check_box2->setView (rm.getTexture ("checkbox.flag"), CheckBox::FLAG);
    check_box2->setPosition (iWidget::Position::BOTTOM | iWidget::Position::HCENTER, 0, 50);


    check_box1->addCollision (check_box2);
    check_box2->addCollision (check_box1);



    child_win->addBackWidget (text_list);
    child_win->addBackWidget (line_edit);



    manager->addBackWidget (menu_bar);
    manager->addBackWidget (button);
    manager->addBackWidget (text);
    manager->addBackWidget (check_box1);
    manager->addBackWidget (check_box2);
    manager->setBackground (rm.findTexture ("background.menu"));



    device.addGuiManager (0, manager);
    device.addGuiManager (1, child_win);
    device.createWindow (0, "SFGE test application", sfge::VideoMode (800, 800));

    return device.run ();
}