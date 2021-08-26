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

#ifndef HSGIL_TIME_HPP
#define HSGIL_TIME_HPP

#include <HSGIL/config/config.hpp>
#include <HSGIL/config/common.hpp>

namespace gil
{
/**
 * @brief Timer Class that measures the time intervals, calculate Delta Time and other time stuff
 * 
 */
class HSGIL_API Time
{
    friend HSGIL_API Time seconds(secT seconds);
    friend HSGIL_API Time milliseconds(milliT milliseconds);
    friend HSGIL_API Time microseconds(microT microseconds);
    friend HSGIL_API Time rawTimeBuilder(microT microseconds);
public:
    /**
     * @brief Construct a new Time object
     * 
     */
    Time();
    /**
     * @brief Destroy the Time object
     * 
     */
    virtual ~Time();

    /**
     * @brief Get the Time Point value as seconds
     * 
     * @return secT 
     */
    secT asSeconds() const;
    /**
     * @brief Get the Time Point value as milliseconds
     * 
     * @return milliT 
     */
    milliT asMilliseconds() const;
    /**
     * @brief Get the Time Point value as microseconds
     * 
     * @return microT 
     */
    microT asMicroseconds() const;

    /**
     * @brief Get the Raw Time Count as microseconds
     * It's equivalent to asMicroseconds function
     * 
     * @return microT 
     */
    microT getRawTimeCount() const;

private:
    /**
     * @brief Construct a new Time object explicitly
     * in order to prevent outer construction
     * 
     * @param t_timeCount 
     */
    explicit Time(microT t_timeCount);

private:
    microT m_timeCount;
};

/**
 * @brief Construct a new Time object given seconds amount
 * 
 * @param seconds 
 * @return Time 
 */
HSGIL_API Time seconds(secT seconds);
/**
 * @brief Construct a new Time object given milliseconds amount
 * 
 * @param milliseconds 
 * @return Time 
 */
HSGIL_API Time milliseconds(milliT milliseconds);
/**
 * @brief Construct a new Time object given microseconds amount
 * 
 * @param microseconds 
 * @return Time 
 */
HSGIL_API Time microseconds(microT microseconds);
/**
 * @brief Construct a new Time object given microseconds amount
 * It's equivalent to microseconds function
 * 
 * @param microseconds 
 * @return Time 
 */
HSGIL_API Time rawTimeBuilder(microT microseconds);

/**
 * @brief Compare two Time Point values
 * 
 * @param o 
 * @return true if equal
 * @return false if different
 */
bool operator==(const Time& lhs, const Time& rhs);
/**
 * @brief Compare two Time Point values
 * 
 * @param o 
 * @return true if different
 * @return false if equal
 */
bool operator!=(const Time& lhs, const Time& rhs);

/**
 * @brief Compare two Time Point values
 * 
 * @param lhs 
 * @param rhs 
 * @return true if lhs is less than rhs
 * @return false otherwise
 */
bool operator<(const Time& lhs, const Time& rhs);
/**
 * @brief Compare two Time Point values
 * 
 * @param lhs 
 * @param rhs 
 * @return true if lhs is greater than rhs
 * @return false otherwise
 */
bool operator>(const Time& lhs, const Time& rhs);
/**
 * @brief Compare two Time Point values
 * 
 * @param lhs 
 * @param rhs 
 * @return true if lhs is less or equal than rhs
 * @return false otherwise
 */
bool operator<=(const Time& lhs, const Time& rhs);
/**
 * @brief Compare two Time Point values
 * 
 * @param lhs if lhs is greater than rhs
 * @param rhs 
 * @return true if lhs is greater or equal than rhs
 * @return false otherwise
 */
bool operator>=(const Time& lhs, const Time& rhs);

/**
 * @brief Add two Time Points
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator+(const Time& lhs, const Time& rhs);
/**
 * @brief Subtract two Time Points
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator-(const Time& lhs, const Time& rhs);
/**
 * @brief Multiply two Time Points
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator*(const Time& lhs, const Time& rhs);
/**
 * @brief Multiply a Time Point by a floating point scalar
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator*(const Time& lhs, float rhs);
/**
 * @brief Multiply a Time Point by an integer scalar
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator*(const Time& lhs, int64 rhs);
/**
 * @brief Multiply a floating point scalar by a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator*(float lhs, const Time& rhs);
/**
 * @brief Multiply an integer scalar by a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator*(int64 lhs, const Time& rhs);
/**
 * @brief Divide two Time Points
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator/(const Time& lhs, const Time& rhs);
/**
 * @brief Divide a Time Point by a floating point scalar
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator/(const Time& lhs, float rhs);
/**
 * @brief Divide a Time Point by an integer scalar
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator/(const Time& lhs, int64 rhs);
/**
 * @brief Divide a floating point scalar by a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator/(float lhs, const Time& rhs);
/**
 * @brief Divide an integer scalar by a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time 
 */
Time operator/(int64 lhs, const Time& rhs);

/**
 * @brief Add a Time Point to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator+=(Time& lhs, const Time& rhs);
/**
 * @brief Subtract a Time Point to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator-=(Time& lhs, const Time& rhs);
/**
 * @brief Multiply a Time Point to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator*=(Time& lhs, const Time& rhs);
/**
 * @brief Multiply a floating point scalar to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator*=(Time& lhs, float rhs);
/**
 * @brief Multiply an integer scalar to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator*=(Time& lhs, int64 rhs);
/**
 * @brief Divide a Time Point to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator/=(Time& lhs, const Time& rhs);
/**
 * @brief Divide a floating point scalar to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator/=(Time& lhs, float rhs);
/**
 * @brief Divide an integer scalar to a Time Point
 * 
 * @param lhs 
 * @param rhs 
 * @return Time& 
 */
Time& operator/=(Time& lhs, int64 rhs);

} // namespace gil

#endif // HSGIL_TIME_HPP
