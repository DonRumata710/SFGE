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


#include "LineEdit.h"
#include "GuiManager.h"
#include "Err.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Vertex.hpp>


namespace sfge
{


    LineEdit::LineEdit () :
        m_texture (std::make_unique<sf::RenderTexture> ())
    {
        m_text.setCharacterSize (14);
        m_text.setPosition (m_text.getCharacterSize () / 4, 0);

        setTextColor (sf::Color::White);
    }

    void LineEdit::attachReaction (const std::function<void ()> func, const EventType type)
    {
        switch (type)
        {
        case STRING_CHANGED:
            m_string_changed = func;
            break;
        case INPUT_COMPLETED:
            m_input_completed = func;
            break;
        }
    }

    void LineEdit::attachView (const std::shared_ptr<const sf::Texture> tex)
    {
        m_background.setTexture (tex);
    }

    void LineEdit::attachView (const sf::Color color)
    {
        m_background.setColor (color);
    }

    void LineEdit::setFont (const std::shared_ptr<const sf::Font> font)
    {
        m_text.setFont (*font);
        redraw ();
    }

    void LineEdit::setCharacterSize (const unsigned size)
    {
        m_text.setCharacterSize (size);

        setRect ({ 
            (int) m_outward_view.getPosition ().x,
            (int) m_outward_view.getPosition ().y,
            m_outward_view.getSize ().x,
            m_outward_view.getSize ().y
        });

        redraw ();
    }

    void LineEdit::setTextColor (sf::Color color)
    {
        m_text.setFillColor (color);
        m_line[0].color = color;
        m_line[1].color = color;
    }

    void LineEdit::inputString (const UString& str)
    {
        m_string += str;
        m_text.setString (m_string);
        m_line[0].position.x = m_text.getLocalBounds ().width + m_text.getCharacterSize () / 4;
        m_line[1].position.x = m_text.getLocalBounds ().width + m_text.getCharacterSize () / 4;

        redraw ();
        if (m_string_changed) m_string_changed ();
    }

    void LineEdit::setString (const UString& str)
    {
        m_string = str;
        m_text.setString (str);
        m_line[0].position.x = m_text.getLocalBounds ().width + m_text.getCharacterSize () / 4;
        m_line[1].position.x = m_text.getLocalBounds ().width + m_text.getCharacterSize () / 4;

        redraw ();
        if (m_string_changed) m_string_changed ();
    }

    void LineEdit::deleteChar ()
    {
        if (!m_focused_char) return;

        set_focus_pos (get_focus_pos () - get_width (--m_focused_char));

        m_string.erase (m_focused_char);
        m_text.setString (m_string);

        redraw ();
        if (m_string_changed) m_string_changed ();
    }

    void LineEdit::clear ()
    {
        m_text.setString ("");
        m_string.clear ();
        m_text.setPosition (m_text.getCharacterSize () / 4, m_text.getPosition ().y);
        m_line[0].position.x = m_text.getCharacterSize () / 4;
        m_line[1].position.x = m_text.getCharacterSize () / 4;

        redraw ();
        if (m_string_changed) m_string_changed ();
    }

    UString LineEdit::getString ()
    {
        return m_string;
    }

    void LineEdit::setRect (const PositionDesc& desc)
    {
        m_outward_view.setPosition (desc.x, desc.y);
        m_outward_view.setSize (desc.width, desc.height);

        m_texture->create (desc.width, desc.height);
        m_background.setSize (desc.width, desc.height);
        m_focus.setSize (0, desc.height);

        m_text.setPosition (m_text.getCharacterSize () / 4, (desc.height - m_text.getCharacterSize ()) / 2);
        m_line[0].position.y = (desc.height - m_text.getCharacterSize ()) / 2;
        m_line[1].position.y = (desc.height - m_text.getCharacterSize ()) / 2 + m_text.getCharacterSize ();

        redraw ();
    }

    void LineEdit::enter ()
    {
        m_line[0].position.y = (m_background.getSize ().y - m_text.getCharacterSize ()) / 2;
        m_line[1].position.y = m_text.getCharacterSize () + m_text.getCharacterSize () / 4;
        set_focus_pos (0);
    }

    bool LineEdit::check_key (const sf::Event::KeyEvent& e, const bool is_pressed)
    {
        if (!is_pressed)
            return false;

        switch (e.code)
        {
        case sf::Keyboard::Home:
            m_focused_char = 0;
            set_focus_pos (0);
            break;
        case sf::Keyboard::End:
            m_focused_char = m_string.getSize ();
            set_focus_pos (m_text.getLocalBounds ().width);
            break;
        case sf::Keyboard::Left:
            if (m_focused_char)
            {
                --m_focused_char;
                set_focus_pos (get_focus_pos () - get_width (m_focused_char));
            }
            break;
        case sf::Keyboard::Right:
            if (m_focused_char < m_string.getSize ())
            {
                unsigned width (get_focus_pos ());
                width += get_width (m_focused_char);
                ++m_focused_char;
                set_focus_pos (width);
            }
            break;
        case sf::Keyboard::Delete:
            if (m_focused_char < m_string.getSize ())
            {
                unsigned width (get_focus_pos ());
                width += get_width (m_focused_char);
                ++m_focused_char;
                set_focus_pos (width);
                deleteChar ();
                if (m_string_changed) m_string_changed ();
            }
            break;
        case sf::Keyboard::Return:
            if (m_input_completed) m_input_completed ();
            break;
        default:
            return false;
        }

        m_dc_timer = 0.0;
        m_line[0].color.a = 255;
        m_line[1].color.a = 255;

        redraw ();

        return true;
    }

    void LineEdit::check_text (const sf::Event::TextEvent& text)
    {
        if (text.unicode == 8) deleteChar ();
        else add_char (text.unicode);

        if (m_string_changed) m_string_changed ();

        m_dc_timer = 0.0;
        m_line[0].color.a = 255;
        m_line[1].color.a = 255;

        redraw ();
    }

    void LineEdit::check_mouse_button (const sf::Event::MouseButtonEvent& e, const bool is_pressed)
    {
        unsigned x (e.x - m_outward_view.getPosition ().x - m_text.getCharacterSize () / 4);
        if (is_pressed && e.button == sf::Mouse::Button::Left)
        {
            unsigned width (0);
            for (unsigned i = 0; i < m_string.getSize (); ++i)
            {
                unsigned w (get_width (i));

                if (width + w / 2 > x)
                {
                    m_focused_char = i;
                    break;
                }

                m_focused_char = i + 1;
                width += w;
            }

            m_dc_timer = 0.0f;
            m_line[0].color.a = 255;
            m_line[1].color.a = 255;

            set_focus_pos (width);
        }
    }

    bool LineEdit::check_mouse (const int x, const int y)
    {
        return m_outward_view.contains (x, y);
    }

    void LineEdit::draw (sf::RenderTarget& target) const
    {
        target.draw (m_outward_view, &m_texture->getTexture ());
    }

    void LineEdit::update (const float delta)
    {
        m_dc_timer += delta;
        if (m_dc_timer > 0.7)
        {
            m_dc_timer = 0.0f;
            m_line[0].color.a ^= 255;
            m_line[1].color.a ^= 255;
            redraw ();
        }
    }

    void LineEdit::redraw ()
    {
        m_texture->draw (m_background);
        m_texture->draw (m_focus);
        m_texture->draw (m_text);
        m_texture->draw (m_line, 2, sf::PrimitiveType::Lines);

        m_texture->display ();
    }

    unsigned LineEdit::get_width (const unsigned index) const
    {
        return unsigned (m_text.getFont ()->getGlyph (m_string[index], m_text.getCharacterSize (), false).advance);
    }

    void LineEdit::set_focus_pos (int x)
    {
        m_line[0].position.x = x + (int) m_text.getCharacterSize () / 4;
        m_line[1].position.x = x + (int) m_text.getCharacterSize () / 4;

        if (m_line[0].position.x > m_background.getSize ().x)
        {
            m_text.move (m_background.getSize ().x - m_line[0].position.x, 0);
            m_line[0].position.x = m_background.getSize ().x;
            m_line[1].position.x = m_background.getSize ().x;
        }
        else if (m_line[0].position.x < m_text.getCharacterSize () / 4)
        {
            m_text.move (m_text.getCharacterSize () / 4 - m_line[0].position.x, 0);
            m_line[0].position.x = m_text.getCharacterSize () / 4;
            m_line[1].position.x = m_text.getCharacterSize () / 4;
        }

        redraw ();
    }

    unsigned LineEdit::get_focus_pos () const
    {
        return unsigned (m_line[0].position.x) - m_text.getCharacterSize () / 4;
    }

    void LineEdit::add_char (const sf::Uint32 ch)
    {
        m_string.insert (m_focused_char, sf::String (ch));

        m_text.setString (m_string);

        unsigned offset (get_focus_pos () + get_width (m_focused_char));

        ++m_focused_char;
        set_focus_pos (offset);
    }


}
