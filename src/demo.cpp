#include <cstdlib>    // EXIT_*
#include <iostream>   // cout
#include <string>     // stoull()
#include <numbers>    // numbers

#include "circ_array_queue.hpp"
#include "ProjectConfig.h"

using namespace std;

void print_usage(const string& executable) {
    std::cout << executable << " Version " << CppdsaQueue_VERSION_MAJOR << "."
              << CppdsaQueue_VERSION_MINOR << "." << CppdsaQueue_VERSION_PATCH
              << std::endl;
    std::cout << "USAGE: " << executable << " <num_elems>" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    if (argc != 2) print_usage(argv[0]);

    try {
        auto num_elems = std::stoull(argv[1]);
        auto x         = std::numbers::pi;

        auto q         = dsa::CircArrayQueue<std::size_t> { 2 };

        cout << "Queuing up the first " << num_elems
             << " significant digits of pi...\n\n";

        cout << "queue (q) created :: size: " << q.size()
             << " | cap: " << q.capacity() << "\n\n";

        try {
            cout << "Cannot peek the front element of the queue when empty\n";
            q.front();
        }
        catch (const dsa::EmptyQueueError& e) {
            cerr << "EmptyQueueError: " << e.what() << "\n\n";
        }

        for (std::size_t i { 0 }; i < num_elems; ++i) {
            auto elem = static_cast<std::size_t>(x) % 10;
            x         *= 10;

            cout << "q.enqueue(" << elem << ") :: ";
            q.enqueue(elem);
            cout << "front: " << q.front() << " | size: " << q.size()
                 << " | cap: " << q.capacity() << endl;
        }
        cout << endl;

        cout << "q.iter() ::\n";
        std::size_t i { 0 };
        q.iter([&i](auto const& x) {
            cout << "q.elems_[" << i << "]: " << x << endl;
            ++i;
        });
        cout << endl;

        while (!q.empty()) {
            cout << "front: " << q.front() << " | size: " << q.size()
                 << " | cap: " << q.capacity() << " -- q.dequeue()\n";
            q.dequeue();
        }
        cout << "\nsize: " << q.size() << " | cap: " << q.capacity() << endl;

        q.dequeue();   // throw EmptyQueueError

        return EXIT_SUCCESS;
    }
    catch (const dsa::EmptyQueueError& e) {
        cerr << "EmptyQueueError: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        cerr << "Uncaught exception: " << e.what() << '\n';
    }

    return EXIT_FAILURE;
}

// -----------------------------------------------------------------------------

/* === COMPILE & RUN ===
g++ demo.cpp -o demo -std=c++20 -g -Og -Wall -pedantic -march=native && ./demo 6
g++ demo.cpp -o demo -std=c++20 -O3 -march=native -DNDEBUG && ./demo 6
*/

/* === SAMPLE OUTPUT ===
Queuing up the first 6 significant digits of pi...

queue (q) created :: size: 0 | cap: 2

Cannot peek the front element of the queue when empty
EmptyQueueError: invalid operation on an empty queue

q.enqueue(3) :: front: 3 | size: 1 | cap: 2
q.enqueue(1) :: front: 3 | size: 2 | cap: 2
q.enqueue(4) :: front: 3 | size: 3 | cap: 4
q.enqueue(1) :: front: 3 | size: 4 | cap: 4
q.enqueue(5) :: front: 3 | size: 5 | cap: 8
q.enqueue(9) :: front: 3 | size: 6 | cap: 8

q.iter() ::
q.elems_[0]: 3
q.elems_[1]: 1
q.elems_[2]: 4
q.elems_[3]: 1
q.elems_[4]: 5
q.elems_[5]: 9

front: 3 | size: 6 | cap: 8 -- q.dequeue()
front: 1 | size: 5 | cap: 8 -- q.dequeue()
front: 4 | size: 4 | cap: 8 -- q.dequeue()
front: 1 | size: 3 | cap: 8 -- q.dequeue()
front: 5 | size: 2 | cap: 8 -- q.dequeue()
front: 9 | size: 1 | cap: 4 -- q.dequeue()

size: 0 | cap: 2
EmptyQueueError: dequeue from empty queue
*/