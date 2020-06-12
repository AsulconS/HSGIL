/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2020 Adrian Bedregal and Gabriela Chipana                      *
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

#ifndef HSGIL_DSTR_VECTOR_HPP
#define HSGIL_DSTR_VECTOR_HPP

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/utility.hpp>

#define INITIAL_CAPACITY 4

namespace gil
{
template <typename T>
class Vector
{
public:
    explicit Vector();
    explicit Vector(uint64 n);

    Vector(uint64 n, const T& val);

    Vector(const Vector<T>& o);
    Vector(Vector<T>&& o);

    virtual ~Vector();

    Vector<T>& operator=(const Vector<T>& o);
    Vector<T>& operator=(Vector<T>&& o);

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
     * @brief Gets a direct pointer to the raw data
     * 
     * @return T* 
     */
    T* data() noexcept;
    /**
     * @brief Gets a direct pointer to the raw data
     * 
     * @return const T* 
     */
    const T* data() const noexcept;
    /**
     * @brief Gets the size of the vector
     * 
     * @return uint64 
     */
    uint64 size() const noexcept;
    /**
     * @brief Gets the capacity of the vector
     * 
     * @return uint64 
     */
    uint64 capacity() const noexcept;

    T& operator[](uint64 n);
    const T& operator[](uint64 n) const;

private:
    T* m_data;
    uint64 m_size;
    uint64 m_capacity;

    void reallocate();
};

} // namespace gil

#include <HSGIL/core/dataStructures/vector.inl>

#endif // HSGIL_DSTR_VECTOR_HPP
