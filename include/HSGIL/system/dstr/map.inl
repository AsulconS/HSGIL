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
      m_size    {o.m_size},
      m_height  {o.m_height}
{
    copyFromTree(o);
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::Map(Map<Key, T, Comp>&& o)
    : mf_comp   {o.mf_comp},
      m_root    {o.m_root},
      m_size    {o.m_size},
      m_height  {o.m_height}
{
    o.m_root = nullptr;
    o.m_size = 0;
    o.m_height = -1;
}

template <typename Key, typename T, typename Comp>
inline Map<Key, T, Comp>::~Map()
{
    makeEmpty();
}

template <typename Key, typename T, typename Comp>
Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(const Map<Key, T, Comp>& o)
{
    copyTree(o.m_root, o.m_height);

    mf_comp = o.mf_comp;
    m_size = o.m_size;
    m_height = o.m_height;
}

template <typename Key, typename T, typename Comp>
Map<Key, T, Comp>& Map<Key, T, Comp>::operator=(Map<Key, T, Comp>&& o)
{
    makeEmpty();

    mf_comp = o.mf_comp;
    m_root = o.m_root;
    m_size = o.m_size;
    m_height = o.m_height;

    o.m_root = nullptr;
    o.m_size = 0;
    o.m_height = -1;
}

template <typename Key, typename T, typename Comp>
bool Map<Key, T, Comp>::empty() const noexcept
{
    return !m_size;
}

template <typename Key, typename T, typename Comp>
uint64 Map<Key, T, Comp>::size() const noexcept
{
    return m_size;
}

template <typename Key, typename T, typename Comp>
T& Map<Key, T, Comp>::operator[](const Key& key)
{
}

template <typename Key, typename T, typename Comp>
T& Map<Key, T, Comp>::operator[](Key&& key)
{
}

template <typename Key, typename T, typename Comp>
T& Map<Key, T, Comp>::at(const Key& key)
{
}

template <typename Key, typename T, typename Comp>
const T& Map<Key, T, Comp>::at(const Key& key) const
{
}

template <typename Key, typename T, typename Comp>
bool Map<Key, T, Comp>::contains(const Key& key) const
{
}

template <typename Key, typename T, typename Comp>
void Map<Key, T, Comp>::makeEmpty()
{
    if(m_root == nullptr)
    {
        return;
    }

    Node* currentNode {nullptr};
    Queue<Node*> path {m_height + 1};
    path.push(m_root);
    while(!path.empty())
    {
        currentNode = path.front();
        path.pop();

        if(currentNode->left != nullptr)
        {
            path.push(currentNode->left);
        }
        if(currentNode->right != nullptr)
        {
            path.push(currentNode->right);
        }

        delete currentNode;
    }

    m_root = nullptr;
    m_size = 0;
    m_height = -1;
}

template <typename Key, typename T, typename Comp>
void Map<Key, T, Comp>::copyTree(const Node* root, int32 height)
{
    if(root == nullptr)
    {
        return;
    }

    makeEmpty();
    Node* currentNode {nullptr};
    Queue<Node*> path {height + 1};
    path.push(root);
    while(!path.empty())
}

} // namespace gil
