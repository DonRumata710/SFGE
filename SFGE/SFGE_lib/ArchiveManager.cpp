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


#include "ArchiveManager.h"
#include "Err.h"

#include <unzip.h>

#include <memory>
#include <sstream>
#include <vector>


using namespace sfge;


class ZipEntry
{
public:
    ZipEntry (unzFile& arch, const std::string& path, const std::string& password) : archive (arch)
    {
        int err = unzLocateFile (archive, path.c_str (), NULL);
        if (err != UNZ_OK)
        {
            std::stringstream str;
            str << "Error " << err << " opening internal file '" << path << "' in zip";
            runtime_error (str.str ());
            return;
        }

        unz_file_info64 file_info = { 0 };
        char filename_inzip[256] = { 0 };

        err = unzGetCurrentFileInfo64 (archive, &file_info, filename_inzip, sizeof (filename_inzip), NULL, 0, NULL, 0);
        if (UNZ_OK != err)
        {
            std::stringstream str;
            str << "Error " << err << " opening internal file '" << path << "' in zip";
            runtime_error (str.str ());
            return;
        }

        name = filename_inzip;
        compressedSize = file_info.compressed_size;
        uncompressedSize = file_info.uncompressed_size;
        dosdate = file_info.dos_date;

        err = unzOpenCurrentFilePassword (archive, password.c_str ());
        if (err != UNZ_OK)
        {
            std::stringstream str;
            str << "Error " << err << " opening internal file '" << name << "' in zip";
            runtime_error (str.str ());
            return;
        }
    }

    ~ZipEntry ()
    {
        if (!valid ())
        {
            debug_message ("Close invalid inner zip file");
            return;
        }

        int err = unzCloseCurrentFile (archive);
        if (err != UNZ_OK)
        {
            std::stringstream str;
            str << "Error " << err << " opening internal file '"
                << name << "' in zip";

            runtime_error (str.str ());
        }
    }

    bool valid () { return !name.empty (); }

    uint64_t getSize () const
    {
        return uncompressedSize;
    }

private:
    unzFile& archive;

    std::string name;
    uint64_t compressedSize = -1;
    uint64_t uncompressedSize = -1;
    uint32_t dosdate = -1;
};



struct ArchiveManager::Implement
{
    unzFile archive;
    std::unique_ptr<ZipEntry> entry;
    std::string password;


    const Int64 WRITEBUFFERSIZE = 8192;


    Implement (const std::string& _archive, const std::string& psw) : password (psw)
    {
        zlib_filefunc64_def ffunc;
        fill_fopen64_filefunc (&ffunc);
        archive = unzOpen2_64 (_archive.c_str (), &ffunc);

        if (!archive)
            runtime_error ("Archive \"" + _archive + "\" wasn't opened");
    }

    bool open (const std::string& path)
    {
        entry.reset (new ZipEntry (archive, path, password));

        if (!entry || !entry->valid ())
            return false;

        return true;
    }

    Int64 read (void* data, Int64 size)
    {
        if (!entry || !entry->valid ())
        {
            runtime_error ("No file has been opened");
            return -1;
        }

        int ret (unzReadCurrentFile (archive, data, size));
        
        return ret;
    }

    Int64 seek (Int64 _position)
    {
        if (!entry || !entry->valid ())
        {
            runtime_error ("No file has been opened");
            return -1;
        }

        unzSetOffset64 (archive, _position);

        return unzGetOffset64 (archive);
    }

    Int64 tell ()
    {
        if (!entry || !entry->valid ())
        {
            runtime_error ("No file has been opened");
            return -1;
        }

        return unzGetOffset64 (archive);
    }

    Int64 getSize ()
    {
        if (!entry || !entry->valid ())
        {
            runtime_error ("No file has been opened");
            return -1;
        }

        return entry->getSize ();
    }
};



ArchiveManager::ArchiveManager (const std::string& archive, const std::string& password) :
    m_impl (new Implement (archive, password))
{}

ArchiveManager::~ArchiveManager ()
{
    if (m_impl)
        delete m_impl;

    m_impl = nullptr;
}

bool ArchiveManager::open (const std::string& path)
{
    return m_impl->open (path);
}

Int64 ArchiveManager::read (void* data, Int64 size)
{
    return m_impl->read (data, size);
}

Int64 ArchiveManager::seek (Int64 position)
{
    return m_impl->seek (position);
}

Int64 ArchiveManager::tell ()
{
    return m_impl->tell ();
}

Int64 ArchiveManager::getSize ()
{
    return m_impl->getSize ();
}
