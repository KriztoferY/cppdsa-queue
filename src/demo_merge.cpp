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

#include <cstdlib>    // EXIT_*
#include <iostream>   // cout, ostream
#include <string>     // string

#include "circ_array_queue.hpp"   // CircArrayQueue<T>
#include "algos.hpp"              // merge<...>()

struct Job
{
    unsigned int time_id;
    unsigned int priority { 0 };
    std::string  name { "unnamed" };
};

struct
{
    /**
     * @brief Compares two jobs based on time ID, followed by priority.
     *
     * @param j1 A job to compare.
     * @param j2 Another job to compare.
     * @return `true` if `j1` should appear before `j2` when jobs are sorted in
     *      ascending order, `false` otherwise.
     * @return false
     */
    bool operator()(Job const& j1, Job const& j2) const {
        if (j1.time_id == j2.time_id) return j1.priority > j2.priority;
        return j1.time_id < j2.time_id;
    }
} compare_jobs;

std::ostream& operator<<(std::ostream& os, Job const& job) {
    return os << "Job(name=" << job.name << ", time_id=" << job.time_id
              << ", priority=" << job.priority << ")";
}

int main(int argc, char** argv) {
    using namespace std;
    using JobQueue = dsa::CircArrayQueue<Job>;

    try {
        dsa::IQueue<Job, dsa::CircArrayQueue>* q1 { new JobQueue {} };

        Job jobs1[] {
            { 2, 1, "M" }, { 3, 0, "E" }, { 5, 2, "Q" }, { 9, 1, "A" }
        };
        for (auto const& job : jobs1) q1->enqueue(job);

        cout << q1->to_string("q1", "\n") << endl << endl;

        dsa::IQueue<Job, dsa::CircArrayQueue>* q2 { new JobQueue {} };

        Job jobs2[] { { 1, 0, "D" }, { 4, 0, "T" }, { 5, 1, "V" },
                      { 7, 0, "B" }, { 8, 1, "H" }, { 10, 1, "R" } };
        for (auto const& job : jobs2) q2->enqueue(job);

        cout << q2->to_string("q2", "\n") << endl << endl;

        auto* q = dsa::merge<Job, dsa::CircArrayQueue, decltype(compare_jobs)>(
            q1, q2);

        cout << "Merging..." << endl;
        cout << q->to_string("q", "\n") << endl << endl;

        destroy(q1);
        destroy(q2);
        destroy(q);
    }
    catch (const std::exception& e) {
        cerr << "Uncaught exception: " << e.what() << '\n';
    }

    return EXIT_FAILURE;
}

// -----------------------------------------------------------------------------

// clang-format off

/* === COMPILE & RUN ===
g++ demo_merge.cpp -o demo_merge -std=c++20 -g -Og -Wall -pedantic -march=native -I./queue && ./demo_merge

g++ demo_merge.cpp -o demo_merge -std=c++20 -O3 -march=native -DNDEBUG -I./queue && ./demo_merge
*/

/* === OUTPUT ===
q1[Job(name=M, time_id=2, priority=1)
Job(name=E, time_id=3, priority=0)
Job(name=Q, time_id=5, priority=2)
Job(name=A, time_id=9, priority=1)]

q2[Job(name=D, time_id=1, priority=0)
Job(name=T, time_id=4, priority=0)
Job(name=V, time_id=5, priority=1)
Job(name=B, time_id=7, priority=0)
Job(name=H, time_id=8, priority=1)
Job(name=R, time_id=10, priority=1)]

Merging...
q[Job(name=D, time_id=1, priority=0)
Job(name=M, time_id=2, priority=1)
Job(name=E, time_id=3, priority=0)
Job(name=T, time_id=4, priority=0)
Job(name=Q, time_id=5, priority=2)
Job(name=V, time_id=5, priority=1)
Job(name=B, time_id=7, priority=0)
Job(name=H, time_id=8, priority=1)
Job(name=A, time_id=9, priority=1)
Job(name=R, time_id=10, priority=1)]
*/