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
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
/////////////////////////////////////////////////////////////////////


#include "GEDevice.h"
#include "Err.h"


using namespace sfge;


const std::string GEDevice::SYSTEM_RESOURCES ("system");

GEDevice* GEDevice::m_device (nullptr);


GEDevice* GEDevice::getInstance ()
{
    return m_device;
}

GEDevice::GEDevice ()
{
    if (m_device)
        critical_error ("Few game engine devices was created!", std::runtime_error);

    m_device = this;
}

GEDevice::~GEDevice ()
{
    m_device = nullptr;
}

void GEDevice::setResourceManager (std::shared_ptr<ResourceManager> resources, const std::string name)
{
    m_resource_managers[name] = resources;
}

std::shared_ptr<ResourceManager> GEDevice::getResourceManager (const std::string name)
{
    return m_resource_managers[name].lock ();
}

bool GEDevice::createWindow (
    const unsigned gui_id,
    const UString& title,
    const VideoMode& mode,
    const uint32_t style,
    const ContextSettings context
)
{
    auto manager (m_managers.find (gui_id));
    if (manager == m_managers.end ()) return false;

    m_active.insert ({ title, m_managers[gui_id].get () });
    auto window (std::make_unique<RenderWindow> (mode, title, style));
    m_managers[gui_id]->enter (window);
    return true;
}

void GEDevice::destroyWindow (const UString& str)
{
    m_active[str]->setSwitch (-1);
    m_active[str]->leave ();
}

void GEDevice::addGuiManager (unsigned id, pGUIManager& gui)
{
    m_managers.insert (std::pair<unsigned, pGUIManager> (id, nullptr));
    m_managers[id].swap (gui);
}

GUIManager* GEDevice::getGUIManager (unsigned id)
{
    return m_managers[id].get ();
}

int GEDevice::run ()
{
    try
    {
        while (!m_active.empty ())
        {
            for (auto iter = m_active.begin (); iter != m_active.end (); ++iter)
            {
                if (!iter->second->update ())
                {
                    int id (iter->second->getSwitch ());
                    if (id >= 0 && m_managers[id].get () != iter->second)
                    {
                        UString window (iter->first);
                        sfge::GUIManager* manager (iter->second);
                        m_active[window] = m_managers[id].get ();
                        m_managers[id]->enter (manager->getWindow ());
                        break;
                    }
                    else if (id == -1)
                    {
                        iter->second->getWindow ()->close ();
                        m_active.erase (iter);
                        break;
                    }
                }

                iter->second->draw ();
            }
        }
    }
    catch (const std::exception& ex)
    {
        runtime_message (ex.what ());
    }
    return 0;
}

void GEDevice::quit ()
{
    for (auto wnd : m_active)
    {
        wnd.second->setSwitch (-1);
        wnd.second->leave ();
    }
}
