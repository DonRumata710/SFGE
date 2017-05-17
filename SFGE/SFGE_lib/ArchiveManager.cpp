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

#include <memory>
#include <sstream>
#include <vector>


using namespace sfge;
using namespace minizip;



class ZipEntry
{
public:
    ZipEntry (const std::string& name, unsigned long long int compressed_size, unsigned long long int uncompressed_size, unsigned long dosdate)
        : name (name), compressedSize (compressed_size), uncompressedSize (uncompressed_size), dosdate (dosdate)
    {}

    bool valid () { return !name.empty (); }

    std::string name, timestamp;
    unsigned long long int compressedSize, uncompressedSize;
    unsigned long dosdate;
};



struct ArchiveManager::Implement
{
    minizip::unzFile archive;
    std::unique_ptr<ZipEntry> entry;


    const Int64 WRITEBUFFERSIZE = 8192;


    Implement (const std::string& _archive)
    {
        zlib_filefunc64_def ffunc;
        fill_fopen64_filefunc (&ffunc);
        archive = unzOpen2_64 (_archive.c_str (), &ffunc);

        if (!archive)
            runtime_error ("File \"" + _archive + "\" wasn't opened");
    }

    bool open (const std::string& path, const std::string& password)
    {
        if (locateEntry (path))
        {
            entry = currentEntryInfo ();

            if (!entry->valid ())
                return false;

            int err (unzOpenCurrentFilePassword (archive, password.c_str ()));
            if (err != UNZ_OK)
            {
                std::stringstream str;
                str << "Error " << err << " opening internal file '" << entry->name << "' in zip";
                runtime_error (str.str ());
                return false;
            }

            return true;
        }

        return false;
    }

    bool locateEntry (const std::string& name)
    {
        return unzLocateFile (archive, name.c_str (), NULL) == UNZ_OK;
    }

    std::unique_ptr<ZipEntry> currentEntryInfo ()
    {
        unz_file_info64 file_info = { 0 };
        char filename_inzip[256] = { 0 };

        int err = unzGetCurrentFileInfo64 (archive, &file_info, filename_inzip, sizeof (filename_inzip), NULL, 0, NULL, 0);
        if (UNZ_OK != err)
        {
            runtime_error ("Error, couln't get the current entry info");
            return nullptr;
        }

        return std::make_unique<ZipEntry> (std::string (filename_inzip), file_info.compressed_size, file_info.uncompressed_size, file_info.dos_date);
    }

    Int64 read (void* data, Int64 size)
    {
        int ret (unzReadCurrentFile (archive, data, size));
        
        int err = unzCloseCurrentFile (archive);
        if (err != UNZ_OK)
        {
            std::stringstream str;
            str << "Error " << err << " opening internal file '"
                << entry->name << "' in zip";

            runtime_error (str.str ());
        }

        return ret;
    }

    Int64 seek (Int64 _position)
    {
        unzSetOffset64 (archive, _position);

        return unzGetOffset64 (archive);
    }

    Int64 tell ()
    {
        return unzGetOffset64 (archive);
    }

    Int64 getSize ()
    {
        return entry->uncompressedSize;
    }
};



ArchiveManager::ArchiveManager (const std::string& archive) : m_impl (new Implement (archive))
{}

ArchiveManager::~ArchiveManager ()
{
    if (m_impl)
        delete m_impl;

    m_impl = nullptr;
}

bool ArchiveManager::open (const std::string& path, const std::string& password)
{
    return m_impl->open (path, password);
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
