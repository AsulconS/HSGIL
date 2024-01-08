/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2024 Adrian Bedregal                                      *
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

#pragma once

#include <HSGIL/config/config.hpp>
#include <HSGIL/config/common.hpp>

#include <HSGIL/system/utility.hpp>

#define HSGIL_INITIAL_CAPACITY 4

namespace gil
{
template <typename T>
class Vector
{
public:
    /**
     * @brief Construct a new Vector object
     * 
     */
    Vector();
    /**
     * @brief Construct a new Vector object
     * 
     * @param n 
     */
    Vector(uint64 n);
    /**
     * @brief Construct a new Vector object
     * 
     * @param n 
     * @param val 
     */
    Vector(uint64 n, const T& val);

    /**
     * @brief Construct a new Vector object
     * 
     * @param o 
     */
    Vector(const Vector<T>& o);
    /**
     * @brief Construct a new Vector object
     * 
     * @param o 
     */
    Vector(Vector<T>&& o);

    /**
     * @brief Destroy the Vector object
     * 
     */
    virtual ~Vector();

    /**
     * @brief C-Assigns a vector to another
     * 
     * @param o 
     * @return Vector<T>& 
     */
    Vector<T>& operator=(const Vector<T>& o);
    /**
     * @brief M-Assigns a vector to another
     * 
     * @param o 
     * @return Vector<T>& 
     */
    Vector<T>& operator=(Vector<T>&& o);

    /**
     * @brief Gets the size of the vector
     * 
     * @return uint64 
     */
    uint64 size() const noexcept;
    /**
     * @brief Resizes the vector given a size
     * 
     * @param n 
     */
    void resize(uint64 n);
    /**
     * @brief Resizes the vector filling the values given a size and a value
     * 
     * @param n 
     * @param val 
     */
    void resize(uint64 n, const T& val);
    /**
     * @brief Gets the capacity of the vector
     * 
     * @return uint64 
     */
    uint64 capacity() const noexcept;
    /**
     * @brief Returns a boolean indicating if vector is empty or not
     * 
     * @return true 
     * @return false 
     */
    bool empty() const noexcept;

    /**
     * @brief Returns a reference to access elements
     * 
     * @param n 
     * @return T& 
     */
    T& operator[](uint64 n);
    /**
     * @brief Returns a constant reference to access elements
     * 
     * @param n 
     * @return const T& 
     */
    const T& operator[](uint64 n) const;
    /**
     * @brief Returns a reference to access first element
     * 
     * @return T& 
     */
    T& front();
    /**
     * @brief Returns a constant reference to access first element
     * 
     * @return const T& 
     */
    const T& front() const;
    /**
     * @brief Returns a reference to access last element
     * 
     * @return T& 
     */
    T& back();
    /**
     * @brief Returns a constant reference to access last element
     * 
     * @return const T& 
     */
    const T& back() const;
    /**
     * @brief Gets a direct pointer to the raw data
     * 
     * @return T* 
     */
    T* data() noexcept;
    /**
     * @brief Gets a direct constant pointer to the raw data
     * 
     * @return const T* 
     */
    const T* data() const noexcept;

    /**
     * @brief Assigns new contents to the vector given size and value
     * 
     * @param n 
     * @param val 
     */
    void assign(uint64 n, const T& val);
    /**
     * @brief C-Pushes a new element at the end of the vector
     * 
     * @param val 
     */
    void push_back(const T& val);
    /**
     * @brief M-Pushes a new element at the end of the vector
     * 
     * @param val 
     */
    void push_back(T&& val);
    /**
     * @brief Drops the last element of the vector
     * 
     */
    void pop_back();
    /**
     * @brief Clears the vector
     * 
     */
    void clear() noexcept;

private:
    T* m_data;
    uint64 m_size;
    uint64 m_capacity;

    void reallocate();
    void guaranteeSpace(uint64 n);
};

namespace hid
{
uint64 p2RoundUp(uint64 val);

} // namespace hid

} // namespace gil

#include <HSGIL/system/dstr/vector.inl>

#undef HSGIL_INITIAL_CAPACITY
