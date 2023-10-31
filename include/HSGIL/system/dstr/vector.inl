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

namespace gil
{
template <typename T>
inline Vector<T>::Vector()
    : m_data     {nullptr},
      m_size     {0},
      m_capacity {HSGIL_INITIAL_CAPACITY}
{
    m_data = new T[m_capacity];
}

template <typename T>
inline Vector<T>::Vector(uint64 n)
    : m_data     {nullptr},
      m_size     {n},
      m_capacity {hid::p2RoundUp(n)}
{
    m_data = new T[m_capacity];
}

template <typename T>
inline Vector<T>::Vector(uint64 n, const T& val)
    : Vector {n}
{
    for(uint64 i = 0; i < m_size; ++i)
    {
        m_data[i] = val;
    }
}

template <typename T>
inline Vector<T>::Vector(const Vector<T>& o)
    : m_size     {o.m_size},
      m_capacity {o.m_capacity}
{
    m_data = new T[m_capacity];
    for(uint64 i = 0; i < m_size; ++i)
    {
        m_data[i] = o.m_data[i];
    }
}

template <typename T>
inline Vector<T>::Vector(Vector<T>&& o)
    : m_size     {o.m_size},
      m_capacity {o.m_capacity}
{
    m_data = o.m_data;
    o.m_data = nullptr;
}

template <typename T>
inline Vector<T>::~Vector()
{
    delete[] m_data;
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& o)
{
    delete[] m_data;

    m_size = o.m_size;
    m_capacity = o.m_capacity;

    m_data = new T[m_capacity];
    for(uint64 i = 0; i < m_size; ++i)
    {
        m_data[i] = o.m_data[i];
    }

    return (*this);
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T>&& o)
{
    delete[] m_data;

    m_size = o.m_size;
    m_capacity = o.m_capacity;

    m_data = o.m_data;
    o.m_data = nullptr;

    return (*this);
}

template <typename T>
inline uint64 Vector<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
inline void Vector<T>::resize(uint64 n)
{
    guaranteeSpace(n);
    m_size = n;
}

template <typename T>
inline void Vector<T>::resize(uint64 n, const T& val)
{
    guaranteeSpace(n);
    for(uint64 i = m_size; i < n; ++i)
    {
        m_data[i] = val;
    }
    m_size = n;
}

template <typename T>
inline uint64 Vector<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
inline bool Vector<T>::empty() const noexcept
{
    return !m_size;
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
inline T& Vector<T>::front()
{
    return m_data[0];
}

template <typename T>
inline const T& Vector<T>::front() const
{
    return m_data[0];
}

template <typename T>
inline T& Vector<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
inline const T& Vector<T>::back() const
{
    return m_data[m_size - 1];
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
inline void Vector<T>::assign(uint64 n, const T& val)
{
    guaranteeSpace(n);
    for(uint64 i = 0; i < n; ++i)
    {
        m_data[i] = val;
    }
    m_size = n;
}

template <typename T>
inline void Vector<T>::push_back(const T& val)
{
    if(m_size == m_capacity)
    {
        m_capacity <<= 0x1;
        reallocate();
    }
    m_data[m_size++] = val;
}

template <typename T>
inline void Vector<T>::push_back(T&& val)
{
    if(m_size == m_capacity)
    {
        m_capacity <<= 0x1;
        reallocate();
    }
    m_data[m_size++] = hsgil_move(val);
}

template <typename T>
inline void Vector<T>::pop_back()
{
    if(m_size)
    {
        --m_size;
    }
}

template <typename T>
inline void Vector<T>::clear() noexcept
{
    m_size = 0;
}

template <typename T>
inline void Vector<T>::reallocate()
{
    T* n_data {new T[m_capacity]};
    for(uint64 i = 0; i < m_size; ++i)
    {
        n_data[i] = hsgil_move(m_data[i]);
    }
    delete[] m_data;
    m_data = n_data;
}

template <typename T>
inline void Vector<T>::guaranteeSpace(uint64 n)
{
    if(n > m_capacity)
    {
        m_capacity = hid::p2RoundUp(n);
        reallocate();
    }
}

namespace hid
{
inline uint64 p2RoundUp(uint64 val)
{
    --val;
    val |= (val >> 0x01);
    val |= (val >> 0x02);
    val |= (val >> 0x04);
    val |= (val >> 0x08);
    val |= (val >> 0x10);
    val |= (val >> 0x20);
    return val + 0x1;
}

} // namespace hid

} // namespace gil
