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


#include "Application.h"

#include <SFGE/MenuBar.h>
#include <SFGE/PullDownMenu.h>
#include <SFGE/MenuItem.h>


using namespace sfge;


Application::Application () :
    m_resource_manager (true)
{
    m_resource_manager.loadScript ("media\\resources\\resources.cfg");
    m_resource_manager.setDefaultFont (m_resource_manager.getFont ("font.standart"));

    std::shared_ptr<MenuItem> file_create_item (std::make_shared<MenuItem> ());
    file_create_item->setText ("Create");

    std::shared_ptr<MenuItem> file_open_item (std::make_shared<MenuItem> ());
    file_open_item->setText ("Open");
    
    std::shared_ptr<MenuItem> file_save_item (std::make_shared<MenuItem> ());
    file_save_item->setText ("Save");
    
    std::shared_ptr<MenuItem> file_save_as_item (std::make_shared<MenuItem> ());
    file_save_as_item->setText ("Save as");

    std::shared_ptr<MenuItem> file_close_item (std::make_shared<MenuItem> ());
    file_close_item->setText ("Close");
    
    std::shared_ptr<MenuItem> program_close_item (std::make_shared<MenuItem> ());
    program_close_item->setText ("Exit");
    program_close_item->attachReaction ([this]() { m_device.quit (); }, Button::EventType::RELEASED);
    
    std::shared_ptr<PullDownMenu> program_control_menu (std::make_shared<PullDownMenu> ());
    program_control_menu->addItem (file_create_item);
    program_control_menu->addItem (file_open_item);
    program_control_menu->addItem (file_save_item);
    program_control_menu->addItem (file_save_as_item);
    program_control_menu->addItem (program_close_item);
    
    std::shared_ptr<MenuBar> menu_bar (std::make_shared<MenuBar> ());
    menu_bar->setPosition (iWidget::Position::TOP | iWidget::Position::WIDTH, 0, 0);
    menu_bar->setSize (800, 30);
    menu_bar->addItem ("File", program_control_menu);
    menu_bar->setView (Color (0x25, 0x06, 0x72));
    menu_bar->setItemView (Color (0x40, 0x13, 0xAF), iWidget::View::RELEASED);
    menu_bar->setItemView (Color (0x71, 0x47, 0xD7), iWidget::View::HOVER);
    menu_bar->setItemView (Color (0x25, 0x06, 0x72), iWidget::View::PRESSED);

    pGUIManager edit_window (std::make_unique<GUIManager> (&m_device));
    edit_window->addBackWidget (menu_bar);

    m_device.addGuiManager (0, edit_window);
}

Application::~Application ()
{}

int Application::run ()
{
    m_device.createWindow (0, "RPG map editor", sfge::VideoMode (1000, 800));
    return m_device.run ();
}
