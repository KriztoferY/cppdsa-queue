.. _algos:

Algorithms on Queue ADT
***********************

Algorithms are independent of implementation of the Queue ADT.

Merging two queues
==================

Modifying overload
------------------

.. doxygenfunction:: dsa::merge(IQueue<Elem, Impl> *queue1, IQueue<Elem, Impl> *queue2)
    :project cppdsa-queue


Non-modifying overload
----------------------

.. doxygenfunction:: dsa::merge(IQueue<Elem, Impl> const* queue1, IQueue<Elem, Impl> const* queue2)
    :project cppdsa-queue

Example
^^^^^^^

Merges two job queues in which jobs are ranked based on time and assigned
priority.

Here are the ``Job`` class along with a function object that specifies how 
jobs are compared and satisfies the ``BinaryPredicate`` concept, and an 
overloaded ``operator<<()`` to make the ``Job`` class ``Insertable``.

.. code-block:: cpp

    struct Job
    {
        unsigned int time_id;              // unique ID as timestamp
        unsigned int priority { 0 };       // job priority
        std::string  name { "unnamed" };   // job name (non-unique)
    };

    struct
    {
        // Compares two jobs based on time ID, followed by priority.
        bool operator()(Job const& j1, Job const& j2) const {
            if (j1.time_id == j2.time_id) return j1.priority > j2.priority;
            return j1.time_id < j2.time_id;
        }
    } compare_jobs;

    std::ostream& operator<<(std::ostream& os, Job const& job) {
        return os << "Job(name=" << job.name << ", time_id=" << job.time_id
                << ", priority=" << job.priority << ")";
    }

We are going to populate two circular array queue of ``Job`` s and then merge 
them.

.. code-block:: cpp

    ...
    #include "circ_array_queue.hpp"   // CircArrayQueue<T>
    #include "algos.hpp"              // merge<...>()

    using JobQueue = dsa::CircArrayQueue<Job>;

    dsa::IQueue<Job, dsa::CircArrayQueue>* jq1 { new JobQueue {} };
    Job jobs1[] {
        { 2, 1, "M" }, { 3, 0, "E" }, 
        { 5, 2, "Q" }, { 9, 1, "A" }
    };
    for (auto const& job : jobs1) jq1->enqueue(job);

    dsa::IQueue<Job, dsa::CircArrayQueue>* jq2 { new JobQueue {} };
    Job jobs2[] { { 1, 0, "D" }, { 4, 0, "T" }, { 5, 1, "V" },
                  { 7, 0, "B" }, { 8, 1, "H" }, { 10, 1, "R" } };
    for (auto const& job : jobs2) jq2->enqueue(job);

    auto* jq = dsa::merge<Job, 
                          dsa::CircArrayQueue, 
                          decltype(compare_jobs)>(jq1, jq2);

    std::cout << "Merging jq1 and jq2..." << '\n';
    std::cout << jq->to_string("jq", "\n") << "\n\n";

    destroy(jq1);
    destroy(jq2);
    destroy(jq);

The merged queue looks like:

.. code-block:: sh

    Merging jq1 and jq2...
    jq[Job(name=D, time_id=1, priority=0)
    Job(name=M, time_id=2, priority=1)
    Job(name=E, time_id=3, priority=0)
    Job(name=T, time_id=4, priority=0)
    Job(name=Q, time_id=5, priority=2)
    Job(name=V, time_id=5, priority=1)
    Job(name=B, time_id=7, priority=0)
    Job(name=H, time_id=8, priority=1)
    Job(name=A, time_id=9, priority=1)
    Job(name=R, time_id=10, priority=1)]

Note that even though jobs Q and V have the same timestamp, job Q appears
before job V as it has a higher priority.

|

Concepts
========

.. doxygenconcept:: dsa::BinaryPredicate
   :project: cppdsa-queue

