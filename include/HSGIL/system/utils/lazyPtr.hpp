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

namespace gil
{
template <typename T>
class LazyPtr
{
public:
	LazyPtr(LazyPtr<T>&& o);
	LazyPtr();
	~LazyPtr();

	template <typename... TArgs>
	void init(TArgs... args);

	T& operator*();
	T* operator->();
	bool operator==(const LazyPtr<T>& o);
	bool operator!=(const LazyPtr<T>& o);
	bool operator==(const std::nullptr_t nullPtr);
	bool operator!=(const std::nullptr_t nullPtr);
	operator T*();

private:
	T* m_data;

	LazyPtr(const LazyPtr<T>& o) = delete;
};

} // namespace gil

#include "lazyPtr.inl"
