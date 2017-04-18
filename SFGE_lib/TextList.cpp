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


#include "TextList.h"
#include "GuiManager.h"
#include "Err.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>



namespace sfge
{


    TextList::TextList () : m_texture (std::make_unique<sf::RenderTexture> ())
    {}

    void TextList::attachReaction (const std::function<void ()> func, const EventType type)
    {
        switch (type)
        {
        case FOCUS_CHANGED:
            m_focus_moved = func;
            break;
        case ITEM_SELECTED:
            m_item_selected = func;
            break;
        default:
            break;
        }
    }

    void TextList::attachView (const std::shared_ptr<const sf::Texture> tex)
    {
        m_background.setTexture (tex);
    }

    void TextList::attachView (const sf::Color color)
    {
        m_background.setColor (color);
    }

    void TextList::setFont (const std::shared_ptr<const sf::Font> font)
    {
        m_font = font;

        for (std::shared_ptr<sf::Text> text : m_string_list)
            text->setFont (*font);
    }

    void TextList::setCharacterSize (const unsigned size)
    {
        m_character_size = size;
    }

    void TextList::addString (const UString& str)
    {
        if (str.isEmpty ()) return;

        //if ((m_string_list.size () + 1) * (m_character_size + m_character_size / 4) > m_outward_view.getSize ().y)
        //{
        //    runtime_error ("Text list is overloaded.");
        //    return;
        //}

        auto text (std::make_shared<sf::Text> (str, *m_font));
        text->setCharacterSize (m_character_size);
        text->setPosition (
            float (m_character_size / 4),
            float (m_offset + m_string_list.size () * (m_character_size + m_character_size / 4) + m_character_size / 8)
        );
        m_string_list.push_back (text);
    }

    void TextList::removeString (const UString& str)
    {
        for (auto text = m_string_list.begin (); text != m_string_list.end (); ++text)
        {
            if ((*text)->getString () == str)
            {
                m_string_list.erase (text);
                return;
            }
        }
    }

    std::string TextList::getCurrent () const
    {
        if (m_current_focus < m_string_list.size ())
            return m_string_list[m_current_focus]->getString ();
        else
            return "";
    }

    void TextList::setRect (const PositionDesc & desc)
    {
        m_outward_view.setPosition (desc.x, desc.y);
        m_outward_view.setSize (desc.width, desc.height);

        m_texture->create (desc.width, desc.height);
        m_background.setSize (desc.width, desc.height);
        m_focus.setSize (desc.width, m_character_size + m_character_size / 4);

        replace_text ();
    }

    void TextList::enter ()
    {
        for (std::shared_ptr<sf::Text> text : m_string_list)
            text->setFont (*m_font);

        if (m_current_focus > m_string_list.size ())
            m_focus.setSize (0, m_character_size);

        m_focus.setColor (sf::Color (64, 64, 64, 127));
        m_focus.setSize (m_background.getSize ().x, m_character_size + m_character_size / 4);
        m_focus.setPosition (0, m_background.getSize ().y);

        replace_text ();
    }

    bool TextList::check_key (const sf::Event::KeyEvent& e, const bool is_pressed)
    {
        if (!is_pressed)
        {
            m_is_key_pressed = false;
            return false;
        }

        if (!m_is_keyboard_mod || m_is_key_pressed) return false;

        switch (e.code)
        {
        case sf::Keyboard::Up:
            set_focus (m_current_focus - 1);
            if (m_focus_moved) m_focus_moved ();
            m_is_key_pressed = true;
            break;
        case sf::Keyboard::Down:
            set_focus (m_current_focus + 1);
            if (m_focus_moved) m_focus_moved ();
            m_is_key_pressed = true;
            break;
        case sf::Keyboard::Return:
            if (m_item_selected) m_item_selected ();
            break;
        case sf::Keyboard::Escape:
            m_is_keyboard_mod = false;
            break;
        default:
            return false;
        }

        return true;
    }

    void TextList::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool pressed)
    {
        unsigned new_focus (count_index (e.y - m_outward_view.getPosition ().y));

        if (pressed)
        {
            //m_is_pressed = true;
            //if (m_dc_timer < 0.3 && new_focus == m_current_focus)
            //{
            //    if (m_item_selected)
            //        m_item_selected ();
            //}
            //else
            //{
            set_focus (new_focus);
            if (m_focus_moved) m_focus_moved ();
            m_is_keyboard_mod = true;
            //}
        }
        else if (!m_is_keyboard_mod)
            set_focus (new_focus);
    }

    void TextList::check_wheel (const sf::Event::MouseWheelScrollEvent& e)
    {
        if (!m_is_keyboard_mod) return;

        if (e.delta < 0.0f)
        {
            set_focus (m_current_focus + 1);
            if (m_focus_moved) m_focus_moved ();
        }
        else if (e.delta > 0.0f)
        {
            set_focus (m_current_focus - 1);
            if (m_focus_moved) m_focus_moved ();
        }
    }

    void TextList::check_click ()
    {
        if (m_item_selected)
            m_item_selected ();
    }

    bool TextList::check_mouse (const int x, const int y)
    {
        if (m_outward_view.contains (x, y))
        {
            if (!m_is_keyboard_mod)
                set_focus (count_index (y - m_outward_view.getPosition ().y));

            return true;
        }
        else
            return false;
    }

    void TextList::draw (sf::RenderTarget& target) const
    {
        target.draw (m_outward_view, &m_texture->getTexture ());
    }

    unsigned TextList::count_index (const unsigned y) const
    {
        return (y - m_offset) / (m_character_size + m_character_size / 4U);
    }

    unsigned TextList::count_position (const unsigned index) const
    {
        return m_offset + index * (m_character_size + m_character_size / 4U);
    }

    void TextList::set_focus (unsigned line)
    {
        if (line >= m_string_list.size ())
        {
            m_focus.setPosition (0, m_background.getSize ().y);
            return;
        }

        if (m_current_focus == line)
            return;

        m_current_focus = line;
        if (m_focus_moved) m_focus_moved ();

        int y_pos (count_position (line));

        if (m_is_keyboard_mod)
        {
            if (y_pos < 0)
            {
                m_offset -= y_pos;
                y_pos = 0;
            }
            else if (y_pos + m_character_size + m_character_size / 4 > m_background.getSize ().y)
            {
                int offset (y_pos + m_character_size + m_character_size / 4 - m_background.getSize ().y);
                m_offset -= offset;
                y_pos -= offset;
            }
        }

        m_focus.setPosition (0, y_pos);

        replace_text ();
    }

    void TextList::replace_text ()
    {
        if (m_string_list.empty ()) return;

        unsigned text_pos (0);

        for (std::shared_ptr<sf::Text> text : m_string_list)
        {
            text->setPosition (m_character_size / 4, m_offset + int (text_pos + m_character_size / 8));
            text_pos += m_character_size + m_character_size / 4;
        }

        redraw ();
    }

    void TextList::redraw ()
    {
        m_texture->draw (m_background);
        m_texture->draw (m_focus);

        for (std::shared_ptr<sf::Text> text : m_string_list)
            m_texture->draw (*text);

        m_texture->display ();
    }


}
