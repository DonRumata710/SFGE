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


#include "Config.h"
#include "AnimationDesc.h"
#include "SpriteDesc.h"
#include "ParticleSystem.h"
#include "DistortionMesh.h"
#include "StringTable.h"
#include "ResourceInputStream.h"

#include <SFML/Graphics/Rect.hpp>

#include <unordered_map>
#include <list>
#include <string>
#include <memory>



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
    /// another resources. It delete them in destructor. Some types of
    /// resources currently are not implemented. Also it is possible to
    /// create a subclass with providing new resources.
    /////////////////////////////////////////////////////////////////////
    class ResourceManager
    {
    public:
        static const std::string DEFAULT;   /// default name for resource manager or resource
        
        /////////////////////////////////////////////////////////////////////
        /// constructor
        ///
        /// Create empty resource manager. If you create resource manager
        /// without create function it will not be available from get
        /// function.
        ///
        /// @param is_default - if true this manager will be used for GUI elements
        ///////////////////////////////////////////////////////////////////// 
        ResourceManager ();


        /////////////////////////////////////////////////////////////////////
        /// setResourceStream - set new place which contains resources
        ///
        /// @param stream - stream of resources
        /////////////////////////////////////////////////////////////////////
        void setResourceStream (std::unique_ptr<iResourceInputStream>& stream);

        /////////////////////////////////////////////////////////////////////
        /// loadScript - loading resources from script
        ///
        /// @param path - path to the script
        ///
        /// @returm - true if resources loaded successfuly, false otherwise
        /////////////////////////////////////////////////////////////////////
        bool loadScript (const std::string& path);

        /////////////////////////////////////////////////////////////////////
        /// setDefaultFont - set font to use as default
        /// 
        /// @param font - pointer to font
        /////////////////////////////////////////////////////////////////////
        void setDefaultFont (std::shared_ptr<const sf::Font> font);

        /////////////////////////////////////////////////////////////////////
        /// useDefaultFont - set use default font or not
        ///
        /// @param use_default_font - use default font if custom font fails to load
        ///////////////////////////////////////////////////////////////////// 
        void useDefaultFont (bool use = true);

        /////////////////////////////////////////////////////////////////////
        /// clear - remove all resources from manager
        /////////////////////////////////////////////////////////////////////
        void clear ();


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
        /// typedefs of resources lists
        /////////////////////////////////////////////////////////////////////

        typedef std::unordered_map<std::string, std::shared_ptr<const Font>>  FontList;
        typedef std::unordered_map<std::string, std::shared_ptr<const Image>> ImageList;
        typedef std::unordered_map<std::string, std::shared_ptr<const Texture>> TextureList;
        typedef std::unordered_map<std::string, const SpriteDesc> SpriteList;
        typedef std::unordered_map<std::string, const AnimationDesc> AnimationList;
        typedef std::unordered_map<std::string, std::shared_ptr<File>> FileList;
        typedef std::unordered_map<std::string, std::shared_ptr<SoundBuffer>> SoundList;
        typedef std::unordered_map<std::string, std::shared_ptr<Music>> MusicList;
        typedef std::unordered_map<std::string, std::shared_ptr<ParticleSystem>> ParticleSystemList;
        typedef std::unordered_map<std::string, std::shared_ptr<DistortionMesh>> DistortionMeshList;
        typedef std::unordered_map<std::string, std::shared_ptr<StringTable>> StringTableList;


        /////////////////////////////////////////////////////////////////////
        /// getXXXXXX - get list of resources
        /// 
        /// @param name - name path to resource
        /////////////////////////////////////////////////////////////////////

        const FontList& getFontList () const;

        const ImageList& getImageList () const;

        const TextureList& getTextureList () const;

        const SpriteList& getSpriteList () const;

        const AnimationList& getAnimationList () const;

        const FileList& getFileList () const;

        const SoundList& getSoundList () const;

        const MusicList& getMusicList () const;

        const ParticleSystemList& getParticleList () const;

        const DistortionMeshList& getDistortionList () const;

        const StringTableList& getStringTableList () const;


    protected:
        std::unique_ptr<iResourceInputStream> m_stream;

        std::list<std::string> m_scripts;

        FontList           m_fonts;
        ImageList          m_images;
        TextureList        m_textures;
        SpriteList         m_sprites;
        AnimationList      m_animations;
        FileList           m_files;
        SoundList          m_sounds;
        MusicList          m_musics;
        ParticleSystemList m_particles;
        DistortionMeshList m_distortions;
        StringTableList    m_string_tables;

        bool m_use_default_font = true;

        static std::unordered_map<std::string, std::weak_ptr<ResourceManager>> m_managers;
    };


}