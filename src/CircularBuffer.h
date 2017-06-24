/**
 * \file   CircularBuffer.h
 * \author Jonathan Simmonds
 * \brief  Fast implementation of a Circular Buffer.
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
#ifndef _COMMON_CIRCULARBUFFER_H
#define _COMMON_CIRCULARBUFFER_H

#include <stdint.h>
#include <stdexcept>    // out_of_range


/**  
 * \brief   Fast implementation of a Circular Buffer.
 *
 * One space in the buffer is always left empty for technical reasons, so ensure
 * that this is accounted for when the bufferSize is decided upon (i.e.
 * <tt>maximumCapacity = bufferSize - 1</tt>). All operations on the
 * Circular Buffer can be performed in constant time.
*/
template <class T>
class CircularBuffer
{
private:
    /** The buffer size. */
    const uint16_t bufferSize;
    /** The actual buffer. */
    T* buffer;
    /** The buffer head: always points to a blank (or no-longer accessible)
     *  element. */
    uint16_t head;
    /** The buffer tail: always points to the oldest element. */
    uint16_t tail;

    /**
     * \brief   sMod performs the calculation (x % bufferSize) where:
     *          <tt>0 <= x < 2*bufferSize</tt>
     *          It performs the calculation much faster than the modulo
     *          function, however it is important that the two restrictions on
     *          x are observed.
     * \param   x   x in the calculation (x % bufferSize).
     * \return      The solution to the calculation (x % bufferSize).
    */
    #define sMod(x) (x < bufferSize ? x : x - bufferSize)

public:
    /**
     * \brief   Constructor, setting the CircularBuffer's variables.
     * \param   bs  The buffer size. Once initialised this is not changeable.
     */
    explicit CircularBuffer(const uint16_t bs = 32) :
        bufferSize(bs),
        head(0),
        tail(0)
    {
        buffer = new T[bs];
    }

    /**
     * \brief   Deconstructor.
     */
    ~CircularBuffer(void)
    {
        delete[] buffer;
    }

    /**
     * \brief   Returns whether or not the buffer is full.
     *          When full the buffer will insert new elements over the oldest.
     * \return  The state of the buffer.
     */
    inline bool isFull(void) const noexcept
    {
        return (sMod(head + 1) == tail);
    }

    /**
     * \brief   Returns whether or not the buffer is empty.
     * \return  The state of the buffer.
     */
    inline bool isEmpty(void) const noexcept
    {
        return (head == tail);
    }

    /**
     * \brief   Retrieves the current number of elements in the buffer.
     * \return  The number of elements in the buffer.
     */
    inline uint16_t getSize(void) const noexcept
    {
        return (head < tail) ? (head + bufferSize) - tail : head - tail;
    }

    /**
     * \brief   Treats the buffer like an array with indexes
     *          <tt>[0,bufferSize)</tt> and returns the item from the buffer
     *          located at the given index. The <i>newest</i> element will be
     *          available at index 0.
     * \param   index   The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \throws  out_of_range    If the index is invalid (i.e. not
     *              <tt>0 <= index < bufferSize-1</tt> (as the buffer
     *              always has 1 empty space for technical reasons)).
     * \see     operator[](int)
     */
    inline const T& at(uint16_t index) const noexcept(false)
    {
        // newest element (which we want to appear at [0]) is accessible from
        // the head, but (head - index) may underflow, so increase by bs-1.
        index = sMod((head + bufferSize - 1) - index);
        if (index >= bufferSize - 1)
            throw std::out_of_range("Out of range access to CircularBuffer");
        return buffer[index];
    }

    /**
     * \brief   Treats the buffer like an array with indexes
     *          <tt>[0,bufferSize)</tt> and returns the item from the buffer
     *          located at the given index. The <i>newest</i> element will be
     *          available at index 0.
     * \param   index   The index of the target element in the virtual 'array'.
     * \return  Reference to the target element.
     * \throws  out_of_range    If the index is invalid (i.e. not
     *              <tt>0 <= index < bufferSize-1</tt> (as the buffer
     *              always has 1 empty space for technical reasons)).
     * \see     at(uint16_t)
     */
    inline const T& operator[](const size_t index) const noexcept(false)
    {
        return at(index);
    }

    /**
     * \brief   Adds an item to the buffer, overwriting the oldest item if the
     *          buffer is full.
     * \param   item    The item to add to the buffer.
     */
    inline void add(const T& item) noexcept
    {
        buffer[head] = item;
        head = sMod(head + 1);
        if (head == tail)
            tail = sMod(tail + 1);
    }

    /**
     * \brief   Removes the oldest item (if one exists) from the buffer.
     */
    inline void remove(void) noexcept
    {
        if (!isEmpty())
            tail = sMod(tail + 1);
    }
};

#endif
