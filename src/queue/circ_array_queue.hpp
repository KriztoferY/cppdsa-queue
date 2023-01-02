/*
BSD 3-Clause License

Copyright (c) 2022, KriztoferY <https://github.com/KriztoferY>
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
 * @file      circ_array_queue.hpp
 * @brief     Circular Array Queue
 * @details   Unbounded generic queue -- an implementation of the Queue ADT
 *            using a circular array with a dynamic resizing scheme
 * @author    KriztoferY
 * @version   0.1.0
 * @date      2022.12.08
 * @copyright Copyright (c) 2022 KriztoferY. All rights reserved.
 */

#ifndef CIRC_ARRAY_QUEUE_HPP_
#define CIRC_ARRAY_QUEUE_HPP_

#include <cstddef>   // size_t
#include <cstdint>   // uint8_t
#include <memory>    // unique_ptr<T>

#include "adt.hpp"   // IQueue<Elem, Impl>

/** Top-level namespace for all `cppdsa-*` libraries. */
namespace dsa
{

/**
 * @brief Circular array queue.
 *
 * An unbounded, generic queue that implements the Queue ADT
 * `dsa::IQueue<Elem>` using a circular array along with a dynamic resizing
 * scheme. This class template statically inherits the Queue ADT template class
 * using the Curiously Recurring Template Pattern (CRTP).
 *
 * @tparam Elem The queue element type.
 * @note The queue has value semantics.
 */
template <typename Elem>
class CircArrayQueue : public IQueue<Elem, CircArrayQueue>
{
    // Parent class, which is allowed to access the private impl methods
    friend class IQueue<Elem, CircArrayQueue>;

public:
    /**
     * @brief Creates an empty queue.
     *
     * @param init_cap The initially anticipated maximum number of elements to
     *      be store in the queue.
     * @note Memory will be allocated according to `init_cap` and the element
     *      type `Elem`.
     */
    CircArrayQueue(std::size_t init_cap = 4096);
    ~CircArrayQueue();

    /** Copy-constructs a new queue from an existing queue. */
    CircArrayQueue(CircArrayQueue const&);
    /** Move-constructs a new queue from an existing queue. */
    CircArrayQueue(CircArrayQueue&&) noexcept;

    /** Copy-assigns an existing queue to this queue. */
    CircArrayQueue& operator=(CircArrayQueue const&);
    /** Move-assigns an existing queue to this queue. */
    CircArrayQueue& operator=(CircArrayQueue&&) noexcept;

    /**
     * @brief Maximum number of elements this queue can store without allocating
     * additional memory.
     *
     * @return The maximum number.
     */
    std::size_t capacity() const noexcept;

private:
    std::unique_ptr<Elem[]> elems_;
    std::size_t             capacity_;
    std::size_t             start_idx_ { 0 };
    std::size_t             num_elems_ { 0 };

    std::size_t end_idx_() const noexcept;
    void        resize_(std::int8_t);

    /** Number of elements in the queue. */
    std::size_t size_() const noexcept;

    /** Determines if this queue has no elements. */
    bool empty_() const noexcept;

    /**
     * @brief Iterates over all elements of this queue from the front.
     *
     * The given operation will be performed on each element iterated.
     *
     * @param action The operation to be performed on each element.
     */
    void iter_(std::function<void(Elem const&)>) const;

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

    /**
     * @brief Adds an element to the end of this queue.
     *
     * A deep copy of the element will be copy-constructed and then put into
     * the queue.
     *
     * @note Additional memory will be allocated prior to this operation if the
     *      number of elements of this queue exceeds the current capacity.
     */
    void enqueue_(Elem const& elem);

    /**
     * @brief Adds an element to the end of this queue.
     *
     * The element will be put into the queue using move semantics.
     *
     * @param elem The element to be added.
     * @note Additional memory will be allocated prior to this operation if the
     *      number of elements of this queue exceeds the current capacity.
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
     * @note Additional memory will be allocated prior to this operation if the
     *      number of elements of this queue exceeds the current capacity.
     */
    template <typename... Args>
    void emplace_(Args&&... args);
};

}   // namespace dsa

#include "circ_array_queue.inl"

#endif /* CIRC_ARRAY_QUEUE_HPP_ */