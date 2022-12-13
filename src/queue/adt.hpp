/**
 *  @file      adt.hpp
 *  @brief     Queue ADT
 *  @details   Defines the API of the Queue ADT.
 *  @author    KriztoferY
 *  @version   0.1.0
 *  @date      2022.12.08
 *  @copyright Copyright (c) 2022 KriztoferY. All rights reserved.
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
     * @brief Construct a new Empty Queue Error object.
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
 *      `_dequeue()`, and `_emplace<...Args>()` for the respective parent class
 *      member functions, including all overloads, unless the client code of
 *      the inherited class template will not require certain operations.
 */
template <typename Elem, template <typename> typename Impl>
class IQueue
{
    // Allow derived impl class to access private ctor
    friend class Impl<Elem>;

public:
    using elem_type = std::remove_const_t<Elem>;

    virtual ~IQueue();

    /** Number of elements in the queue. */
    std::size_t size() const noexcept;

    /** Determine if this queue has no elements. */
    bool        empty() const noexcept;

    /**
     * @brief Iterate over all elements of this queue from the front.
     *
     * The given operation will be performed on each element iterated.
     *
     * @param action The operation to be performed on each element.
     */
    void        iter(std::function<void(Elem const&)> action) const;

    /**
     * @brief Access the element at the front of this queue.
     *
     * @returns The front element.
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem&       front();

    /**
     * @brief Access (read-only) the element at the front of this queue.
     *
     * @returns The front element (immutable).
     * @throws dsa::EmptyQueueError if the queue is empty.
     */
    Elem const& front() const;

    /**
     * @brief Add an element to the end of this queue.
     *
     * A deep copy of the element will be copy-constructed and then put into
     * the queue.
     *
     * @param elem The element to be added.
     */
    void        enqueue(Elem const& elem);

    /**
     * @brief Add an element to the end of this queue.
     *
     * The element will be put into the queue using move semantics.
     *
     * @param elem The element to be added.
     */
    void        enqueue(Elem&& elem);

    /**
     * @brief Remove the element at end of this queue.
     *
     * @throws dsa::EmptyQueueError if this queue is empty.
     */
    void        dequeue();

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
    const Impl<Elem>* derived_() const;
};

}   // namespace dsa

#include "adt.inl"

#endif /* ADT_HPP_ */