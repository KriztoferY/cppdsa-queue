/*** Inline definitions ***/
#include "circ_array_queue.hpp"

namespace dsa
{

// === PUBLIC METHODS ===

template <typename Elem>
CircArrayQueue<Elem>::CircArrayQueue(std::size_t init_cap)
    : elems_ { new Elem[init_cap] }, capacity_ { init_cap } {}

template <typename Elem>
CircArrayQueue<Elem>::~CircArrayQueue() {
    delete[] elems_;
}

// clang-format off

template <typename Elem>
CircArrayQueue<Elem>::CircArrayQueue(CircArrayQueue const& other)
    : elems_ { new Elem[other.capacity_] },
      capacity_ { other.capacity_ },
      num_elems_ { other.num_elems_ }
{
    for (std::size_t i { 0 }; i < other.num_elems_; ++i) 
        elems_[i] = other.elems_[i];
}

template <typename Elem>
CircArrayQueue<Elem>::CircArrayQueue(CircArrayQueue&& other)
    : elems_ { other.elems_ }, 
      capacity_ { other.capacity_ },
      start_idx_ { other.start_idx_ }, 
      num_elems_ { other.num_elems_ } 
{
    other.elems_ = nullptr;
    other.capacity_ = 0;
    other.start_idx_ = 0;
    other.num_elems_ = 0;
}

// clang-format on

template <typename Elem>
CircArrayQueue<Elem>&
    CircArrayQueue<Elem>::operator=(CircArrayQueue const& other) {
    delete[] elems_;
    elems_     = new Elem[other.capacity_];
    capacity_  = other.capacity_;
    start_idx_ = other.start_idx_;
    num_elems_ = other.num_elems_;
    return *this;
}

template <typename Elem>
CircArrayQueue<Elem>& CircArrayQueue<Elem>::operator=(CircArrayQueue&& other) {
    delete[] elems_;
    elems_           = other.elems_;
    capacity_        = other.capacity_;
    start_idx_       = other.start_idx_;
    num_elems_       = other.num_elems_;

    other.elems_     = nullptr;
    other.capacity_  = 0;
    other.start_idx_ = 0;
    other.num_elems_ = 0;

    return *this;
}

template <typename Elem>
std::size_t CircArrayQueue<Elem>::capacity() const noexcept {
    return capacity_;
}

// === PRIVATE METHODS ===

template <typename Elem>
std::size_t CircArrayQueue<Elem>::end_idx_() const noexcept {
    return (start_idx_ + num_elems_) % capacity_;
}

template <typename Elem>
std::size_t CircArrayQueue<Elem>::size_() const noexcept {
    return num_elems_;
}

template <typename Elem>
bool CircArrayQueue<Elem>::empty_() const noexcept {
    return num_elems_ == 0;
}

template <typename Elem>
void CircArrayQueue<Elem>::iter_(std::function<void(Elem const&)> visit) const {
    for (std::size_t i { 0 }; i < num_elems_; ++i) {
        visit(elems_[(start_idx_ + i) % capacity_]);
    }
}

template <typename Elem>
Elem const& CircArrayQueue<Elem>::front_() const {
    if (num_elems_ == 0) throw EmptyQueueError {};
    return elems_[start_idx_];
}

template <typename Elem>
void CircArrayQueue<Elem>::resize_(std::int8_t factor) {
    std::size_t new_cap { 0 };
    if (factor > 0 && num_elems_ == capacity_) {
        new_cap = capacity_ * 2;
    } else if (factor < 0 && capacity_ >= 2 && num_elems_ * 4 < capacity_) {
        new_cap = capacity_ / 2;
    }

    if (new_cap > 0) {
        auto arr = new Elem[new_cap];
        for (std::size_t i { 0 }; i < num_elems_; ++i) {
            arr[i] = elems_[(start_idx_ + i) % capacity_];
        }
        delete[] elems_;
        elems_     = arr;
        capacity_  = new_cap;
        start_idx_ = 0;
    }
}

template <typename Elem>
void CircArrayQueue<Elem>::enqueue_(Elem const& elem) {
    resize_(1);
    elems_[end_idx_()] = elem;
    num_elems_         += 1;
}

template <typename Elem>
void CircArrayQueue<Elem>::enqueue_(Elem&& elem) {
    resize_(1);
    elems_[end_idx_()] = std::move(elem);
    num_elems_         += 1;
}

template <typename Elem>
void CircArrayQueue<Elem>::dequeue_() {
    if (num_elems_ == 0) throw EmptyQueueError { "dequeue from empty queue" };
    start_idx_ = (start_idx_ + 1) % capacity_;
    num_elems_ -= 1;
    resize_(-1);
}

template <typename Elem>
template <typename... Args>
void CircArrayQueue<Elem>::emplace_(Args&&... args) {
    resize_(1);
    elems_[end_idx_()] = Elem { std::forward<Args>(args)... };
    num_elems_         += 1;
}

}   // namespace dsa