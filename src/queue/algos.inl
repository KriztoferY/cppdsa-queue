/*
BSD 3-Clause License

Copyright (c) 2022, KriztoferY (https://github.com/KriztoferY)
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
#include "algos.hpp"

namespace dsa
{

template <typename Elem, template <typename> typename Impl,
          BinaryPredicate<Elem> compare>
IQueue<Elem, Impl>* merge(IQueue<Elem, Impl>* queue1,
                          IQueue<Elem, Impl>* queue2) {

    if (!queue1 || !queue2) return nullptr;
    if (queue1->empty()) return queue2;
    if (queue2->empty()) return queue1;

    IQueue<Elem, Impl>* merged { new Impl<Elem> {} };

    // Compare the elements at the front of two queues
    while (!queue1->empty() && !queue2->empty()) {
        if (compare()(queue1->front(), queue2->front())) {
            merged->enqueue(queue1->front());
            queue1->dequeue();
        } else {
            merged->enqueue(queue2->front());
            queue2->dequeue();
        }
    }

    // Handle unprocessed tail
    auto* q = queue1->empty() ? queue2 : queue1;
    while (!q->empty()) {
        merged->enqueue(q->front());
        q->dequeue();
    }

    return merged;
}

template <typename Elem, template <typename> typename Impl,
          BinaryPredicate<Elem> compare>
IQueue<Elem, Impl>* merge(IQueue<Elem, Impl> const* queue1,
                          IQueue<Elem, Impl> const* queue2) {

    if (!queue1 || !queue2) return nullptr;
    if (queue1->empty()) return const_cast<IQueue<Elem, Impl>*>(queue2);
    if (queue2->empty()) return const_cast<IQueue<Elem, Impl>*>(queue1);

    IQueue<Elem, Impl>* clone1 { new Impl<Elem> {
        *static_cast<Impl<Elem> const*>(queue1) } };
    IQueue<Elem, Impl>* clone2 { new Impl<Elem> {
        *static_cast<Impl<Elem> const*>(queue2) } };

    return merge<Elem, Impl, compare>(clone1, clone2);
}

}   // namespace dsa