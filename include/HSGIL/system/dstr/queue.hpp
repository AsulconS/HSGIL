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

#define HSGIL_QUEUE_DEFAULT_CAPACITY 16

namespace gil
{
template <typename T>
class Queue
{
public:
    /**
     * @brief Construct a new Queue object
     * 
     * @param t_capacity 
     */
    Queue(uint64 t_capacity = HSGIL_QUEUE_DEFAULT_CAPACITY);

    /**
     * @brief Construct a new Queue object
     * 
     * @param o 
     */
    Queue(const Queue<T>& o);
    /**
     * @brief Construct a new Queue object
     * 
     * @param o 
     */
    Queue(Queue<T>&& o);

    /**
     * @brief Destroy the Queue object
     * 
     */
    virtual ~Queue();

    /**
     * @brief C-Assigns a queue to another
     * 
     * @param o 
     * @return Queue<T>& 
     */
    Queue<T>& operator=(const Queue<T>& o);
    /**
     * @brief M-Assigns a queue to another
     * 
     * @param o 
     * @return Queue<T>& 
     */
    Queue<T>& operator=(Queue<T>&& o);

    /**
     * @brief Gets the size of the queue
     * 
     * @return uint64 
     */
    uint64 size() const noexcept;
    /**
     * @brief Returns a boolean indicating if queue is empty or not
     * 
     * @return true 
     * @return false 
     */
    bool empty() const noexcept;

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
     * @brief C-Pushes a new element to the queue
     * 
     * @param val 
     */
    void push(const T& val);
    /**
     * @brief M-Pushes a new element to the queue
     * 
     * @param val 
     */
    void push(T&& val);
    /**
     * @brief Drops the last element of the queue
     * 
     */
    void pop();

private:
    T* m_data;
    uint64 m_front;
    uint64 m_back;
    uint64 m_size;
    uint64 m_capacity;
};

} // namespace gil

#include <HSGIL/system/dstr/queue.inl>

#undef HSGIL_QUEUE_DEFAULT_CAPACITY
