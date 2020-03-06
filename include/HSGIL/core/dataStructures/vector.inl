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

template <typename T>
inline Vector<T>::Vector()
    : m_data     {nullptr},
      m_size     {0},
      m_capacity {INITIAL_CAPACITY}
{
    m_data = new T[INITIAL_CAPACITY];
}

template <typename T>
inline Vector<T>::~Vector()
{
    delete[] m_data;
}

template <typename T>
inline void Vector<T>::push_back(const T& val)
{
    if(m_size >= m_capacity)
    {
        reallocate();
    }
    m_data[m_size++] = val;
}

template <typename T>
inline void Vector<T>::push_back(T&& val)
{
    if(m_size >= m_capacity)
    {
        reallocate();
    }
    m_data[m_size++] = hsgil_move(val);
}

template <typename T>
inline T* Vector<T>::data() noexcept
{
    return m_data;
}

template <typename T>
inline const T* Vector<T>::data() const noexcept
{
    return m_data;
}

template <typename T>
inline uint64 Vector<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
inline uint64 Vector<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
inline T& Vector<T>::operator[](uint64 n)
{
    return m_data[n];
}

template <typename T>
inline const T& Vector<T>::operator[](uint64 n) const
{
    return m_data[n];
}

template <typename T>
inline void Vector<T>::reallocate()
{
    T* n_data = new T[m_capacity *= 2];
    for(uint64 i = 0; i < m_size; ++i)
    {
        n_data[i] = hsgil_move(m_data[i]);
    }
    delete[] m_data;
    m_data = n_data;
}
