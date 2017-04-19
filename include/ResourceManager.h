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


#pragma once

#include "AnimationDesc.h"
#include "SpriteDesc.h"
#include "ParticleSystem.h"
#include "DistortionMesh.h"
#include "StringTable.h"

#include <unordered_map>
#include <list>
#include <string>
#include <memory>

#include <SFML/Graphics/Rect.hpp>



namespace sf
{
    class Font;
    class Image;
    class Texture;
    class Sprite;
    class Sound;
    class SoundBuffer;
    class Music;
}



namespace sfge
{


    using sf::Image;
    using sf::Texture;
    using sf::Sprite;
    using sf::Font;
    using sf::Sound;
    using sf::SoundBuffer;
    using sf::Music;


    class Animation;
    class File;


    /////////////////////////////////////////////////////////////////////
    /// ResourceManager - class for control resources
    ///
    /// ResourceManager can contain all resources of game engine and
    /// another resources. It delete them in destructor.
    /// Some types of resources currently are not implemented.
    /////////////////////////////////////////////////////////////////////
    class ResourceManager
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// constructor
        ///
        /// Create empty resource manager.
        ///
        /// @param use_default_font use default font if custom font fails to load.
        ///////////////////////////////////////////////////////////////////// 
        explicit ResourceManager (bool use_default_font = true);

        /////////////////////////////////////////////////////////////////////
        /// clear - remove all resources from manager
        /////////////////////////////////////////////////////////////////////
        void clear ();

        bool loadScript (const std::string& path);


        /////////////////////////////////////////////////////////////////////
        /// findXXXXXX - find resource
        ///
        /// Resource will be returned if it is already loaded.
        ///
        /// @param name of resource.
        ///
        /// @return pointer to resource or empty pointer if search failed
        ///////////////////////////////////////////////////////////////////// 

        std::shared_ptr<const Font> findFont (const std::string& name);

        std::shared_ptr<const Image> findImage (const std::string& name);

        std::shared_ptr<const Texture> findTexture (const std::string& name);

        std::unique_ptr<Sprite> findSprite (const std::string& name);

        std::unique_ptr<Animation> findAnimation (const std::string& name);

        std::shared_ptr<File> findFile (const std::string& name);

        std::shared_ptr<Sound> findSound (const std::string& name);

        std::shared_ptr<Music> findMusic (const std::string& name);

        std::shared_ptr<ParticleSystem> findParticle (const std::string& name);

        std::shared_ptr<DistortionMesh> findDistortion (const std::string& name);

        std::shared_ptr<StringTable> findStringTable (const std::string& name);


        /////////////////////////////////////////////////////////////////////
        /// getXXXXXX - find or load resource
        /// 
        /// Resource will be loaded if not done so before.
        /// 
        /// @param name of resource.
        /// @param description of resource (if it is necessary).
        /// 
        /// @return pointer to resource or empty pointer if loading failed
        /////////////////////////////////////////////////////////////////////

        std::shared_ptr<const Font> getFont (const std::string& name);

        std::shared_ptr<const Image> getImage (const std::string& name);

        std::shared_ptr<const Texture> getTexture (const std::string& name, sf::IntRect area = sf::IntRect ());

        std::unique_ptr<Sprite> getSprite (const std::string& name, SpriteDesc = SpriteDesc ());

        std::unique_ptr<Animation> getAnimation (const std::string& name, AnimationDesc = AnimationDesc ());

        std::shared_ptr<File> getFile (const std::string& name);

        std::shared_ptr<Sound> getSound (const std::string& name);

        std::shared_ptr<Music> getMusic (std::string& name);

        std::shared_ptr<ParticleSystem> getParticle (std::string& name);

        std::shared_ptr<DistortionMesh> getDistortion (std::string& name);

        std::shared_ptr<StringTable> getStringTable (std::string& name);


        /////////////////////////////////////////////////////////////////////
        /// addXXXXXX - add resource
        /// 
        /// A resource with the same name will be replaced.
        /// 
        /// @param name - name path to resource
        /// @param resource to add
        /////////////////////////////////////////////////////////////////////

        void addFont (const std::string& name, std::shared_ptr<const Font>);

        void addImage (const std::string& name, std::shared_ptr<const Image>);

        void addTexture (const std::string& name, std::shared_ptr<const Texture>);

        void addSprite (const std::string& name, const SpriteDesc&);

        void addAnimation (const std::string& name, const AnimationDesc&);

        void addFile (const std::string& name, std::shared_ptr<File>);

        void addSound (const std::string& name, std::shared_ptr<SoundBuffer>);

        void addMusic (const std::string& name, std::shared_ptr<Music>);

        void addParticle (const std::string& name, std::shared_ptr<ParticleSystem>);

        void addDistortion (const std::string& name, std::shared_ptr<DistortionMesh>);

        void addStringTable (const std::string& name, std::shared_ptr<StringTable>);


        /////////////////////////////////////////////////////////////////////
        /// setDefaultFont - set font to use as default
        /// 
        /// @param font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setDefaultFont (std::shared_ptr<const sf::Font> font);


    protected:
        std::list<std::string> m_scripts;

        std::unordered_map<std::string, std::shared_ptr<const Font>>  m_fonts;
        std::unordered_map<std::string, std::shared_ptr<const Image>> m_images;
        std::unordered_map<std::string, std::shared_ptr<const Texture>> m_textures;
        std::unordered_map<std::string, const SpriteDesc> m_sprites;
        std::unordered_map<std::string, const AnimationDesc> m_animations;
        std::unordered_map<std::string, std::shared_ptr<File>> m_files;
        std::unordered_map<std::string, std::shared_ptr<SoundBuffer>> m_sounds;
        std::unordered_map<std::string, std::shared_ptr<Music>> m_musics;
        std::unordered_map<std::string, std::shared_ptr<ParticleSystem>> m_particles;
        std::unordered_map<std::string, std::shared_ptr<DistortionMesh>> m_distortions;
        std::unordered_map<std::string, std::shared_ptr<StringTable>> m_string_tables;

        bool m_use_default_font;
    };


}