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
        int num;
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
