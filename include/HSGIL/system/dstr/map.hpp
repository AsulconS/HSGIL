/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2021 Adrian Bedregal                                      *
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

#ifndef HSGIL_DSTR_MAP_HPP
#define HSGIL_DSTR_MAP_HPP

#include <HSGIL/config/config.hpp>
#include <HSGIL/config/common.hpp>

#include <HSGIL/system/utility.hpp>
#include <HSGIL/system/dstr/queue.hpp>

#define _CONST_RED true
#define _CONST_BLACK false

namespace gil
{
namespace _priv
{
template <typename T>
class LessComp
{
    inline constexpr bool operator()(const T& l, const T& r) const { return l < r; }
};

} // namespace _priv

template <typename Key, typename T, typename Comp = _priv::LessComp<Key>>
class Map
{
public:
    /**
     * @brief Construct a new Map object
     * 
     * @param t_comp 
     */
    Map(const Comp& t_comp = Comp {});

    /**
     * @brief Construct a new Map object
     * 
     * @param o 
     */
    Map(const Map<Key, T, Comp>& o);
    /**
     * @brief Construct a new Map object
     * 
     * @param o 
     */
    Map(Map<Key, T, Comp>&& o);

    /**
     * @brief Destroy the Map object
     * 
     */
    virtual ~Map();

    /**
     * @brief C-Assigns a map to another
     * 
     * @param o 
     * @return Map<Key, T, Comp>& 
     */
    Map<Key, T, Comp>& operator=(const Map<Key, T, Comp>& o);
    /**
     * @brief M-Assigns a map to another
     * 
     * @param o 
     * @return Map<Key, T, Comp>& 
     */
    Map<Key, T, Comp>& operator=(Map<Key, T, Comp>&& o);

    /**
     * @brief Returns a boolean indicating if map is empty or not
     * 
     * @return true 
     * @return false 
     */
    bool empty() const noexcept;
    /**
     * @brief Gets the size of the map
     * 
     * @return uint64 
     */
    uint64 size() const noexcept;

    /**
     * @brief Returns a reference to access elements given a l-value key. 
     * If key doesn't exist, it gets created
     * 
     * @param key 
     * @return T& 
     */
    T& operator[](const Key& key);
    /**
     * @brief Returns a reference to access elements given a r-value key. 
     * If key doesn't exist, it gets created
     * 
     * @param key 
     * @return const T& 
     */
    T& operator[](Key&& key);
    /**
     * @brief Returns a reference to access elements given a l-value key
     * 
     * @param key 
     * @return T& 
     */
    T& at(const Key& key);
    /**
     * @brief Returns a constant reference to access elements given a l-value key
     * 
     * @param key 
     * @return const T& 
     */
    const T& at(const Key& key) const;

    /**
     * @brief Returns a boolean indicating if map contains some key
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool contains(const Key& key) const;

private:
    struct Pair
    {
        const Key first;
        T second;
    };

    struct Node
    {
        Pair data;
        bool color;
        Node* left;
        Node* right;
    };

private:
    void makeEmpty();
    void copyFromTree(const Map<Key, T, Comp>& o);

private:
    Comp mf_comp;
    Node* m_root;
    uint64 m_size;

    int32 m_height;
};

} // namespace gil

#include <HSGIL/system/dstr/map.inl>

#endif // HSGIL_DSTR_MAP_HPP
