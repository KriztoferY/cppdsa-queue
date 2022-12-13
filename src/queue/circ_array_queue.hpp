/**
 *  @file      circ_array_queue.hpp
 *  @brief     Circular Array Queue
 *  @details   Unbounded generic queue -- an implementation of the Queue ADT
 *             using a circular array with a dynamic resizing scheme
 *  @author    KriztoferY
 *  @version   0.1.0
 *  @date      2022.12.08
 *  @copyright Copyright (c) 2022 KriztoferY. All rights reserved.
 */

#ifndef CIRC_ARRAY_QUEUE_HPP_
#define CIRC_ARRAY_QUEUE_HPP_

#include <cstddef>   // size_t
#include <cstdint>   // uint8_t

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
     * @brief Create an empty queue.
     *
     * @param init_cap The initially anticipated maximum number of elements to
     *      be store in the queue.
     * @note Memory will be allocated according to `init_cap` and the element
     *      type `Elem`.
     */
    CircArrayQueue(std::size_t init_cap = 4096);
    ~CircArrayQueue();

    /** Copy-construct a new queue from an existing queue. */
    CircArrayQueue(CircArrayQueue const&);
    /** Move-construct a new queue from an existing queue. */
    CircArrayQueue(CircArrayQueue&&);

    /** Copy-assign an existing queue to this queue. */
    CircArrayQueue& operator=(CircArrayQueue const&);
    /** Move-assign an existing queue to this queue. */
    CircArrayQueue& operator=(CircArrayQueue&&);

    /**
     * @brief Maximum number of elements this queue can store without allocating
     * additional memory.
     *
     * @return The maximum number.
     */
    std::size_t     capacity() const noexcept;

private:
    Elem*       elems_;
    std::size_t capacity_;
    std::size_t start_idx_ { 0 };
    std::size_t num_elems_ { 0 };

    std::size_t end_idx_() const noexcept;
    void        resize_(std::int8_t);

    /** Number of elements in the queue. */
    std::size_t size_() const noexcept;

    /** Determine if this queue has no elements. */
    bool        empty_() const noexcept;

    /**
     * @brief Iterate over all elements of this queue from the front.
     *
     * The given operation will be performed on each element iterated.
     *
     * @param action The operation to be performed on each element.
     */
    void        iter_(std::function<void(Elem const&)>) const;

    /**
     * @brief Access the element at the front of this queue.
     *
     * @returns The front element.
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem&       front_();

    /**
     * @brief Access (read-only) the element at the front of this queue.
     *
     * @returns The front element (immutable).
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem const& front_() const;

    /**
     * @brief Add an element to the end of this queue.
     *
     * A deep copy of the element will be copy-constructed and then put into
     * the queue.
     *
     * @note Additional memory will be allocated prior to this operation if the
     *      number of elements of this queue exceeds the current capacity.
     */
    void        enqueue_(Elem const& elem);

    /**
     * @brief Add an element to the end of this queue.
     *
     * The element will be put into the queue using move semantics.
     *
     * @param elem The element to be added.
     * @note Additional memory will be allocated prior to this operation if the
     *      number of elements of this queue exceeds the current capacity.
     */
    void        enqueue_(Elem&& elem);

    /**
     * @brief Remove the element at end of this queue.
     *
     * @throws dsa::EmptyQueueError if this queue is empty.
     * @note Removing an element will trigger memory deallocation (and
     *      re-allocation of half the size) only when the number of elements in
     *      this queue is a quarter of the current capacity.
     */
    void        dequeue_();

    /**
     * @brief Create a new element in-place after the last element of this
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