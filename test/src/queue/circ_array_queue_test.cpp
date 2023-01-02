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

#include <gtest/gtest.h>

#include "circ_array_queue.hpp"

using IntCircArrayQueue = dsa::CircArrayQueue<int>;

/* --- CORNER CASES --- */

// Peek front when empty --> throw
TEST(CircArrayQueueTest, PeekFrontWhenEmptyThrows) {
    auto q = IntCircArrayQueue();
    EXPECT_THROW(q.front(), dsa::EmptyQueueError);
}

// Enqueue when full --> grow array
TEST(CircArrayQueueTest, EnqueueWhenFullRaisesCapacity) {
    auto q = IntCircArrayQueue(2);
    EXPECT_EQ(q.capacity(), 2);
    q.enqueue(3);
    q.enqueue(1);
    EXPECT_EQ(q.capacity(), 2);
    q.enqueue(4);
    EXPECT_EQ(q.capacity(), 4);
    q.enqueue(1);
    EXPECT_EQ(q.capacity(), 4);
    q.enqueue(5);
    EXPECT_EQ(q.capacity(), 8);
    q.enqueue(9);
    q.enqueue(2);
    q.enqueue(6);
    EXPECT_EQ(q.capacity(), 8);
    q.enqueue(5);
    EXPECT_EQ(q.capacity(), 16);
}

// Dequeue when empty --> throw
TEST(CircArrayQueueTest, DequeueWhenEmptyThrows) {
    auto q = IntCircArrayQueue();
    EXPECT_THROW(q.dequeue(), dsa::EmptyQueueError);
}

// Dequeue when just a quarter full --> shrink array
TEST(CircArrayQueueTest, DequeueWhenQuarterFullReducesCapcity) {
    // capacity > 2 : will shrink array
    auto q = IntCircArrayQueue(8);
    q.enqueue(3);
    q.enqueue(1);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.capacity(), 8);
    q.dequeue();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.capacity(), 4);

    // capacity = 2 : won't shrink array
    q = IntCircArrayQueue(2);
    q.enqueue(3);
    q.enqueue(1);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.capacity(), 2);
    q.dequeue();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.capacity(), 2);

    // capacity = 1 : won't shrink array
    q = IntCircArrayQueue(1);
    q.enqueue(3);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.capacity(), 1);
    q.dequeue();
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), 1);
}

/* --- REGULAR CASES --- */

// Enqueue, peek, dequeue idiom (along with empty, size, capacity)
TEST(CircArrayQueueTest, EnqueuePeekDeqeueIdiomWorks) {
    std::size_t init_cap { 8 };
    auto        q = IntCircArrayQueue(init_cap);
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), init_cap);

    constexpr std::size_t init_sz { 4 };
    constexpr int         nums[init_sz] { 3, 1, 4, 1 };
    int                   i { 0 };
    for (auto num : nums) {
        q.enqueue(num);
        EXPECT_FALSE(q.empty());
        EXPECT_EQ(q.size(), ++i);
        EXPECT_EQ(q.capacity(), init_cap);
    }
    // now i = 4 (q.size)

    while (!q.empty()) {
        int num { 0 };
        EXPECT_NO_THROW(num = q.front());
        EXPECT_EQ(num, nums[init_sz - i]);
        EXPECT_GT(q.capacity(), 0);
        EXPECT_EQ(q.size(), i);
        EXPECT_NO_THROW(q.dequeue());
        EXPECT_GT(q.capacity(), 0);
        EXPECT_EQ(q.size(), --i);
    }
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_GT(q.capacity(), 0);
}

// Non-const front
TEST(CircArrayQueueTest, NonconstFrontReturnValueIsMutable) {
    auto q = IntCircArrayQueue(8);
    q.enqueue(3);
    q.enqueue(1);
    q.enqueue(4);
    auto& elem = q.front();
    EXPECT_EQ(elem, 3);
    elem = 2;
    EXPECT_EQ(q.front(), 2);
}