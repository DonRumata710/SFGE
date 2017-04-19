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


#include "ResourceLoader.h"
#include "ResourceParser.h"
#include "TextParser.h"
#include "Err.h"

#include <SFML/Graphics/Font.hpp>
#include "Animation.h"
#include "File.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <fstream>
#include <sstream>
#include <cstring>

#include "Err.h"



namespace sfge
{


    class RepeateException
    {};


    void log_undefined_base_resource (const std::string& name)
    {
        debug_message ("Resource \"" + name + "\" wasn't defined");
    }


    char* ResourceParser::load_script (const char* path, size_t* size)
    {
        std::ifstream data (path);

        if (!data.is_open ()) return nullptr;

        std::ostringstream buf;
        buf << data.rdbuf ();
        std::string str (buf.str ());

        data.close ();

        char* ptr (new char[str.size () + 1]);
        std::memcpy (ptr, str.c_str (), str.size ());
        ptr[str.size ()] = '\0';

        return ptr;
    }

    
    bool ResourceParser::parse_script (ResourceLoader* rm, const char* path)
    {
        size_t size (0);
        char* script (load_script (path, &size));

        if (!script) return false;

        TextParser tp (script);

        for (;;)
        {
            tp.get_token ();
            if (tp.get_tokentype () == TextParser::TTEND)
            {
                break;
            }
            else if (tp.get_tokentype () == TextParser::TTRES_INCLUDE)
            {
                tp.get_token ();
                if (!parse_script (rm, tp.tkn_string ())) runtime_error ("Loading script failed!");
            }

            else if (tp.get_tokentype () > TextParser::TTRES__FIRST && tp.get_tokentype () < TextParser::TTRES__LAST)
            {
                try
                {
                    Resource restype (Resource (tp.get_tokentype () - TextParser::TTRES__FIRST - 1));

                    tp.get_token ();
                    char name[256] = { 0 };
                    std::strcpy (name, tp.tkn_string ());

                    tp.get_token ();

                    char basename[256] = { 0 };
                    if (tp.get_tokentype () == TextParser::TTBASED)
                    {
                        tp.get_token ();
                        std::strcpy (basename, tp.tkn_string ());
                        tp.get_token ();
                    }

                    if (tp.get_tokentype () == TextParser::TTOPENBLOCK)
                    {
                        switch (restype)
                        {
                        case FONT:
                            if (rm->findFont (name)) throw RepeateException ();
                            if (!rm->findFont (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_font (rm, &tp, name, basename);
                            break;
                        case IMAGE:
                            if (rm->findImage (name)) throw RepeateException ();
                            if (!rm->findImage (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_image (rm, &tp, name, basename);
                            break;
                        case TEXTURE:
                            if (rm->findTexture (name)) throw RepeateException ();
                            if (!rm->findTexture (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_texture (rm, &tp, name, basename);
                            break;
                        case SPRITE:
                            if (rm->findSprite (name).texture) throw RepeateException ();
                            if (!rm->findSprite (basename).texture)
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_sprite (rm, &tp, name, basename);
                            break;
                        case ANIMATION:
                            if (rm->findSprite (name).texture) throw RepeateException ();
                            if (!rm->findSprite (basename).texture)
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_animation (rm, &tp, name, basename);
                            break;
                        case FILE:
                            if (rm->findFile (name)) throw RepeateException ();
                            if (!rm->findFile (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_file_resource (rm, &tp, name, basename);
                            break;
                        case SOUND:
                            if (rm->findSound (name)) throw RepeateException ();
                            if (!rm->findSound (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_effect (rm, &tp, name, basename);
                            break;
                        case MUSIC:
                            if (rm->findMusic (name)) throw RepeateException ();
                            if (!rm->findMusic (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_music (rm, &tp, name, basename);
                            break;
                        case PARTICLE:
                            if (rm->findParticle (name)) throw RepeateException ();
                            if (!rm->findParticle (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_particle (rm, &tp, name, basename);
                            break;
                        case DISTORT:
                            if (rm->findDistortion (name)) throw RepeateException ();
                            if (!rm->findDistortion (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_distort (rm, &tp, name, basename);
                            break;
                        case STRTABLE:
                            if (rm->findStringTable (name)) throw RepeateException ();
                            if (!rm->findStringTable (basename))
                            {
                                log_undefined_base_resource (basename);
                                basename[0] = '\0';
                            }
                            parse_string_table (rm, &tp, name, basename);
                            break;
                        }
                    }
                    else
                    {
                        debug_message ("Illegal resource syntax in line " + std::to_string (tp.get_line ()) + ". '{' expected.");
                        while ((tp.get_tokentype () <= TextParser::TTRES__FIRST || tp.get_tokentype () >= TextParser::TTRES__LAST) && tp.get_tokentype () != TextParser::TTEND)
                        {
                            tp.get_token ();
                        }
                        tp.put_back ();
                    }
                }
                catch (RepeateException)
                {
                    while ((tp.get_tokentype () <= TextParser::TTRES__FIRST || tp.get_tokentype () >= TextParser::TTRES__LAST) && tp.get_tokentype () != TextParser::TTEND)
                    {
                        tp.get_token ();
                    }
                    tp.put_back ();
                    continue;
                }
            }
            else
            {
                debug_message ("Unrecognized resource specificator in line " + std::to_string (tp.get_line ()) + ".");
                while ((tp.get_tokentype () <= TextParser::TTRES__FIRST || tp.get_tokentype () >= TextParser::TTRES__LAST) && tp.get_tokentype () != TextParser::TTEND)
                {
                    tp.get_token ();
                }
                tp.put_back ();
            }
        }

        delete[] script;

        return true;
    }


    void ResourceParser::parse_font (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        std::shared_ptr<sf::Font> font (std::make_shared<sf::Font> ());

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                font->loadFromFile (tp->tkn_string ());
            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        rm->addFont (name, font);
    }

    void ResourceParser::parse_image (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        std::shared_ptr<sf::Image> image (std::make_shared<sf::Image> ());

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                image->loadFromFile (tp->tkn_string ());
            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        rm->addImage (name, image);
    }


    void ResourceParser::parse_texture (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        std::shared_ptr<sf::Texture> texture (std::make_shared<sf::Texture> ());

        sf::IntRect rect;

        char path[256] = { 0 };

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_RECT:
                tp->get_token ();
                tp->get_token ();
                rect.left = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                rect.top = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                rect.width = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                rect.height = tp->tkn_int ();
                break;
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                std::strcpy (path, tp->tkn_string ());
                break;

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        if (!texture->loadFromFile (path, rect))
            debug_message ("Texture wasn't loaded");
        rm->addTexture (name, texture);
    }

    void ResourceParser::parse_sprite (ResourceLoader * rm, TextParser * tp, const char * name, const char * basename)
    {
        SpriteDesc sprite;

        char path[256] = { 0 };

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_RECT:
                tp->get_token ();
                tp->get_token ();
                sprite.rect.left = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                sprite.rect.top = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                sprite.rect.width = tp->tkn_int ();
                tp->get_token ();
                tp->get_token ();
                sprite.rect.height = tp->tkn_int ();
                break;
            case TextParser::TTPAR_TEXTURE:
                tp->get_token ();
                tp->get_token ();
                std::strcpy (path, tp->tkn_string ());
                break;
            case TextParser::TTPAR_HOTSPOT:
                tp->get_token ();
                tp->get_token ();
                sprite.hotspot.x = tp->tkn_float ();
                tp->get_token ();
                tp->get_token ();
                sprite.hotspot.y = tp->tkn_float ();
                break;

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        sprite.texture = std::make_shared<sf::Texture> ();
        if (!sprite.texture->loadFromFile (path, sprite.rect))
            debug_message ("Sprite wasn't loaded");
        rm->addTexture (name, sprite.texture);
        rm->addSprite (name, sprite);
    }

    void ResourceParser::parse_animation (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        AnimationDesc animation;
        if (basename && basename[0] != '\0')
        {
            animation = rm->findAnimation (basename);
        }
        else
        {
            animation.texture = std::make_shared<sf::Texture> ();
            rm->addTexture (name, animation.texture);
        }

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_TEXTURE:
                tp->get_token ();
                tp->get_token ();
                if (!animation.texture->loadFromFile (tp->tkn_string ()))
                    debug_message ("Animation wasn't loaded");
                break;

            case TextParser::TTPAR_HOTSPOT:
                tp->get_token ();
                tp->get_token ();
                animation.hotspot.x = tp->tkn_float ();
                tp->get_token ();
                tp->get_token ();
                animation.hotspot.y = tp->tkn_float ();
                break;

            case TextParser::TTPAR_FRAMES:
                if (true)
                {
                    tp->get_token ();
                    tp->get_token ();
                    animation.frames = tp->tkn_int ();
                    break;
                }

            case TextParser::TTPAR_ROWS:
                if (true)
                {
                    tp->get_token ();
                    tp->get_token ();
                    animation.rows = tp->tkn_int ();
                    break;
                }

            case TextParser::TTPAR_COLUMNS:
                if (true)
                {
                    tp->get_token ();
                    tp->get_token ();
                    animation.cols = tp->tkn_int ();
                    break;
                }

            case TextParser::TTPAR_FPS:
                if (true)
                {
                    tp->get_token ();
                    tp->get_token ();
                    animation.fps = tp->tkn_float ();
                    break;
                }

            case TextParser::TTPAR_START:
                if (true)
                {
                    tp->get_token ();
                    tp->get_token ();
                    animation.start = tp->tkn_int ();
                    break;
                }

            case TextParser::TTPAR_MODE:
                if (true)
                {
                    int mode (Animation::FWD | Animation::LOOP);
                    for (;;)
                    {
                        tp->get_token ();
                        if (tp->get_tokentype () != TextParser::TTEQUALS && tp->get_tokentype () != TextParser::TTSEPARATOR)
                        {
                            tp->put_back ();
                            break;
                        }

                        switch (tp->get_token ())
                        {
                        case TextParser::TTCON_FORWARD:
                            mode &= ~Animation::REV;
                            break;

                        case TextParser::TTCON_REVERSE:
                            mode |= Animation::REV;
                            break;

                        case TextParser::TTCON_NOPINGPONG:
                            mode &= ~Animation::PINGPONG;
                            break;

                        case TextParser::TTCON_PINGPONG:
                            mode |= Animation::PINGPONG;
                            break;

                        case TextParser::TTCON_NOLOOP:
                            mode &= ~Animation::LOOP;
                            break;

                        case TextParser::TTCON_LOOP:
                            mode |= Animation::LOOP;
                            break;

                        default:
                            //tp->ScriptPostError ("Unsupported value ", ".");
                            break;
                        }
                    }
                    animation.mode = mode;
                    break;
                }

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        rm->addAnimation (name, animation);
    }


    void ResourceParser::parse_file_resource (ResourceLoader* rm, TextParser* tp, const char *name, const char* basename)
    {
        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                rm->addFile (name, std::make_shared<File> (tp->tkn_string ()));
                break;

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }
    }

    void ResourceParser::parse_effect (ResourceLoader * rm, TextParser * tp, const char * name, const char * basename)
    {
        char path[256] = { 0 };

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                std::strcpy (path, tp->tkn_string ());
                break;

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        std::shared_ptr<sf::SoundBuffer> sound (std::make_shared<sf::SoundBuffer> ());
        if (!sound->loadFromFile (path))
            debug_message ("Effect wasn't loaded");
        rm->addSound (name, sound);
    }

    void ResourceParser::parse_music (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        char path[256] = { 0 };

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {
            case TextParser::TTPAR_FILENAME:
                tp->get_token ();
                tp->get_token ();
                std::strcpy (path, tp->tkn_string ());
                break;

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }

        std::shared_ptr<sf::Music> music (std::make_shared<sf::Music> ());
        if (!music->openFromFile (path))
            debug_message ("Music wasn't loaded");
    }

    void ResourceParser::parse_target (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }
    }

    void ResourceParser::parse_particle (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }
    }

    void ResourceParser::parse_distort (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }
    }

    void ResourceParser::parse_string_table (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (tp->scriptSkipToNextParameter (false))
        {
            switch (tp->get_tokentype ())
            {

            default:
                tp->scriptSkipToNextParameter (true);
                break;
            }
        }
    }


}