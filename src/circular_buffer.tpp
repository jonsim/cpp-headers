/**
 * \file   circular_buffer.tpp
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
#include <stdexcept> // out_of_range

#include "circular_buffer.h"


template <typename T, std::size_t SIZE>
T& circular_buffer<T, SIZE>::iterator::operator*() noexcept {
    return buffer.buffer[pos];
}
template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::iterator::operator++() noexcept {
    pos = buffer.capped_mod(pos + 1);
}
template <typename T, std::size_t SIZE>
const bool circular_buffer<T, SIZE>::iterator::operator==(const iterator& other) noexcept {
    return &buffer == &other.buffer && pos == other.pos;
}
template <typename T, std::size_t SIZE>
const bool circular_buffer<T, SIZE>::iterator::operator!=(const iterator& other) noexcept {
    return !operator==(other);
}

template <typename T, std::size_t SIZE>
const T& circular_buffer<T, SIZE>::const_iterator::operator*() noexcept {
    return buffer.buffer[pos];
}
template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::const_iterator::operator++() noexcept {
    pos = buffer.capped_mod(pos + 1);
}
template <typename T, std::size_t SIZE>
const bool circular_buffer<T, SIZE>::const_iterator::operator==(const const_iterator& other) noexcept {
    return &buffer == &other.buffer && pos == other.pos;
}
template <typename T, std::size_t SIZE>
const bool circular_buffer<T, SIZE>::const_iterator::operator!=(const const_iterator& other) noexcept {
    return !operator==(other);
}


template <typename T, std::size_t SIZE>
bool circular_buffer<T, SIZE>::full() const noexcept {
    return capped_mod(head + 1) == tail;
}

template <typename T, std::size_t SIZE>
bool circular_buffer<T, SIZE>::empty() const noexcept {
    return head == tail;
}

template <typename T, std::size_t SIZE>
std::size_t circular_buffer<T, SIZE>::len() const noexcept {
    return (head < tail) ? (head + SIZE) - tail : head - tail;
}

template <typename T, std::size_t SIZE>
constexpr std::size_t circular_buffer<T, SIZE>::capacity() const noexcept {
    return SIZE - 1;
}

template <typename T, std::size_t SIZE>
const T& circular_buffer<T, SIZE>::at(std::size_t pos) const noexcept(false) {
    if (pos >= len()) {
        throw std::out_of_range("Out of range access to circular_buffer");
    }
    return operator[](pos);
}

template <typename T, std::size_t SIZE>
T& circular_buffer<T, SIZE>::at(std::size_t pos) noexcept(false) {
    if (pos >= len()) {
        throw std::out_of_range("Out of range access to circular_buffer");
    }
    return operator[](pos);
}

template <typename T, std::size_t SIZE>
const T& circular_buffer<T, SIZE>::operator[](std::size_t pos) const noexcept {
    return buffer[capped_mod(tail + pos)];
}

template <typename T, std::size_t SIZE>
T& circular_buffer<T, SIZE>::operator[](std::size_t pos) noexcept {
    return buffer[capped_mod(tail + pos)];
}

template <typename T, std::size_t SIZE>
const T& circular_buffer<T, SIZE>::back() const noexcept {
    return buffer[capped_mod(head + SIZE - 1)];
}

template <typename T, std::size_t SIZE>
T& circular_buffer<T, SIZE>::back() noexcept {
    return buffer[capped_mod(head + SIZE - 1)];
}

template <typename T, std::size_t SIZE>
const T& circular_buffer<T, SIZE>::front() const noexcept {
    return buffer[tail];
}

template <typename T, std::size_t SIZE>
T& circular_buffer<T, SIZE>::front() noexcept {
    return buffer[tail];
}

template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::push_back(const T& item) noexcept {
    buffer[head] = item;
    head = capped_mod(head + 1);
    if (head == tail) {
        tail = capped_mod(tail + 1);
    }
}

template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::push_back(T&& item) noexcept {
    std::swap(buffer[head], item);
    head = capped_mod(head + 1);
    if (head == tail) {
        tail = capped_mod(tail + 1);
    }
}

template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::pop_back() noexcept {
    head = capped_mod(head + SIZE - 1);
}

template <typename T, std::size_t SIZE>
void circular_buffer<T, SIZE>::pop_front() noexcept {
    tail = capped_mod(tail + 1);
}

template <typename T, std::size_t SIZE>
typename circular_buffer<T, SIZE>::iterator circular_buffer<T, SIZE>::begin() noexcept {
    return iterator(*this, tail);
}

template <typename T, std::size_t SIZE>
typename circular_buffer<T, SIZE>::const_iterator circular_buffer<T, SIZE>::begin() const noexcept {
    return const_iterator(*this, tail);
}

template <typename T, std::size_t SIZE>
typename circular_buffer<T, SIZE>::iterator circular_buffer<T, SIZE>::end() noexcept {
    return iterator(*this, head);
}

template <typename T, std::size_t SIZE>
typename circular_buffer<T, SIZE>::const_iterator circular_buffer<T, SIZE>::end() const noexcept {
    return const_iterator(*this, head);
}
