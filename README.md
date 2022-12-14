# cppdsa-queue

A modern C++ (header-only) library that provides generic implementations of the Queue ADT and related algorithms.

```cpp
#include <iostream>                 // cout, endl
#include "circ_array_queue.hpp"     // CircArrayQueue<Elem>

int main() {
    auto q = dsa::CircArrayQueue<int> {};
    q.enqueue(3);
    q.enqueue(1);
    ...
    while (!q.empty()) {
        std::cout << q.front() << ' ';
        q.dequeue();
    }
    std::cout << endl;
    ...
    return 0;
}
```

It supports static (compile-time) polymorphism and is extensible by means of template programming.
