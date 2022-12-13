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

}   // namespace dsa