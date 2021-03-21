/**
 * \file   circular_buffer.h
 * \author Jonathan Simmonds
 * \brief  Fast implementation of a Circular Buffer.
 *
 * MIT License
 *
 * Copyright (c) 2017-2021 Jonathan Simmonds
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
#ifndef _COMMON_CIRCULAR_BUFFER_H
#define _COMMON_CIRCULAR_BUFFER_H

#include <array>    // array
#include <cstdlib>  // size_t


/**  
 * \brief       Fast implementation of a Circular Buffer. All operations on the
 *              Circular Buffer can be performed in constant time.
 *
 * \param T     The type stored in this buffer. Must have a default constructor.
 * \param SIZE  The number of elements to be stored in the buffer. 
 *              One space in the buffer is always left empty, so ensure that
 *              this is accounted for when the SIZE is decided upon (i.e.
 *              <tt>capacity = SIZE - 1</tt>).
 */
template <typename T, std::size_t SIZE>
class circular_buffer {
public:
    /** The type this buffer stores. */
    using value_type = T;
    /** An iterator type to iterate over elements in this buffer. */
    using iterator = T*;
    /** A const-iterator type to iterate over elements in this buffer. */
    using const_iterator = const T*;

    /**
     * \brief   Constructor, initialising the circular_buffer.
     */
    circular_buffer() = default;

    /**
     * \brief   Destructor.
     */
    virtual ~circular_buffer() = default;

    /**
     * \brief   Returns whether or not the buffer is full.
     *          When full the buffer will insert new elements over the oldest.
     * \return  The state of the buffer.
     */
    bool full() const noexcept;

    /**
     * \brief   Returns whether or not the buffer is empty.
     * \return  The state of the buffer.
     */
    bool empty() const noexcept;

    /**
     * \brief   Retrieves the current number of elements in the buffer.
     * \return  The number of elements in the buffer.
     */
    std::size_t len() const noexcept;

    /**
     * \brief   Retrieves the maximum number of elements the buffer can hold
     *          before it starts overwriting the oldest. This is always
     *          <tt>SIZE - 1</tt>.
     * \return  The maximum number of unique elements this buffer can hold.
     */
    constexpr std::size_t capacity() const noexcept;

    /**
     * \brief   Treats the buffer like an array with indices <tt>[0,SIZE-1)</tt>
     *          and returns the item from the buffer located at the given index.
     *          The <i>newest</i> element will be available at index 0.
     * \param   pos The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \throws  std::out_of_range   If the index is invalid (i.e. not
     *              <tt>0 <= index < SIZE-1</tt>.
     * \see     operator[](std::size_t)
     */
    const T& at(std::size_t pos) const noexcept(false);

    /**
     * \brief   Treats the buffer like an array with indices <tt>[0,SIZE-1)</tt>
     *          and returns the item from the buffer located at the given index.
     *          The <i>newest</i> element will be available at index 0.
     * \param   pos The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \throws  std::out_of_range   If the index is invalid (i.e. not
     *              <tt>0 <= index < SIZE-1</tt>.
     * \see     operator[](std::size_t)
     */
    T& at(std::size_t pos) noexcept(false);

    /**
     * \brief   Treats the buffer like an array with indices <tt>[0,SIZE-1)</tt>
     *          and returns the item from the buffer located at the given index.
     *          The <i>newest</i> element will be available at index 0.
     *          This operation does not perform bounds checking, accessing an
     *          uninitialised element causes undefined behaviour.
     * \param   pos The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \see     at(std::size_t)
     */
    const T& operator[](std::size_t pos) const noexcept;

    /**
     * \brief   Treats the buffer like an array with indices <tt>[0,SIZE-1)</tt>
     *          and returns the item from the buffer located at the given index.
     *          The <i>newest</i> element will be available at index 0.
     *          This operation does not perform bounds checking, accessing an
     *          uninitialised element causes undefined behaviour.
     * \param   pos The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \see     at(std::size_t)
     */
    T& operator[](std::size_t pos) noexcept;

    /**
     *  \brief  Returns a reference to the last inserted (i.e. <i>newest</i>)
     *          element in the buffer.
     *          Calling <tt>back()</tt> on an empty buffer causes undefined
     *          behavior.
     *  \return Reference to the newest element in the buffer.
     */
    const T& back() const noexcept;

    /**
     *  \brief  Returns a reference to the last inserted (i.e. <i>newest</i>)
     *          element in the buffer.
     *          Calling <tt>back()</tt> on an empty buffer causes undefined
     *          behavior.
     *  \return Reference to the newest element in the buffer.
     */
    T& back() noexcept;

    /**
     *  \brief  Returns a reference to the first inserted (i.e. <i>oldest</i>)
     *          element in the buffer.
     *          Calling <tt>front()</tt> on an empty buffer causes undefined
     *          behavior.
     *  \return Reference to the oldest element in the buffer.
     */
    const T& front() const noexcept;

    /**
     *  \brief  Returns a reference to the first inserted (i.e. <i>oldest</i>)
     *          element in the buffer.
     *          Calling <tt>front()</tt> on an empty buffer causes undefined
     *          behavior.
     *  \return Reference to the oldest element in the buffer.
     */
    T& front() noexcept;

    /**
     * \brief   Copies an item into the buffer, overwriting the oldest item if the
     *          buffer is full.
     * \param   item    The item to copy into the buffer.
     */
    void push_back(const T& item) noexcept;

    /**
     * \brief   Moves an item into the buffer, overwriting the oldest item if the
     *          buffer is full.
     * \param   item    The item to move into the buffer.
     */
    void push_back(T&& item) noexcept;

    /**
     * \brief   Removes the oldest item (if one exists) from the buffer.
     *          Calling <tt>pop_front()</tt> on an empty buffer causes undefined
     *          behaviour.
     */
    void pop_front() noexcept;

    /**
     *  \brief  Returns an iterable object to the beginning (i.e. front) of the
     *          buffer. If the buffer is empty the returned iterator will be
     *          equal to <tt>end()</tt>.
     *  \return Iterator to the front of the buffer.
     */
    iterator begin() noexcept;

    /**
     *  \brief  Returns an iterable object to the beginning (i.e. front) of the
     *          buffer. If the buffer is empty the returned iterator will be
     *          equal to <tt>end()</tt>.
     *  \return Iterator to the front of the buffer.
     */
    const_iterator begin() const noexcept;

    /**
     *  \brief  Returns an iterable object to the element following the last
     *          element (i.e. back) of the buffer.
     *          This element acts as a placeholder; attempting to access it
     *          results in undefined behavior.
     *  \return Iterator to the element following the last element.
     */
    iterator end() noexcept;

    /**
     *  \brief  Returns an iterable object to the element following the last
     *          element (i.e. back) of the buffer.
     *          This element acts as a placeholder; attempting to access it
     *          results in undefined behavior.
     *  \return Iterator to the element following the last element.
     */
    const_iterator end() const noexcept;

private:
    /** The actual buffer. */
    std::array<T, SIZE> buffer {};
    /** The buffer head: always points to a blank (or no-longer accessible)
     *  element. */
    std::size_t head { 0 };
    /** The buffer tail: always points to the oldest element. */
    std::size_t tail { 0 };

    /**
     * \brief   Performs the calculation (x % SIZE) where:
     *          <tt>0 <= x < 2*SIZE</tt>
     *          It performs the calculation much faster than the modulo
     *          function, however it is important that the two restrictions on
     *          x are observed.
     * \param   x   x in the calculation (x % SIZE).
     * \return      The solution to the calculation (x % SIZE).
    */
    constexpr std::size_t capped_mod(std::size_t x) const noexcept {
        return x < SIZE ? x : x - SIZE;
    }
};

#include "circular_buffer.tpp"
#endif // _COMMON_CIRCULAR_BUFFER_H