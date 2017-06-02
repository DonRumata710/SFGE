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


#include "FileInputStream.h"
#include "ResourceManager.h"
#include "ResourceParser.h"
#include "ResourceLoader.h"
#include "Animation.h"
#include "File.h"
#include "Err.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <algorithm>


namespace sfge
{


    ResourceManager* ResourceManager::m_default_manager (nullptr);


    ResourceManager::ResourceManager (bool is_default) : m_stream (new FileInputStream ())
    {
        if (is_default)
            m_default_manager = this;
    }

    void ResourceManager::setResourceStream (std::unique_ptr<iResourceInputStream>& stream)
    {
        m_stream.swap (stream);
    }

    void ResourceManager::useDefaultFont (bool use)
    {
        m_use_default_font = use;
    }

    bool ResourceManager::loadScript (const std::string& path)
    {
        auto font_iter = std::find (m_scripts.begin (), m_scripts.end (), path);

        if (font_iter != m_scripts.end ())
        {
            runtime_error ("Resource script \"" + path + "\" was already read");
            return true;
        }

        m_scripts.push_back (path);

        ResourceParser rp (m_stream.get ());
        return rp.parse_script ((ResourceLoader*) this, path.c_str ());
    }

    void ResourceManager::clear ()
    {
        m_fonts.clear ();
        m_images.clear ();
        m_textures.clear ();
        m_sprites.clear ();
        m_animations.clear ();
    }


    std::shared_ptr<const sf::Font> ResourceManager::findFont (const std::string& name)
    {
        auto font_iter = m_fonts.find (name);

        if (font_iter != m_fonts.end ())
            return font_iter->second;

        return std::shared_ptr<const sf::Font> ();
    }

    std::shared_ptr<const sf::Image> ResourceManager::findImage (const std::string& name)
    {
        auto image_iter = m_images.find (name);

        if (image_iter != m_images.end ())
            return image_iter->second;

        return std::shared_ptr<const sf::Image> ();
    }

    std::shared_ptr<const sf::Texture> ResourceManager::findTexture (const std::string& name)
    {
        auto texture_iter = m_textures.find (name);

        if (texture_iter != m_textures.end ())
            return texture_iter->second;

        return std::shared_ptr<sf::Texture> ();
    }

    std::unique_ptr<sf::Sprite> ResourceManager::findSprite (const std::string& name)
    {
        auto sprite_iter = m_sprites.find (name);

        if (sprite_iter != m_sprites.end ())
        {
            std::unique_ptr<sf::Sprite> sprite (std::make_unique<sf::Sprite> (*sprite_iter->second.texture));
            sprite->setOrigin (sprite_iter->second.hotspot);
            sprite->setTextureRect (sprite_iter->second.rect);
            return sprite;
        }

        return std::make_unique<sf::Sprite> ();
    }

    std::unique_ptr<Animation> ResourceManager::findAnimation (const std::string& name)
    {
        auto animation_iter = m_animations.find (name);

        if (animation_iter != m_animations.end ())
            return std::make_unique<Animation> (animation_iter->second);

        return std::make_unique<Animation> ();
    }

    std::shared_ptr<File> ResourceManager::findFile (const std::string& name)
    {
        auto file_iter = m_files.find (name);

        if (file_iter != m_files.end ())
            return file_iter->second;

        return std::shared_ptr<File> ();
    }

    std::shared_ptr<sf::Sound> ResourceManager::findSound (const std::string& name)
    {
        auto iter = m_sounds.find (name);

        if (iter != m_sounds.end ())
        {
            std::shared_ptr<sf::Sound> sound (std::make_shared<sf::Sound> ());
            sound->setBuffer (*iter->second);
            return sound;
        }

        return std::shared_ptr<sf::Sound> ();
    }

    std::shared_ptr<sf::Music> ResourceManager::findMusic (const std::string& name)
    {
        auto iter = m_musics.find (name);

        if (iter != m_musics.end ())
            return iter->second;

        return std::shared_ptr<sf::Music> ();
    }

    std::shared_ptr<ParticleSystem> ResourceManager::findParticle (const std::string& name)
    {
        auto iter = m_particles.find (name);

        if (iter != m_particles.end ())
            return iter->second;

        return std::shared_ptr<ParticleSystem> ();
    }

    std::shared_ptr<DistortionMesh> ResourceManager::findDistortion (const std::string& name)
    {
        auto iter = m_distortions.find (name);

        if (iter != m_distortions.end ())
            return iter->second;

        return std::shared_ptr<DistortionMesh> ();
    }

    std::shared_ptr<StringTable> ResourceManager::findStringTable (const std::string& name)
    {
        auto iter = m_string_tables.find (name);

        if (iter != m_string_tables.end ())
            return iter->second;

        return std::shared_ptr<StringTable> ();
    }


    std::shared_ptr<const sf::Font> ResourceManager::getFont (const std::string& name)
    {
        auto font_iter = m_fonts.find (name);

        if (font_iter != m_fonts.end ())
        {
            return font_iter->second;
        }

        if (name == "Default")
        {
            if (m_use_default_font)
            {
                auto font = std::make_shared<sf::Font> ();
                m_fonts[name] = font;

                return font;
            }

            return std::shared_ptr<const sf::Font> ();
        }

        sf::Font* fnt (new sf::Font ());

        m_stream->open (name);
        auto file (std::make_shared<File> (m_stream.get ()));
        addFile (name, file);
        
        if(!fnt->loadFromStream (*file))
            return getFont ("Default");

        if (!fnt)
            return getFont ("Default");

        std::shared_ptr<const sf::Font> font (fnt);

        m_fonts[name] = font;
        return font;
    }

    std::shared_ptr<const sf::Image> ResourceManager::getImage (const std::string& name)
    {
        auto image_iter = m_images.find (name);

        if (image_iter != m_images.end ())
        {
            return image_iter->second;
        }

        sf::Image* img (new sf::Image ());

        m_stream->open (name);
        img->loadFromStream (*m_stream);

        if (!img)
            return std::shared_ptr<const sf::Image> ();

        std::shared_ptr<const sf::Image> image (img);

        m_images[name] = image;
        return image;
    }

    std::shared_ptr<const sf::Texture> ResourceManager::getTexture (const std::string& name, sf::IntRect area)
    {
        auto texture_iter = m_textures.find (name);

        if (texture_iter != m_textures.end ())
            return texture_iter->second;

        std::shared_ptr<sf::Texture> tex (std::make_shared<sf::Texture> ());

        m_stream->open (name);
        if (!tex->loadFromStream (*m_stream, area))
            return std::shared_ptr<sf::Texture> ();

        m_textures[name] = tex;

        return tex;
    }

    std::unique_ptr<sf::Sprite> ResourceManager::getSprite (const std::string& name, SpriteDesc desc)
    {
        auto sprite_iter = m_sprites.find (name);

        if (sprite_iter != m_sprites.end ())
        {
            std::unique_ptr<sf::Sprite> sprite (std::make_unique<sf::Sprite> ());
            sprite->setOrigin (sprite_iter->second.hotspot);
            sprite->setTexture (*sprite_iter->second.texture);
            sprite->setTextureRect (sprite_iter->second.rect);
            return sprite;
        }

        std::shared_ptr<sf::Texture> tex (std::make_shared<sf::Texture> ());

        m_stream->open (name);
        if (!tex->loadFromStream (*m_stream, desc.rect))
            return std::unique_ptr<sf::Sprite> ();

        addTexture (name, tex);

        desc.texture = tex;

        std::unique_ptr<sf::Sprite> sprite (new sf::Sprite ());
        sprite->setTexture (*tex);
        sprite->setOrigin (desc.hotspot);

        addSprite (name, desc);

        return sprite;
    }

    std::unique_ptr<Animation> ResourceManager::getAnimation (const std::string& name, AnimationDesc desc)
    {
        auto animation_iter = m_animations.find (name);

        if (animation_iter != m_animations.end ())
            return std::make_unique<Animation> (animation_iter->second);

        std::shared_ptr<sf::Texture> tex (std::make_shared<sf::Texture> ());

        m_stream->open (name);
        if (!tex->loadFromStream (*m_stream))
            return std::unique_ptr<Animation> ();

        desc.texture = tex;

        std::unique_ptr<Animation> animation (new Animation ());
        animation->setTexture (*tex, desc.rows, desc.cols, desc.frames, desc.start);

        addAnimation (name, desc);

        return animation;
    }

    std::shared_ptr<File> ResourceManager::getFile (const std::string& name)
    {
        auto file_iter = m_files.find (name);

        if (file_iter != m_files.end ())
            return file_iter->second;

        m_stream->open (name);
        return std::shared_ptr<File> (new File (m_stream.get ()));
    }

    std::shared_ptr<sf::Sound> ResourceManager::getSound (const std::string & name)
    {
        auto iter = m_sounds.find (name);

        if (iter != m_sounds.end ())
        {
            std::shared_ptr<sf::Sound> sound (std::make_shared<sf::Sound> ());
            sound->setBuffer (*iter->second);
            return sound;
        }

        sf::SoundBuffer sound_buffer;
        m_stream->open (name);
        if (!sound_buffer.loadFromStream (*m_stream))
            return std::shared_ptr<sf::Sound> ();

        std::shared_ptr<sf::Sound> sound (std::make_shared<sf::Sound> ());
        sound->setBuffer (sound_buffer);
        return sound;
    }

    std::shared_ptr<sf::Music> ResourceManager::getMusic (std::string& name)
    {
        auto iter = m_musics.find (name);

        if (iter != m_musics.end ())
            return iter->second;

        std::shared_ptr<sf::Music> music (std::make_shared<sf::Music> ());

        m_stream->open (name);
        auto file (std::make_shared<File> (m_stream.get ()));
        addFile (name, file);
        if (!music->openFromStream (*file))
            return std::shared_ptr<sf::Music> ();

        return music;
    }

    std::shared_ptr<ParticleSystem> ResourceManager::getParticle (std::string & name)
    {
        return std::shared_ptr<ParticleSystem> ();
    }

    std::shared_ptr<DistortionMesh> ResourceManager::getDistortion (std::string & name)
    {
        return std::shared_ptr<DistortionMesh> ();
    }

    std::shared_ptr<StringTable> ResourceManager::getStringTable (std::string & name)
    {
        return std::shared_ptr<StringTable> ();
    }



    void ResourceManager::addFont (const std::string& name, std::shared_ptr<const sf::Font> font)
    {
        m_fonts[name] = font;
    }

    void ResourceManager::addImage (const std::string& name, std::shared_ptr<const sf::Image> image)
    {
        m_images[name] = image;
    }

    void ResourceManager::addTexture (const std::string& name, std::shared_ptr<const sf::Texture> texture)
    {
        m_textures[name] = texture;
    }

    void ResourceManager::addSprite (const std::string& name, const SpriteDesc& sprite)
    {
        m_sprites.insert ({ name, sprite });
    }

    void ResourceManager::addAnimation (const std::string& name, const AnimationDesc& animation)
    {
        m_animations.insert ({ name, animation });
    }

    void ResourceManager::addFile (const std::string& name, std::shared_ptr<File> file)
    {
        m_files[name] = file;
    }

    void ResourceManager::addSound (const std::string& name, std::shared_ptr<sf::SoundBuffer> sound)
    {
        m_sounds[name] = sound;
    }

    void ResourceManager::addMusic (const std::string& name, std::shared_ptr<sf::Music> music)
    {
        m_musics[name] = music;
    }

    void ResourceManager::addParticle (const std::string& name, std::shared_ptr<ParticleSystem> particle)
    {
        m_particles[name] = particle;
    }

    void ResourceManager::addDistortion (const std::string& name, std::shared_ptr<DistortionMesh> distortion)
    {
        m_distortions[name] = distortion;
    }

    void ResourceManager::addStringTable (const std::string& name, std::shared_ptr<StringTable> string_table)
    {
        m_string_tables[name] = string_table;
    }


    void ResourceManager::setDefaultFont (std::shared_ptr<const sf::Font> font)
    {
        addFont ("Default", font);
    }


}