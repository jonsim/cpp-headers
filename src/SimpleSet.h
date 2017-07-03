/**
 * \file   SimpleSet.h
 * \author Jonathan Simmonds
 * \brief  Very basic, light-weight unordered set designed for small data.
 *
 * MIT License
 *
 * Copyright (c) 2017 Jonathan Simmonds
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _COMMON_SIMPLESET_H
#define _COMMON_SIMPLESET_H

#include <algorithm>    // find
#include <vector>       // vector


/**
 * \brief   Very basic, light-weight unordered set for small data.
 *
 * This uses a std::vector to hold the data and merely guarantees uniqueness
 * (and immutability) of data and provides set-like methods. This has a smaller
 * memory footprint and is faster than std::set for small amounts of data, but
 * has O(n) complexity for insertion (all other operations are O(1)) so will
 * perform worse than std::set for large n.
 */
template <class T>
class SimpleSet
{
private:
    /** The vector that actually holds the data. */
    std::vector<T> set;

public:
    /**
     * \brief   SimpleSet Constructor.
     */
    explicit SimpleSet(void) : set() {}

    /**
     * \brief   SimpleSet Destructor.
     */
    virtual ~SimpleSet(void) {}

    /**
     * \brief   Queries whether the set contains the given element.
     * \param   elem    The element to check for (will use ==).
     * \return  true if the element is already in the set, false otherwise.
     */
    inline bool contains(const T& elem) const noexcept
    {
        return std::find(set.begin(), set.end(), elem) != set.end();
    }

    /**
     * \brief   Inserts the given element into the set.
     * \param   elem    The element to insert (no action will be taken if it is
     *                  already in the set).
     */
    inline void insert(const T& elem) noexcept
    {
        if (!contains(elem))
            set.push_back(elem);
    }

    /**
     * \brief   Queries whether the set is empty (i.e. size 0).
     * \return  true if empty, false otherwise.
     */
    inline bool empty(void) const noexcept
    {
        return set.empty();
    }

    /**
     * \brief   Determines the set size.
     * \return  Number of elements in the set.
     */
    inline size_t size(void) const noexcept
    {
        return set.size();
    }

    /**
     * \brief   Returns an iterator pointing to the first element in the set.
     * \return  An iterator to the beginning of the container.
     */
    inline typename std::vector<T>::iterator begin(void) noexcept
    {
        return set.begin();
    }

    /**
     * \brief   Returns an iterator pointing to the past-the-end element in the
     *          set.
     * \return  An iterator to past the end of the container.
     */
    inline typename std::vector<T>::iterator end(void) noexcept
    {
        return set.end();
    }

    /**
     * \brief   Retrieves the element at the given position in the set.
     * \param   n   The index of the element to fetch.
     * \return  Constant reference to the element.
     * \throws  out_of_range    If the index is invalid (i.e. not <tt>0 <= n <
     *              size</tt>)
     */
    inline const T& at(const size_t n) const noexcept(false)
    {
        return set[n];
    }

    /**
     * \brief   Retrieves the element at the given position in the set.
     * \param   n   The index of the element to fetch.
     * \return  Constant reference to the element.
     * \throws  out_of_range    If the index is invalid (i.e. not <tt>0 <= n <
     *              size</tt>)
     */
    inline const T& operator[](const size_t n) const noexcept(false)
    {
        return set[n];
    }
};

#endif
