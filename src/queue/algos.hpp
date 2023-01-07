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
 * @file      algos.hpp
 * @brief     Algorithms on the Queue ADT.
 * @author    KriztoferY
 * @version   0.1.0
 * @date      2023.01.02
 * @copyright Copyright (c) 2023 KriztoferY. All rights reserved.
 */

#ifndef QUEUE_ALGOS_HPP
#define QUEUE_ALGOS_HPP

#include <concepts>
#include <type_traits>

#include "adt.hpp"   // IQueue<Elem, Impl>

namespace dsa
{

/**
 * @brief Specifies that the type `T` is a callable type that, when called,
 *       behaves as a binary predicate that accepts two instances of type `Arg`.
 *
 * @tparam T The type to test.
 * @tparam Arg The argument type of the binary predicate.
 */
template <typename T, typename Arg>
concept BinaryPredicate = requires (T t, Arg a, Arg b) {
                              { t(a, b) } -> std::same_as<bool>;
                          };

/**
 * @brief Stable-merges two queues.
 *
 * Elements are compared using the @ref dsa::BinaryPredicate `compare` to
 * determine the order in which they appear in the merged queue. Relative order
 * of elements in the original queues are preserved. A new queue is created and
 * returned if both queues to merge are not empty.
 *
 * @tparam Elem Type of each element in the queue.
 * @tparam Impl The derived implementation class of the Queue ADT of which the
 *       two queues to merge are.
 * @tparam compare A callable object that determines the element order in the
 *       merged queue; it has not effect on the relative order of elements in
 *       the original queues. The signature of an equivalent function reads
 *       `bool (Elem const&, Elem const&)`, i.e. it must satisfy the @ref
 *       dsa::BinaryPredicate concept.
 * @param queue1 A queue to merge.
 * @param queue2 Another queue to merge.
 * @return The merged queue if both queues to merge are not empty, one of the
 *       queues to merge if the other is empty, `nullptr` if both are empty.
 *       **[IMPORTANT]** In the first case, call @ref dsa::destroy when you're
 *       done with the merged queue to free the memory allocated to it.
 * @note The complexity of the merge algorithm is `O(n1 + n2)` in both time and
 *      space, where `n1` and `n2` are the sizes of the two queues to merge.
 */
template <typename Elem, template <typename> typename Impl,
          BinaryPredicate<Elem> compare>
IQueue<Elem, Impl>* merge(IQueue<Elem, Impl>* queue1,
                          IQueue<Elem, Impl>* queue2);

}   // namespace dsa

#include "algos.inl"

#endif /* QUEUE_ALGOS_HPP */