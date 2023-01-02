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

/*** Inline definitions ***/
#include "adt.hpp"

namespace dsa
{

// === PUBLIC METHODS ===

template <typename Elem, template <typename> typename Impl>
IQueue<Elem, Impl>::~IQueue() {
    /* Do nothing. */
}

template <typename Elem, template <typename> typename Impl>
std::size_t IQueue<Elem, Impl>::size() const noexcept {
    return derived_()->size_();
}

template <typename Elem, template <typename> typename Impl>
bool IQueue<Elem, Impl>::empty() const noexcept {
    return derived_()->empty_();
}

template <typename Elem, template <typename> typename Impl>
void IQueue<Elem, Impl>::iter(std::function<void(Elem const&)> action) const {
    derived_()->iter_(action);
}

template <typename Elem, template <typename> typename Impl>
Elem& IQueue<Elem, Impl>::front() {
    return derived_()->front_();
}

template <typename Elem, template <typename> typename Impl>
Elem const& IQueue<Elem, Impl>::front() const {
    return derived_()->front_();
}

template <typename Elem, template <typename> typename Impl>
void IQueue<Elem, Impl>::enqueue(Elem const& elem) {
    derived_()->enqueue_(elem);
}

template <typename Elem, template <typename> typename Impl>
void IQueue<Elem, Impl>::enqueue(Elem&& elem) {
    derived_()->enqueue_(std::move(elem));
}

template <typename Elem, template <typename> typename Impl>
void IQueue<Elem, Impl>::dequeue() {
    derived_()->dequeue_();
}

template <typename Elem, template <typename> typename Impl>
template <typename... Args>
void IQueue<Elem, Impl>::emplace(Args&&... args) {
    derived_()->emplace_(std::forward<Args>(args)...);
}

// === PRIVATE METHODS ===

template <typename Elem, template <typename> typename Impl>
IQueue<Elem, Impl>::IQueue() {
    /* Do nothing. */
}

template <typename Elem, template <typename> typename Impl>
Impl<Elem>* IQueue<Elem, Impl>::derived_() {
    return static_cast<Impl<Elem>*>(this);
}

template <typename Elem, template <typename> typename Impl>
const Impl<Elem>* IQueue<Elem, Impl>::derived_() const {
    return static_cast<Impl<Elem> const*>(this);
}

// === FREE FUNCTIONS ====

template <typename Elem, template <typename> typename Impl>
void destroy(IQueue<Elem, Impl>* queue) {
    if (queue) delete static_cast<Impl<Elem>*>(queue);
}

}   // namespace dsa