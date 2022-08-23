/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2022 Adrian Bedregal                                      *
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

#include <HSGIL/system/timer.hpp>

#include <chrono>
#include <iostream>

#include "timerPlatform.hpp"

namespace gil
{
Timer::Timer(const bool t_debugMode, const float t_period)
    : m_start           {plat::getTime().getRawTimeCount()},
      m_currentStart    {plat::getTime().getRawTimeCount()},
      m_lastTime        {plat::getTime().getRawTimeCount()},
      m_deltaTime       {0.0f},
      m_currentTime     {0.0f},
      m_totalFrames     {0},
      m_framesPerSecond {0},
      m_period          {t_period},
      m_debugMode       {t_debugMode}
{
}

Timer::~Timer()
{
}

void Timer::tick()
{
    m_currentTime = procCurrentElapsedTime();
    m_deltaTime = procDeltaTime();
    ++m_framesPerSecond;
    ++m_totalFrames;
    if(m_currentTime >= m_period)
    {
        if(m_debugMode)
        {
            std::cout << m_framesPerSecond << " fps" << std::endl;
        }
        m_currentStart    = plat::getTime().getRawTimeCount();
        m_framesPerSecond = 0;
    }
}

void Timer::restart()
{
    m_lastTime = m_currentStart = m_start = plat::getTime().getRawTimeCount();
    m_framesPerSecond = m_totalFrames = 0;
}

secT Timer::getDeltaTime()
{
    return m_deltaTime;
}

uint32 Timer::getTotalFrames()
{
    return m_totalFrames;
}

uint32 Timer::getFramesPerSecond()
{
    return m_framesPerSecond;
}

secT Timer::procDeltaTime()
{
    Time currentTime {plat::getTime()};
    secT deltaTime {(currentTime - rawTimeBuilder(m_lastTime)).asSeconds()};
    m_lastTime = currentTime.getRawTimeCount();
    return deltaTime;
}

secT Timer::procTotalElapsedTime()
{
    Time currentTime {plat::getTime()};
    return (currentTime - rawTimeBuilder(m_start)).asSeconds();
}

secT Timer::procCurrentElapsedTime()
{
    Time currentTime {plat::getTime()};
    return (currentTime - rawTimeBuilder(m_currentStart)).asSeconds();
}

} // namespace gil
