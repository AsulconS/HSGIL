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
template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::Map(const Comp& t_comp)
    : mf_comp   {t_comp},
      m_root    {nullptr},
      m_size    {0},
      m_height  {-1}
{
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::Map(const Map<Key, T, Comp>& o)
    : mf_comp   {o.mf_comp},
      m_root    {h_clone(o.m_root)},
      m_size    {o.m_size},
      m_height  {o.m_height}
{
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::Map(Map<Key, T, Comp>&& o)
    : mf_comp   {o.mf_comp},
      m_root    {o.m_root},
      m_size    {o.m_size},
      m_height  {o.m_height}
{
    o.m_root = nullptr;
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::~Map()
{
    h_makeEmpty(m_root);
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(const Map<Key, T, Comp>& o)
{
    h_makeEmpty(m_root);

    mf_comp = o.mf_comp;
    m_root = h_clone(o.m_root);
    m_size = o.m_size;
    m_height = o.m_height;
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(Map<Key, T, Comp>&& o)
{
    h_makeEmpty(m_root);

    mf_comp = o.mf_comp;
    m_root = o.m_root;
    m_size = o.m_size;
    m_height = o.m_height;

    o.m_root = nullptr;
}

template <typename Key, typename T, typename Comp>
inline bool Map<Key, T, Comp>::empty() const noexcept
{
    return !m_size;
}

template <typename Key, typename T, typename Comp>
inline uint64 Map<Key, T, Comp>::size() const noexcept
{
    return m_size;
}

template <typename Key, typename T, typename Comp>
inline void Map<Key, T, Comp>::clear()
{
    h_makeEmpty(m_root);

    m_root = nullptr;
    m_size = 0;
    m_height = -1;
}

template <typename Key, typename T, typename Comp>
inline T& Map<Key, T, Comp>::operator[](const Key& key)
{
}

template <typename Key, typename T, typename Comp>
inline T& Map<Key, T, Comp>::operator[](Key&& key)
{
}

template <typename Key, typename T, typename Comp>
inline T& Map<Key, T, Comp>::at(const Key& key)
{
    Node* node {h_find(key, m_root)};
    if(node == nullptr)
    {
        throw KeyNotFoundException();
        return;
    }
    return node->data.second;
}

template <typename Key, typename T, typename Comp>
inline const T& Map<Key, T, Comp>::at(const Key& key) const
{
    const Node* node {h_find(key, m_root)};
    if(node == nullptr)
    {
        throw KeyNotFoundException();
        return;
    }
    return node->data.second;
}

template <typename Key, typename T, typename Comp>
inline bool Map<Key, T, Comp>::contains(const Key& key) const
{
    h_find(key, m_root) != nullptr;
}

template <typename Key, typename T, typename Comp>
inline typename Map<Key, T, Comp>::Node* Map<Key, T, Comp>::h_clone(const Node* root) const
{
    if(root == nullptr)
    {
        return nullptr;
    }
    return new Node {root->data, root->color, h_clone(root->left), h_clone(root->right)};
}

template <typename Key, typename T, typename Comp>
inline typename Map<Key, T, Comp>::Node* Map<Key, T, Comp>::h_find(const Key& key, Node* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    if(mf_comp(key, root->data.first))
    {
        return h_contains(key, root->left);
    }
    if(mf_comp(root->data.first, key))
    {
        return h_contains(key, root->right);
    }
    return root;
}

template <typename Key, typename T, typename Comp>
inline const typename Map<Key, T, Comp>::Node* Map<Key, T, Comp>::h_find(const Key& key, const Node* root) const
{
    if(root == nullptr)
    {
        return nullptr;
    }
    if(mf_comp(key, root->data.first))
    {
        return h_contains(key, root->left);
    }
    if(mf_comp(root->data.first, key))
    {
        return h_contains(key, root->right);
    }
    return root;
}

template <typename Key, typename T, typename Comp>
inline typename Map<Key, T, Comp>::Node* Map<Key, T, Comp>::h_stdInsert(const Key& key)
{
    Node* parent {nullptr};
    Node* current {m_root};
    while(current != nullptr)
    {
        parent = current;
        if(mf_comp(key, current->data.first))
        {
            current = current->left;
        }
        else if(mf_comp(current->data.first, key))
        {
            current = current->right;
        }
        else
        {
            return;
        }
    }

    Node* node {new Node {{key, T {}}, parent, nullptr, nullptr, HSGIL_CONST_RED}};
    if(parent == nullptr)
    {
        m_root = node;
    }
    else if(m)

    if(node->parent == nullptr)

    return node;
}

template <typename Key, typename T, typename Comp>
inline typename Map<Key, T, Comp>::Node* Map<Key, T, Comp>::h_stdInsert(Key&& key)
{
    if(root == nullptr)
    {
        return root = new Node {{hsgil_move(key), T {}}, HSGIL_CONST_RED, nullptr, nullptr};
    }
    if(mf_comp(key, root->data.first))
    {
        return h_insert(hsgil_move(key), root->left);
    }
    if(mf_comp(root->data.first, key))
    {
        return h_insert(hsgil_move(key), root->right);
    }
    return nullptr;
}

template <typename Key, typename T, typename Comp>
inline void Map<Key, T, Comp>::h_makeEmpty(Node* root)
{
    if(root == nullptr)
    {
        return;
    }
    h_makeEmpty(root->left);
    h_makeEmpty(root->right);
    delete root;
}

} // namespace gil
