/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2021 Adrian Bedregal                                      *
 *                                                                              *
 * This software is provided 'as-is', without any express or implied            *
 * warranty. In no event will the authors be held liable for any damages        *
 * arising from the use of this software.                                       *
 *                                                                              *
 * Permission is granted to anyone to use this software for any purpose,        *
 * including commercial applications, and to alter it and redistribute it       *
 * freely, subject to the following restrictions:                               *
 *                                                                              *
 * 1. The origin of this software must not be misrepresented; you must not      *
 *    claim that you wrote the original software. If you use this software      *
 *    in a product, an acknowledgment in the product documentation would be     *
 *    appreciated but is not required.                                          *
 * 2. Altered source versions must be plainly marked as such, and must not be   *
 *    misrepresented as being the original software.                            *
 * 3. This notice may not be removed or altered from any source distribution.   *
 *                                                                              *
 ********************************************************************************/

#include <HSGIL/window/wmLazyPtr.hpp>
#include <HSGIL/window/windowManager.hpp>

namespace gil
{
WMLazyPtr::WMLazyPtr()
    : m_wm {nullptr}
{
}

WMLazyPtr::~WMLazyPtr()
{
    if(m_wm != nullptr)
    {
        delete m_wm;
    }
}

void WMLazyPtr::init(const uint32 index)
{
    if(m_wm == nullptr)
    {
        m_wm = new WindowManager(index);
    }
}

WindowManager& WMLazyPtr::operator*()
{
    return *m_wm;
}

WindowManager* WMLazyPtr::operator->()
{
    return m_wm;
}

bool WMLazyPtr::operator==(const WMLazyPtr& o)
{
    return this->m_wm == o.m_wm;
}

bool WMLazyPtr::operator!=(const WMLazyPtr& o)
{
    return this->m_wm != o.m_wm;
}

bool WMLazyPtr::operator==(const std::nullptr_t nullPtr)
{
    return this->m_wm == nullPtr;
}

bool WMLazyPtr::operator!=(const std::nullptr_t nullPtr)
{
    return this->m_wm != nullPtr;
}

WMLazyPtr::operator WindowManager*()
{
    return m_wm;
}

} // namespace gil
