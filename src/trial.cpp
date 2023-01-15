/**
 *
 * ---
 * Ref:
 */

// === /devbox/projects/c++/cppdsa-queue/src/trial.cpp ===

#include <iostream>   // cout

#include "trial.hpp"

using namespace std;
// using namespace dsa;

int main(int argc, char** argv) {

    auto lst = List<int> {};
    lst.foo(42);
    // cout << lst.first() << endl;

    return 0;
}

// -----------------------------------------------------------------------------

/* === COMPILE & RUN ===
g++ trial.cpp -std=c++20 -g -Og -Wall -pedantic -march=native && ./a.out
g++ trial.cpp -std=c++20 -O3 -march=native -DNDEBUG && ./a.out
*/

/* === OUTPUT ===

*/