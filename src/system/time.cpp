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

#include <HSGIL/system/time.hpp>

namespace gil
{
Time::Time()
    : m_timeCount {0}
{
}

Time::Time(microT t_timeCount)
    : m_timeCount {t_timeCount}
{
}

Time::~Time()
{
}

secT Time::asSeconds() const
{
    return static_cast<secT>(m_timeCount) / 1000000.0f;
}

milliT Time::asMilliseconds() const
{
    return static_cast<milliT>(m_timeCount / 1000);
}

microT Time::asMicroseconds() const
{
    return m_timeCount;
}

microT Time::getRawTimeCount() const
{
    return m_timeCount;
}

Time seconds(secT seconds)
{
    return Time {static_cast<microT>(seconds * 1000000.0f)};
}

Time milliseconds(milliT milliseconds)
{
    return Time {static_cast<microT>(milliseconds * 1000)};
}

Time microseconds(microT microseconds)
{
    return Time {microseconds};
}

Time rawTimeBuilder(microT microseconds)
{
    return Time {microseconds};
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() == rhs.getRawTimeCount();
}

bool operator!=(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() != rhs.getRawTimeCount();
}

bool operator<(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() < rhs.getRawTimeCount();
}

bool operator>(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() > rhs.getRawTimeCount();
}

bool operator<=(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() <= rhs.getRawTimeCount();
}

bool operator>=(const Time& lhs, const Time& rhs)
{
    return lhs.getRawTimeCount() >= rhs.getRawTimeCount();
}

Time operator+(const Time& lhs, const Time& rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() + rhs.getRawTimeCount());
}

Time operator-(const Time& lhs, const Time& rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() - rhs.getRawTimeCount());
}

Time operator*(const Time& lhs, const Time& rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() * rhs.getRawTimeCount());
}

Time operator*(const Time& lhs, float rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() * static_cast<microT>(rhs));
}

Time operator*(const Time& lhs, int64 rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() * static_cast<microT>(rhs));
}

Time operator*(float lhs, const Time& rhs)
{
    return rawTimeBuilder(static_cast<microT>(lhs) * rhs.getRawTimeCount());
}

Time operator*(int64 lhs, const Time& rhs)
{
    return rawTimeBuilder(static_cast<microT>(lhs) * rhs.getRawTimeCount());
}

Time operator/(const Time& lhs, const Time& rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() / rhs.getRawTimeCount());
}

Time operator/(const Time& lhs, float rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() / static_cast<microT>(rhs));
}

Time operator/(const Time& lhs, int64 rhs)
{
    return rawTimeBuilder(lhs.getRawTimeCount() / static_cast<microT>(rhs));
}

Time operator/(float lhs, const Time& rhs)
{
    return rawTimeBuilder(static_cast<microT>(lhs) / rhs.getRawTimeCount());
}

Time operator/(int64 lhs, const Time& rhs)
{
    return rawTimeBuilder(static_cast<microT>(lhs) / rhs.getRawTimeCount());
}

Time& operator+=(Time& lhs, const Time& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

Time& operator-=(Time& lhs, const Time& rhs)
{
    lhs = lhs - rhs;
    return lhs;
}

Time& operator*=(Time& lhs, const Time& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

Time& operator*=(Time& lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

Time& operator*=(Time& lhs, int64 rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

Time& operator/=(Time& lhs, const Time& rhs)
{
    lhs = lhs / rhs;
    return lhs;
}

Time& operator/=(Time& lhs, float rhs)
{
    lhs = lhs / rhs;
    return lhs;
}

Time& operator/=(Time& lhs, int64 rhs)
{
    lhs = lhs / rhs;
    return lhs;
}

} // namespace gil
