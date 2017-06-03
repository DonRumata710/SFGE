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



#include "MapSectorDesc.h"

#include <SFGE/ResourceInputStream.h>

#include <vector>


namespace sfge
{


    class TextParser;
    struct SemanticsDescription;


    class SectorLoader
    {
    public:

        /////////////////////////////////////////////////////////////////////
        /// Constructor
        ///
        /// @param stream - source for loading file
        /////////////////////////////////////////////////////////////////////
        SectorLoader (iResourceInputStream* stream);
        
        /////////////////////////////////////////////////////////////////////
        /// loadSectors - load sectors of map
        ///
        /// @param sectors - pointers to sectors which should be loaded
        /////////////////////////////////////////////////////////////////////
        void loadSectors (const std::vector<MapSectorDesc*>& sectors);

    private:
        bool loadMapSector (TextParser* tp, MapSector* sector);

        std::pair<uint32_t, std::string> loadTile (TextParser* tp, Uint32 sector_width);

    private:
        iResourceInputStream* m_stream;

    private:
        static const SemanticsDescription m_sem_desc;
    };


}