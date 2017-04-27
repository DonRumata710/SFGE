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

    enum Token : size_t
    {
        TTNONE, TTEND, TTNUMBER, TTSTRING,

        TTBOOL, TTEQUALS, TTBASED, TTSEPARATOR, TTOPENBLOCK, TTCLOSEBLOCK,

        TTRES__FIRST,
        TTRES_INCLUDE, TTRES_FONT, TTRES_IMAGE, TTRES_TEXTURE, TTRES_SPRITE,
        TTRES_ANIMATION, TTRES_FILE, TTRES_SOUND, TTRES_MUSIC,
        TTRES_PARTICLE, TTRES_DISTORT, TTRES_STRTABLE,
        TTRES__LAST,

        TTPAR__FIRST,
        TTPAR_FILENAME, TTPAR_RESGROUP, TTPAR_MIPMAP, TTPAR_AMPLIFY, TTPAR_SIZE, TTPAR_ZBUFFER,
        TTPAR_TEXTURE, TTPAR_RECT, TTPAR_HOTSPOT, TTPAR_BLENDMODE, TTPAR_COLOR,
        TTPAR_ZORDER, TTPAR_FLIP, TTPAR_SCALE, TTPAR_PROPORTION, TTPAR_ROTATION, TTPAR_FRAMES,
        TTPAR_FPS, TTPAR_MODE, TTPAR_TRACKING, TTPAR_SPACING, TTPAR_SPRITE, TTPAR_MESH, TTPAR_COLUMNS, TTPAR_ROWS, TTPAR_START,
        TTPAR__LAST,

        TTCON__FIRST,
        TTCON_COLORMUL, TTCON_COLORADD, TTCON_ALPHABLND, TTCON_ALPHAADD, TTCON_ZWRITE,
        TTCON_NOZWRITE, TTCON_FORWARD, TTCON_REVERSE, TTCON_PINGPONG, TTCON_NOPINGPONG,
        TTCON_LOOP, TTCON_NOLOOP, TTCON_CIRCLE, TTCON_RECT, TTCON_ALPHA,
        TTCON__LAST
    };


    std::unordered_map<std::string, const size_t> keytable = {
        { "=",			Token::TTEQUALS },
        { ":",			Token::TTBASED },
        { ",",			Token::TTSEPARATOR },
        { "{",			Token::TTOPENBLOCK },
        { "}",			Token::TTCLOSEBLOCK },
        { "true",		Token::TTBOOL },
        { "false",		Token::TTBOOL },

        { "Include",	Token::TTRES_INCLUDE },
        { "Resource",	Token::TTRES_FILE },
        { "Texture",	Token::TTRES_TEXTURE },
        { "Sound",		Token::TTRES_SOUND },
        { "Music",		Token::TTRES_MUSIC },
        { "Image",      Token::TTRES_IMAGE },
        { "Sprite",		Token::TTRES_SPRITE },
        { "Animation",	Token::TTRES_ANIMATION },
        { "Font",		Token::TTRES_FONT },
        { "Particle",	Token::TTRES_PARTICLE },
        { "Distortion",	Token::TTRES_DISTORT },
        { "StringTable",Token::TTRES_STRTABLE },

        { "filename",	Token::TTPAR_FILENAME },
        { "resgroup",	Token::TTPAR_RESGROUP },
        { "mipmap",		Token::TTPAR_MIPMAP },
        { "amplify",	Token::TTPAR_AMPLIFY },
        { "size",		Token::TTPAR_SIZE },
        { "zbuffer",	Token::TTPAR_ZBUFFER },
        { "texture",	Token::TTPAR_TEXTURE },
        { "rect",		Token::TTPAR_RECT },
        { "hotspot",	Token::TTPAR_HOTSPOT },
        { "blendmode",	Token::TTPAR_BLENDMODE },
        { "color",		Token::TTPAR_COLOR },
        { "zorder",		Token::TTPAR_ZORDER },
        { "flip",		Token::TTPAR_FLIP },
        { "scale",		Token::TTPAR_SCALE },
        { "proportion",	Token::TTPAR_PROPORTION },
        { "rotation",	Token::TTPAR_ROTATION },
        { "frames",		Token::TTPAR_FRAMES },
        { "fps",		Token::TTPAR_FPS },
        { "mode",		Token::TTPAR_MODE },
        { "tracking",	Token::TTPAR_TRACKING },
        { "spacing",	Token::TTPAR_SPACING },
        { "sprite",		Token::TTPAR_SPRITE },
        { "mesh",		Token::TTPAR_MESH },
        { "columns",    Token::TTPAR_COLUMNS },
        { "rows",       Token::TTPAR_ROWS },
        { "start",      Token::TTPAR_START },

        { "COLORMUL",	Token::TTCON_COLORMUL },
        { "COLORADD",	Token::TTCON_COLORADD },
        { "ALPHABLEND",	Token::TTCON_ALPHABLND },
        { "ALPHAADD",	Token::TTCON_ALPHAADD },
        { "ZWRITE",		Token::TTCON_ZWRITE },
        { "NOZWRITE",	Token::TTCON_NOZWRITE },
        { "FORWARD",	Token::TTCON_FORWARD },
        { "REVERSE",	Token::TTCON_REVERSE },
        { "PINGPONG",	Token::TTCON_PINGPONG },
        { "NOPINGPONG",	Token::TTCON_NOPINGPONG },
        { "LOOP",		Token::TTCON_LOOP },
        { "NOLOOP",		Token::TTCON_NOLOOP },
        { "CIRCLE",		Token::TTCON_CIRCLE },
        { "RECT",		Token::TTCON_RECT },
        { "ALPHA",		Token::TTCON_ALPHA }
    };




    bool ResourceParser::scriptSkipToNextParameter (TextParser *tp, bool ignore)
    {
        bool bToBeIgnored = ignore;
        if (ignore)
        {
            tp->putBack ();
        }

        for (;;)
        {
            tp->getToken ();
            if (tp->getTokentype () == Token::TTCLOSEBLOCK)
            {
                if (ignore)
                {
                    tp->putBack ();
                    return true;
                }
                return false;
            }
            if ((tp->getTokentype () > Token::TTRES__FIRST && tp->getTokentype () < Token::TTRES__LAST) ||
                tp->getTokentype () == Token::TTEND
            )
            {
                tp->putBack ();
                if (ignore)
                    return true;

                runtime_error ("End of block missed");
                return false;
            }
            // ≈сли допустимо рекурсивное включение структур, то этот блок нужно переписать
            if ((tp->getTokentype () <= Token::TTPAR__FIRST && tp->getTokentype () >= Token::TTPAR__LAST) || bToBeIgnored)
            {
                bToBeIgnored = false;
                runtime_error ("Unsupported resource parameter");
                do
                {
                    tp->getToken ();
                }
                while (
                    (tp->getTokentype () <= Token::TTPAR__FIRST || tp->getTokentype () >= Token::TTPAR__LAST) &&
                    (tp->getTokentype () <= Token::TTRES__FIRST || tp->getTokentype () >= Token::TTRES__LAST) &&
                    tp->getTokentype () != Token::TTCLOSEBLOCK && tp->getTokentype () != Token::TTEND
                );
                tp->putBack ();
            }
            else
            {
                if (ignore)
                {
                    tp->putBack ();
                }
                return true;
            }
        }
    }


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

        if (!script)
        {
            runtime_error ("Loading script file " + std::string (path) + " failed");
            return false;
        }

        SemanticsDescription desc;
        desc.keytable = keytable;
        desc.end_of_file = Token::TTEND;
        desc.number = Token::TTNUMBER;
        desc.string = Token::TTSTRING;

        TextParser tp (script, desc);

        for (;;)
        {
            tp.getToken ();
            if (tp.getTokentype () == Token::TTEND)
            {
                break;
            }
            else if (tp.getTokentype () == Token::TTRES_INCLUDE)
            {
                tp.getToken ();
                if (!parse_script (rm, tp.tknString ()))
                    runtime_error ("Including script named " + std::string(tp.tknString ()) + " failed!");
            }

            else if (tp.getTokentype () > Token::TTRES__FIRST && tp.getTokentype () < Token::TTRES__LAST)
            {
                try
                {
                    Resource restype (Resource (tp.getTokentype () - Token::TTRES__FIRST - 1));

                    tp.getToken ();
                    char name[256] = { 0 };
                    std::strcpy (name, tp.tknString ());

                    tp.getToken ();

                    char basename[256] = { 0 };
                    if (tp.getTokentype () == Token::TTBASED)
                    {
                        tp.getToken ();
                        std::strcpy (basename, tp.tknString ());
                        tp.getToken ();
                    }

                    if (tp.getTokentype () == Token::TTOPENBLOCK)
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
                        debug_message ("Illegal resource syntax in line " + std::to_string (tp.getLine ()) + ". '{' expected.");
                        while ((tp.getTokentype () <= Token::TTRES__FIRST || tp.getTokentype () >= Token::TTRES__LAST) && tp.getTokentype () != Token::TTEND)
                        {
                            tp.getToken ();
                        }
                        tp.putBack ();
                    }
                }
                catch (RepeateException)
                {
                    while ((tp.getTokentype () <= Token::TTRES__FIRST || tp.getTokentype () >= Token::TTRES__LAST) && tp.getTokentype () != Token::TTEND)
                    {
                        tp.getToken ();
                    }
                    tp.putBack ();
                    continue;
                }
            }
            else
            {
                debug_message ("Unrecognized resource specificator in line " + std::to_string (tp.getLine ()) + ".");
                while ((tp.getTokentype () <= Token::TTRES__FIRST || tp.getTokentype () >= Token::TTRES__LAST) && tp.getTokentype () != Token::TTEND)
                {
                    tp.getToken ();
                }
                tp.putBack ();
            }
        }

        delete[] script;

        return true;
    }


    void ResourceParser::parse_font (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        std::shared_ptr<sf::Font> font (std::make_shared<sf::Font> ());

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                font->loadFromFile (tp->tknString ());
            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }

        rm->addFont (name, font);
    }

    void ResourceParser::parse_image (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {
        std::shared_ptr<sf::Image> image (std::make_shared<sf::Image> ());

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                image->loadFromFile (tp->tknString ());
            default:
                scriptSkipToNextParameter (tp, true);
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

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_RECT:
                tp->getToken ();
                tp->getToken ();
                rect.left = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                rect.top = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                rect.width = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                rect.height = tp->tknInt ();
                break;
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                std::strcpy (path, tp->tknString ());
                break;

            default:
                scriptSkipToNextParameter (tp, true);
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

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_RECT:
                tp->getToken ();
                tp->getToken ();
                sprite.rect.left = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                sprite.rect.top = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                sprite.rect.width = tp->tknInt ();
                tp->getToken ();
                tp->getToken ();
                sprite.rect.height = tp->tknInt ();
                break;
            case Token::TTPAR_TEXTURE:
                tp->getToken ();
                tp->getToken ();
                std::strcpy (path, tp->tknString ());
                break;
            case Token::TTPAR_HOTSPOT:
                tp->getToken ();
                tp->getToken ();
                sprite.hotspot.x = tp->tknFloat ();
                tp->getToken ();
                tp->getToken ();
                sprite.hotspot.y = tp->tknFloat ();
                break;

            default:
                scriptSkipToNextParameter (tp, true);
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

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_TEXTURE:
                tp->getToken ();
                tp->getToken ();
                if (!animation.texture->loadFromFile (tp->tknString ()))
                    debug_message ("Animation wasn't loaded");
                break;

            case Token::TTPAR_HOTSPOT:
                tp->getToken ();
                tp->getToken ();
                animation.hotspot.x = tp->tknFloat ();
                tp->getToken ();
                tp->getToken ();
                animation.hotspot.y = tp->tknFloat ();
                break;

            case Token::TTPAR_FRAMES:
                if (true)
                {
                    tp->getToken ();
                    tp->getToken ();
                    animation.frames = tp->tknInt ();
                    break;
                }

            case Token::TTPAR_ROWS:
                if (true)
                {
                    tp->getToken ();
                    tp->getToken ();
                    animation.rows = tp->tknInt ();
                    break;
                }

            case Token::TTPAR_COLUMNS:
                if (true)
                {
                    tp->getToken ();
                    tp->getToken ();
                    animation.cols = tp->tknInt ();
                    break;
                }

            case Token::TTPAR_FPS:
                if (true)
                {
                    tp->getToken ();
                    tp->getToken ();
                    animation.fps = tp->tknFloat ();
                    break;
                }

            case Token::TTPAR_START:
                if (true)
                {
                    tp->getToken ();
                    tp->getToken ();
                    animation.start = tp->tknInt ();
                    break;
                }

            case Token::TTPAR_MODE:
                if (true)
                {
                    int mode (Animation::FWD | Animation::LOOP);
                    for (;;)
                    {
                        tp->getToken ();
                        if (tp->getTokentype () != Token::TTEQUALS && tp->getTokentype () != Token::TTSEPARATOR)
                        {
                            tp->putBack ();
                            break;
                        }

                        switch (tp->getToken ())
                        {
                        case Token::TTCON_FORWARD:
                            mode &= ~Animation::REV;
                            break;

                        case Token::TTCON_REVERSE:
                            mode |= Animation::REV;
                            break;

                        case Token::TTCON_NOPINGPONG:
                            mode &= ~Animation::PINGPONG;
                            break;

                        case Token::TTCON_PINGPONG:
                            mode |= Animation::PINGPONG;
                            break;

                        case Token::TTCON_NOLOOP:
                            mode &= ~Animation::LOOP;
                            break;

                        case Token::TTCON_LOOP:
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
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }

        rm->addAnimation (name, animation);
    }


    void ResourceParser::parse_file_resource (ResourceLoader* rm, TextParser* tp, const char *name, const char* basename)
    {
        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                rm->addFile (name, std::make_shared<File> (tp->tknString ()));
                break;

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }
    }

    void ResourceParser::parse_effect (ResourceLoader * rm, TextParser * tp, const char * name, const char * basename)
    {
        char path[256] = { 0 };

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                std::strcpy (path, tp->tknString ());
                break;

            default:
                scriptSkipToNextParameter (tp, true);
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

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {
            case Token::TTPAR_FILENAME:
                tp->getToken ();
                tp->getToken ();
                std::strcpy (path, tp->tknString ());
                break;

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }

        std::shared_ptr<sf::Music> music (std::make_shared<sf::Music> ());
        if (!music->openFromFile (path))
            debug_message ("Music wasn't loaded");
    }

    void ResourceParser::parse_target (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }
    }

    void ResourceParser::parse_particle (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }
    }

    void ResourceParser::parse_distort (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }
    }

    void ResourceParser::parse_string_table (ResourceLoader* rm, TextParser* tp, const char* name, const char* basename)
    {

        while (scriptSkipToNextParameter (tp, false))
        {
            switch (tp->getTokentype ())
            {

            default:
                scriptSkipToNextParameter (tp, true);
                break;
            }
        }
    }


}