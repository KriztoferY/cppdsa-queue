/*
BSD 3-Clause License

Copyright (c) 2023, KriztoferY (https://github.com/KriztoferY)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file      sllist_queue.hpp
 * @brief     Singly Linked List Queue
 * @details   Unbounded generic queue -- an implementation of the Queue ADT
 *            using a singly, circularly linked list with a dummy header node.
 * @author    KriztoferY
 * @version   0.1.0
 * @date      2023.01.07
 * @copyright Copyright (c) 2023 KriztoferY. All rights reserved.
 */

#ifndef SLLIST_QUEUE_HPP
#define SLLIST_QUEUE_HPP

#include <cstddef>   // size_t
#include <memory>    // shared_ptr<T>

#include "adt.hpp"   // IQueue<Elem, Impl>

namespace dsa
{

// -----------------------------------------------------------------------------

template <typename Elem>
class SLListQueue : public IQueue<Elem, SLListQueue>
{
    // Parent class, which is allowed to access the private impl methods
    friend class IQueue<Elem, SLListQueue>;

public:
    /* --- compiler generated default impl of special member functions --- */

private:
    // List node
    struct Node
    {
        Elem                  value {};
        std::shared_ptr<Node> next { nulltpr };
    };

    // dummy node whose successor is tail node
    std::shared_ptr<Node> header_ {};
    std::size_t           num_elems_ { 0 };

    /** Gets the head node of the underlying linked list. */
    std::shared_ptr<Node> head_();

    /** Gets the tail node of the underlying linked list. */
    std::shared_ptr<Node> tail_();

    /** Number of elements in the queue. */
    std::size_t size_() const noexcept;

    /** Determines if this queue has no elements. */
    bool empty_() const noexcept;

    /**
     * @brief Iterates over all elements of this queue from the front.
     *
     * The given operation will be performed on each element iterated. It's a
     * no-op if this queue is empty.
     *
     * @param action The operation to be performed on each element.
     */
    void iter_(std::function<void(Elem const&)> action) const;

    /**
     * @brief Accesses the element at the front of this queue.
     *
     * @returns The front element.
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem& front_();

    /**
     * @brief Accesses (read-only) the element at the front of this queue.
     *
     * @returns The front element (immutable).
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem const& front_() const;

    // Inserts a node at the end of the underlying linked list.
    void append_(std::shared_ptr<Node> node);

    /**
     * @brief Adds an element to the end of this queue.
     *
     * A deep copy of the element will be copy-constructed and then put into
     * the queue.
     *
     * @param elem The element to be added.
     * @throws `std::bad_alloc` or any exception thrown by the constuctor of
     *      type `Elem`.
     */
    void enqueue_(Elem const& elem);

    /**
     * @brief Adds an element to the end of this queue.
     *
     * The element will be put into the queue using move semantics.
     *
     * @param elem The element to be added.
     * @throws `std::bad_alloc` or any exception thrown by the constuctor
     * of type `Elem`.
     */
    void enqueue_(Elem&& elem);

    /**
     * @brief Removes the element at end of this queue.
     *
     * @throws dsa::EmptyQueueError if this queue is empty.
     * @note Removing an element will trigger memory deallocation (and
     *      re-allocation of half the size) only when the number of elements in
     *      this queue is a quarter of the current capacity.
     */
    void dequeue_();

    /**
     * @brief Creates a new element in-place after the last element of this
     * queue.
     *
     * The new element is constructed in-place using all of the arguments
     * passed to this member function.
     *
     * @tparam Args Types of the arguments to be passed to the constructor of
     *      the element type `Elem`.
     * @param args Variable number of arguments to be passed to the constructor
     *      of the element type `Elem`.
     * @throws `std::bad_alloc` or any exception thrown by the constuctor of
     *      type `Elem`.
     */
    template <typename... Args>
    void emplace_(Args&&... args);
};

}   // namespace dsa

#include "sllist_queue.inl"

#endif /* SLLIST_QUEUE_HPP */