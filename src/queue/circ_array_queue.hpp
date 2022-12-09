/**
 *  \file      circ_array_queue.hpp
 *  \brief     Circular Array Queue
 *  \details   Unbounded generic queue -- an implementation of the Queue ADT
 *             using a circular array with a dynamic resizing scheme
 *  \author    KriztoferY
 *  \version   1.0.0
 *  \date      2022.12.08
 *  \copyright Copyright (c) 2022 KriztoferY. All rights reserved.
 */

#ifndef CIRC_ARRAY_QUEUE_HPP_
#define CIRC_ARRAY_QUEUE_HPP_

#include <cstddef>   // size_t
#include <cstdint>   // uint8_t

#include "adt.hpp"   // IQueue<Elem, Impl>

namespace dsa
{

template <typename Elem>
class CircArrayQueue : public IQueue<Elem, CircArrayQueue>
{
    // Parent class, which is allowed to access the private impl methods
    friend class IQueue<Elem, CircArrayQueue>;

public:
    CircArrayQueue(std::size_t init_cap = 4'096);
    ~CircArrayQueue();

    CircArrayQueue(CircArrayQueue const&);
    CircArrayQueue(CircArrayQueue&&);

    CircArrayQueue& operator=(CircArrayQueue const&);
    CircArrayQueue& operator=(CircArrayQueue&&);

    std::size_t     capacity() const noexcept;

private:
    Elem*       elems_;
    std::size_t capacity_;
    std::size_t start_idx_ { 0 };
    std::size_t num_elems_ { 0 };

    std::size_t end_idx_() const noexcept;
    void        resize_(std::int8_t);

    std::size_t size_() const noexcept;
    bool        empty_() const noexcept;
    void        iter_(std::function<void(Elem const&)>) const;
    Elem const& front_() const;

    void        enqueue_(Elem const& elem);
    void        enqueue_(Elem&& elem);
    void        dequeue_();

    template <typename... Args>
    void emplace_(Args&&... args);
};

}   // namespace dsa

#include "circ_array_queue.inl"

#endif /* CIRC_ARRAY_QUEUE_HPP_ */