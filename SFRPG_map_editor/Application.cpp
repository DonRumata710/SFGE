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
#include "Application.h"
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"

#include <SFGE/MenuBar.h>
#include <SFGE/PullDownMenu.h>
#include <SFGE/MenuItem.h>
#include <SFGE/WidgetStyle.h>


using namespace sfge;


const Color BACKGROUND_COLOR (0x22, 0x22, 0x22);
const Color MAIN_COLOR (0x25, 0x26, 0x52);
const Color SECOND_COLOR (0x40, 0x23, 0x9F);
const Color HOVER_COLOR (0x21, 0x27, 0x67);


Application::Application () :
    m_default_resource_manager (std::make_shared<ResourceManager> ()),
    m_custom_resource_manager (std::make_shared<ResourceManager> ())
{
    m_default_resource_manager->loadScript ("media\\resources\\resources.cfg");
    m_default_resource_manager->setDefaultFont (m_default_resource_manager->getFont ("font.standart"));

    m_device.setResourceManager (m_default_resource_manager);

    /// File

    std::shared_ptr<MenuItem> file_create_item (std::make_shared<MenuItem> ());
    file_create_item->setText ("Create");
    file_create_item->attachReaction ([this]() { m_editor->createMap (256, 256, 512); }, Button::EventType::RELEASED);

    std::shared_ptr<MenuItem> file_open_item (std::make_shared<MenuItem> ());
    file_open_item->setText ("Open");
    file_open_item->attachReaction ([this]() { openFileDialog (Action::OPEN_MAP); }, Button::EventType::RELEASED);
    
    std::shared_ptr<MenuItem> file_save_item (std::make_shared<MenuItem> ());
    file_save_item->attachReaction ([this]() { saveMap (); }, Button::EventType::RELEASED);
    file_save_item->setText ("Save");
    
    std::shared_ptr<MenuItem> file_save_as_item (std::make_shared<MenuItem> ());
    file_save_as_item->attachReaction ([this]() { saveFileDialog (); }, Button::EventType::RELEASED);
    file_save_as_item->setText ("Save as");

    std::shared_ptr<MenuItem> file_close_item (std::make_shared<MenuItem> ());
    file_close_item->attachReaction ([this]() { m_editor->closeMap (); }, Button::EventType::RELEASED);
    file_close_item->setText ("Close");
    
    std::shared_ptr<MenuItem> program_close_item (std::make_shared<MenuItem> ());
    program_close_item->setText ("Exit");
    program_close_item->attachReaction ([this]() { m_device.quit (); }, Button::EventType::RELEASED);
    
    std::shared_ptr<PullDownMenu> program_control_menu (std::make_shared<PullDownMenu> ());
    program_control_menu->addItem (file_create_item);
    program_control_menu->addItem (file_open_item);
    program_control_menu->addItem (file_save_item);
    program_control_menu->addItem (file_save_as_item);
    program_control_menu->addItem (file_close_item);
    program_control_menu->addItem (program_close_item);


    /// Resources

    std::shared_ptr<MenuItem> resource_add_item (std::make_shared<MenuItem> ());
    resource_add_item->setText ("Add resource set");
    resource_add_item->attachReaction ([this]() { openFileDialog (Action::ADD_RESOURCES); }, Button::EventType::RELEASED);

    std::shared_ptr<PullDownMenu> resource_control_menu (std::make_shared<PullDownMenu> ());
    resource_control_menu->addItem (resource_add_item);

    
    std::shared_ptr<MenuBar> menu_bar (std::make_shared<MenuBar> ());
    menu_bar->setPosition (iWidget::Position::TOP | iWidget::Position::WIDTH, 0, 0);
    menu_bar->setSize (800, 30);
    menu_bar->addItem ("File", program_control_menu);
    menu_bar->addItem ("Resources", resource_control_menu);
    menu_bar->setBackground (MAIN_COLOR);

    WidgetStyle style;
    style.setView (SECOND_COLOR, iWidget::View::RELEASED);
    style.setView (HOVER_COLOR, iWidget::View::HOVER);
    style.setView (MAIN_COLOR, iWidget::View::PRESSED);
    menu_bar->setItemStyle (style);


    /// Editing

    m_tile_list = std::make_shared<ItemList> ();
    m_tile_list->setPosition (iWidget::Position::RIGHT | iWidget::Position::TOP, 0, 30);
    m_tile_list->setBackground (SECOND_COLOR);
    m_tile_list->setSize (200, 770);


    /// Map drawing

    m_editor = std::make_shared<EditField> ();
    m_editor->setSize (1000, 800);

    pGUIManager edit_window (std::make_unique<GUIManager> (&m_device));
    edit_window->addBackWidget (menu_bar);
    edit_window->addBackWidget (m_tile_list);
    edit_window->addBackWidget (m_editor);
    edit_window->setBackground (BACKGROUND_COLOR);

    m_device.addGuiManager (0, edit_window);
}

Application::~Application ()
{}

int Application::run ()
{
    m_device.createWindow (0, "RPG map editor", sfge::VideoMode (1000, 800));
    return m_device.run ();
}

void Application::setChoisedString (const std::string& str)
{
    m_string = str;
    m_file_select_window.reset ();

    if (m_last_action == OPEN_MAP && !m_string.empty ())
        m_editor->loadMap (m_string);
    else if (m_last_action == SAVE_MAP && !m_string.empty ())
        m_editor->saveMap (m_string);
    else if (m_last_action == ADD_RESOURCES && !m_string.empty ())
    {
        m_custom_resource_manager->loadScript (m_string);
        for (auto texture : m_custom_resource_manager->getTextureList ())
        {
            std::shared_ptr<Button> button (std::make_shared<Button>());
            button->setView (texture.second, iWidget::View::HOVER);
            button->setView (texture.second, iWidget::View::PRESSED);
            button->setView (texture.second, iWidget::View::RELEASED);
            button->setSize (200, 200);
            button->attachReaction ([this, texture]() { m_editor->setTexture (texture.first); }, Button::EventType::PRESSED);

            m_tile_list->addWidget (button, 0);
        }
    }

    m_file_select_window.reset ();
    m_last_action = NONE;
}

void Application::saveMap ()
{
    if (m_string.empty ())
        m_string = "new_map";

    m_editor->saveMap (m_string);
}

void Application::openFileDialog (Action action)
{
    m_last_action = action;
    m_file_select_window = std::make_unique<OpenFileDialog> (this);
}

void Application::saveFileDialog ()
{
    m_last_action = SAVE_MAP;
    m_file_select_window = std::make_unique<SaveFileDialog> (this);
}
