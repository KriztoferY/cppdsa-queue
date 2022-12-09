/**
 *  \file      adt.hpp
 *  \brief     Queue ADT
 *  \details   Defines the API of the Queue ADT.
 *  \author    KriztoferY
 *  \version   1.0.0
 *  \date      2022.12.08
 *  \copyright Copyright (c) 2022 KriztoferY. All rights reserved.
 */

#ifndef ADT_HPP_
#define ADT_HPP_

#include <cstddef>       // size_t
#include <functional>    // function<T>
#include <type_traits>   // remove_const_t<T>
#include <exception>     // exception
#include <string>        // string

namespace dsa
{

class EmptyQueueError : public std::exception
{
    static constexpr const char* default_msg_ =
        "invalid operation on an empty queue";
    std::string msg_;

public:
    EmptyQueueError(std::string custom_message = "")
        : msg_ { custom_message } {}

    const char* what() const noexcept override {
        return msg_.empty() ? default_msg_ : msg_.c_str();
    }
};

// -----------------------------------------------------------------------------

template <typename Elem, template <typename> typename Impl>
class IQueue
{
    // Allow derived impl class to access private ctor
    friend class Impl<Elem>;

public:
    using elem_type = std::remove_const_t<Elem>;

    virtual ~IQueue();

    std::size_t size() const noexcept;
    bool        empty() const noexcept;
    void        iter(std::function<void(Elem const&)>) const;
    Elem const& front() const;

    void        enqueue(Elem const& elem);
    void        enqueue(Elem&& elem);
    void        dequeue();

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