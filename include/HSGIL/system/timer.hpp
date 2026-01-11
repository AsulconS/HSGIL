/**
 * HSGIL - Handy Scalable Graphics Integration Library
 * Copyright (c) 2026 Adrian Bedregal
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include <HSGIL/core/minimal.hpp>

#include <HSGIL/system/time.hpp>

namespace gil
{
/**
 * @brief Timer Class that measures the time intervals, calculate Delta Time and other time stuff
 * 
 */
class Timer
{
public:
	/**
	 * @brief Construct a new Timer object
	 * 
	 */
	HSGIL_API explicit Timer(const bool t_debugMode = false, const float t_period = 1.0f);
	/**
	 * @brief Destroy the Timer object
	 * 
	 */
	HSGIL_API virtual ~Timer();

	/**
	 * @brief Update the timer
	 * 
	 */
	HSGIL_API void tick();
	/**
	 * @brief Restart the timer
	 * 
	 */
	HSGIL_API void restart();

	/**
	 * @brief Get the Delta Time
	 * 
	 * @return float 
	 */
	HSGIL_API secT getDeltaTime();
	/**
	 * @brief Get the Total Frame count
	 * 
	 * @return uint32 
	 */
	HSGIL_API uint32 getTotalFrames();
	/**
	 * @brief Get the Frames Per Second count
	 * 
	 * @return uint32 
	 */
	HSGIL_API uint32 getFramesPerSecond();

private:
	secT procDeltaTime();
	secT procTotalElapsedTime();
	secT procCurrentElapsedTime();

private:
	microT m_start;
	microT m_currentStart;
	microT m_lastTime;

	secT m_deltaTime;
	secT m_currentTime;
	uint32 m_totalFrames;
	uint32 m_framesPerSecond;

	secT m_period;
	bool m_debugMode;
};

} // namespace gil
