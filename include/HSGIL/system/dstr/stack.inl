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
inline Stack<T>::Stack(uint64 t_capacity)
    : m_size     {0},
      m_capacity {t_capacity}
{
    m_data = new T[m_capacity];
}

template <typename T>
inline Stack<T>::Stack(const Stack<T>& o)
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
inline Stack<T>::Stack(Stack<T>&& o)
    : m_data     {o.m_data},
      m_size     {o.m_size},
      m_capacity {o.m_capacity}
{
    o.m_data = nullptr;
}

template <typename T>
inline Stack<T>::~Stack()
{
    delete[] m_data;
}

template <typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& o)
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
inline Stack<T>& Stack<T>::operator=(Stack<T>&& o)
{
    delete[] m_data;

    m_data = o.m_data;
    m_size = o.m_size;
    m_capacity = o.m_capacity;

    o.m_data = nullptr;

    return (*this);
}

template <typename T>
inline uint64 Stack<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
inline bool Stack<T>::empty() const noexcept
{
    return !m_size;
}

template <typename T>
inline T& Stack<T>::top()
{
    return m_data[m_size - 1];
}

template <typename T>
inline const T& Stack<T>::top() const
{
    return m_data[m_size - 1];
}

template <typename T>
inline void Stack<T>::push(const T& val)
{
    if(m_size == m_capacity)
    {
        return;
    }
    m_data[m_size++] = val;
}

template <typename T>
inline void Stack<T>::push(T&& val)
{
    if(m_size == m_capacity)
    {
        return;
    }
    m_data[m_size++] = hsgil_move(val);
}

template <typename T>
inline void Stack<T>::pop()
{
    if(!m_size)
    {
        return;
    }
    --m_size;
}

} // namespace gil
