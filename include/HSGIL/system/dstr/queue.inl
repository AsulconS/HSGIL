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

namespace gil
{
template <typename T>
inline Queue<T>::Queue(uint64 t_capacity)
    : m_front    {0},
      m_back     {t_capacity - 1},
      m_size     {0},
      m_capacity {t_capacity}
{
    m_data = new T[m_capacity];
}

template <typename T>
inline Queue<T>::Queue(const Queue<T>& o)
    : m_front    {o.m_front},
      m_back     {o.m_back},
      m_size     {o.m_size},
      m_capacity {o.m_capacity}
{
    m_data = new T[m_capacity];
    for(uint64 i = 0; i < m_capacity; ++i)
    {
        m_data[i] = o.m_data[i];
    }
}

template <typename T>
inline Queue<T>::Queue(Queue<T>&& o)
    : m_data     {o.m_data},
      m_front    {o.m_front},
      m_back     {o.m_back},
      m_size     {o.m_size},
      m_capacity {o.m_capacity}
{
    o.m_data = nullptr;
}

template <typename T>
inline Queue<T>::~Queue()
{
    delete[] m_data;
}

template <typename T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& o)
{
    delete[] m_data;

    m_front = o.m_front;
    m_back = o.m_back;
    m_size = o.m_size;
    m_capacity = o.m_capacity;

    m_data = new T[m_capacity];
    for(uint64 i = 0; i < m_capacity; ++i)
    {
        m_data[i] = o.m_data[i];
    }

    return (*this);
}

template <typename T>
inline Queue<T>& Queue<T>::operator=(Queue<T>&& o)
{
    delete[] m_data;

    m_data = o.m_data;
    m_front = o.m_front;
    m_back = o.m_back;
    m_size = o.m_size;
    m_capacity = o.m_capacity;

    o.m_data = nullptr;

    return (*this);
}

template <typename T>
inline uint64 Queue<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
inline bool Queue<T>::empty() const noexcept
{
    return !m_size;
}

template <typename T>
inline T& Queue<T>::front()
{
    return m_data[m_front];
}

template <typename T>
inline const T& Queue<T>::front() const
{
    return m_data[m_front];
}

template <typename T>
inline T& Queue<T>::back()
{
    return m_data[m_back];
}

template <typename T>
inline const T& Queue<T>::back() const
{
    return m_data[m_back];
}

template <typename T>
inline void Queue<T>::push(const T& val)
{
    if(m_size == m_capacity)
    {
        return;
    }
    m_back = (m_back + 1) % m_capacity;
    m_data[m_back] = val;
    ++m_size;
}

template <typename T>
inline void Queue<T>::push(T&& val)
{
    if(m_size == m_capacity)
    {
        return;
    }
    m_back = (m_back + 1) % m_capacity;
    m_data[m_back] = hsgil_move(val);
    ++m_size;
}

template <typename T>
inline void Queue<T>::pop()
{
    if(!m_size)
    {
        return;
    }
    m_front = (m_front + 1) % m_capacity;
    --m_size;
}

} // namespace gil
