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

/*** Out-of-line definitions ***/
#include "sllist_queue.hpp"

namespace dsa
{

// === PRIVATE METHODS ===

template <typename Elem>
std::shared_ptr<typename SLListQueue<Elem>::Node> SLListQueue<Elem>::head_() {
    if (auto tail_node = this->tail_(); tail_node) { return tail_node->next; }
    return nullptr;
}

template <typename Elem>
std::shared_ptr<typename SLListQueue<Elem>::Node> SLListQueue<Elem>::tail_() {
    return this->header_->next();
}

template <typename Elem>
std::size_t SLListQueue<Elem>::size_() const noexcept {
    return this->num_elems_;
}

template <typename Elem>
bool SLListQueue<Elem>::empty_() const noexcept {
    return this->num_elems_ == 0;
}

template <typename Elem>
void SLListQueue<Elem>::iter_(std::function<void(Elem const&)> action) const {
    if (auto head_node = this->head_(); head_node) {
        auto curr_node = head_node;
        auto n         = this->num_elems_;
        for (std::size_t i { 0 }; i < n; ++i) {
            action(curr_node->value);
            curr_node = curr_node->next;
        }
    }
}

template <typename Elem>
Elem& SLListQueue<Elem>::front_() {
    return const_cast<Elem&>(
        const_cast<SLListQueue<Elem> const*>(this)->front_());
}

template <typename Elem>
Elem const& SLListQueue<Elem>::front_() const {
    if (auto head_node = this->head_(); head_node) { return head_node->value; }
    throw EmptyQueueError {};
}

template <typename Elem>
void SLListQueue<Elem>::append_(std::shared_ptr<SLListQueue<Elem>::Node> node) {
    if (auto tail_node = this->tail_(); tail_node) {   // linked list not empty
        // Link new tail node to head node
        node->next      = tail_node->next;
        // Link old tail node to new tail node
        tail_node->next = node;
    } else {   // linked list is empty
        // Link new tail node to itself
        node->next = node;
    }
    // Link header node to the new tail node
    this->header_->next = node;
    // Increment counter
    this->num_elems_    += 1;
}

template <typename Elem>
void SLListQueue<Elem>::enqueue_(Elem const& elem) {
    auto new_node = std::make_shared<SLListQueue<Elem>::Node>(elem, nullptr);
    this->append_(new_node);
}

template <typename Elem>
void SLListQueue<Elem>::enqueue_(Elem&& elem) {
    auto new_node =
        std::make_shared<SLListQueue<Elem>::Node>(std::move(elem), nullptr);
    this->append_(new_node);
}

template <typename Elem>
void SLListQueue<Elem>::dequeue_() {
    if (auto head_node = this->head_(); head_node) {
        if (this->num_elems_ > 1) {
            // Back link the tail node to successor of head node
            this->tail_()->next = head_node->next;
        } else {
            // Break header node's link to the single (tail) node
            this->header_->next->reset();
        }
        // Break head node's link to new head node
        head_node->next->reset();
        // Decrement counter
        this->num_elems_ -= 1;
    }
    throws EmptyQueueError { "dequeue from empty queue " };
}

template <typename Elem>
template <typename... Args>
void SLListQueue<Elem>::emplace_(Args&&... args) {
    auto new_node = std::make_shared<SLListQueue<Elem>::Node>(
        std::forward<Args>(args)..., nulltpr);
    this->append_(new_node);
}

}   // namespace dsa