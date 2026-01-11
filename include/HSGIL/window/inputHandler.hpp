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

//#include <HSGIL/system/dstr/map.hpp>
#include <map>
#define Map std::map

#include <HSGIL/math/vec2.hpp>

#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/inputBindings.hpp>

namespace gil
{
/**
 * @brief InputHandler class that handles input
 * 
 */
class InputHandler
{
	friend class RenderingWindow;
public:
	HSGIL_API InputHandler();
	HSGIL_API virtual ~InputHandler();

	HSGIL_API bool onKeyDown(InputCode key);
	HSGIL_API bool onKeyUp(InputCode key);
	HSGIL_API bool onKeyReleased(InputCode key);
	HSGIL_API bool onKeyTriggered(InputCode key);

	HSGIL_API bool onClick(InputCode button);
	HSGIL_API bool onRelease(InputCode button);
	HSGIL_API bool onButtonDown(InputCode button);
	HSGIL_API bool onButtonUp(InputCode button);

	HSGIL_API Vec2i getMousePos();

private:
	struct KeyInfo
	{
		InputEvent event;
		int32 time;
	};

	struct MouseInfo
	{
		InputEvent event;
		int32 time;
	};

private:
	void tick();

	void initKey(InputCode key);
	void initButton(InputCode button);

	void updateKeyEvent(InputCode key, InputEvent event);
	void updateMouseEvent(InputCode button, InputEvent event);
	void updateMousePosition(Vec2i position);

private:
	Vec2i m_mousePos;
	Map<InputCode, KeyInfo>* m_keys;
	Map<InputCode, MouseInfo>* m_mouseButtons;

	int32 m_currentTime;
};

} // namespace gil
