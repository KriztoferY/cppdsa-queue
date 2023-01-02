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
 * @file      adt.hpp
 * @brief     Queue ADT
 * @details   Defines the API of the Queue ADT.
 * @author    KriztoferY
 * @version   0.1.0
 * @date      2022.12.08
 * @copyright Copyright (c) 2022 KriztoferY. All rights reserved.
 */

#ifndef ADT_HPP_
#define ADT_HPP_

#include <cstddef>       // size_t
#include <functional>    // function<T>
#include <type_traits>   // remove_const_t<T>
#include <exception>     // exception
#include <string>        // string

/** Top-level namespace for all `cppdsa-*` libraries. */
namespace dsa
{

/**
 * @brief Empty queue error.
 *
 * An exception that indicates an operation on the queue is invalid when the
 * queue is empty.
 */
class EmptyQueueError : public std::exception
{
    std::string msg_;

public:
    /**
     * @brief Constructs a new Empty Queue Error object.
     *
     * @param custom_message A custom message. Defaults to `""`.
     * @note If no custom message is provided, the default error message will
     *      be used.
     */
    EmptyQueueError(std::string custom_message = "")
        : msg_ { custom_message } {}

    const char* what() const noexcept override {
        return msg_.empty() ? default_msg : msg_.c_str();
    }

    /** Default error message */
    static constexpr const char* default_msg =
        "invalid operation on an empty queue";
};

// -----------------------------------------------------------------------------

/**
 * @brief The queue abstract data type (ADT)
 *
 * A sequential ADT that emulates the first-in-first-out behavior of a queue in
 * real world. This class template specifies the API for all implementations of
 * the queue ADT in the `cppdsa-queue` library.
 *
 * @tparam Elem The element type.
 * @tparam Impl The derived implementation class.
 * @note All implementations of the queue ADT must statically inherit this
 *      class template using the Curiously Recurring Template Pattern (CRTP).
 *      The inherited class template must implement the private member
 *      functions `_size()`, `_empty()`, `_iter()`, `_front()`, `_enqueue()`,
 *      `_dequeue()`, and `_emplace<...Args>()` to realize the functionalty
 *      provided by the respective parent class member functions, including all
 *      overloads, unless the client code of the inherited class template will
 *      not require certain operations.
 */
template <typename Elem, template <typename> typename Impl>
class IQueue
{
    // Allow derived impl class to access private ctor
    friend class Impl<Elem>;

public:
    using elem_type = std::remove_const_t<Elem>;

    ~IQueue();

    /** Number of elements in the queue. */
    std::size_t size() const noexcept;

    /** Determines if this queue has no elements. */
    bool empty() const noexcept;

    /**
     * @brief Iterates over all elements of this queue from the front.
     *
     * The given operation will be performed on each element iterated.
     *
     * @param action The operation to be performed on each element.
     */
    void iter(std::function<void(Elem const&)> action) const;

    /**
     * @brief Accesses the element at the front of this queue.
     *
     * @returns The front element.
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem& front();

    /**
     * @brief Accesses (read-only) the element at the front of this queue.
     *
     * @returns The front element (immutable).
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem const& front() const;

    /**
     * @brief Adds an element to the end of this queue.
     *
     * A deep copy of the element will be copy-constructed and then put into
     * the queue.
     *
     * @param elem The element to be added.
     */
    void enqueue(Elem const& elem);

    /**
     * @brief Adds an element to the end of this queue.
     *
     * The element will be put into the queue using move semantics.
     *
     * @param elem The element to be added.
     */
    void enqueue(Elem&& elem);

    /**
     * @brief Removes the element at end of this queue.
     *
     * @throws dsa::EmptyQueueError if this queue is empty.
     */
    void dequeue();

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
     * @note Strictly speaking, this is a convenient member function, and hence
     *      implementations without `_emplace<...Args>()` is still considered
     *      complete with respect to the Queue ADT in theory.
     */
    template <typename... Args>
    void emplace(Args&&... args);

private:
    // Prohibit direct instantiation of IQueue
    IQueue();
    Impl<Elem>*       derived_();
    Impl<Elem> const* derived_() const;
};

/**
 * @brief Destroys a queue on the free store via a pointer.
 *
 * @tparam Elem The element type.
 * @tparam Impl The derived implementation class.
 * @param queue Pointer to a queue on the free store.
 * @note **IMPORTANT** This is the only proper way to destroy a queue via a
 *      base pointer. DO NOT use `delete queue;` in such context, which will
 *      lead to memory leak.
 */
template <typename Elem, template <typename> typename Impl>
void destroy(IQueue<Elem, Impl>* queue);

}   // namespace dsa

#include "adt.inl"

#endif /* ADT_HPP_ */