.. highlight:: cpp

A Quick Tour
************

Using a Queue
=============

From the consumers' perspective, the ``cppdsa-queue`` library provides various
ready-to-use queue data structures that can store pretty much any kind of C++
objects of both the fundamental and user-defined types. Each queue
implementation is a class template and has the same standardized API, except
the additional features specific to a particular implementation.

Having known the type `T` of the elements to store, you instantiate a queue 
from the chosen class template. It's often convenient to define a type alias
for it upfront. Now, let's try the unbounded
:ref:`Circular Array Queue<circ_array_queue>`.

.. code-block:: cpp

    #include "circ_array_queue.hpp"

    using IntQueue = dsa::CircArrayQueue<int>;

    auto q = IntQueue {};

Now, you've an empty queue ``q`` awaiting data.

.. code-block:: cpp

    for (int nums[] { 3, 1, 4, 1 }; auto num : nums) {
        q.enqueue(num);
    }

    std::cout << q.size() << std::endl;     // prints 4

In case of large element type `T`, you may use the ``emplace<Args...>()`` 
member function to create the new elements in-place without copying and moving
to boost performance.

In any case, you may then use the typical idiom to process the elements in the 
queue in the first-in-first-out (FIFO) manner.

.. code-block:: cpp

    while (!q.empty()) {
        std::cout << q.front() << ' ';
        q.dequeue();
    }
    std::cout << std::endl;

As long as you're not using the *static polymorphism* feature of the library,
you have nothing to worry about ``q`` and its elements when you're done with it, 
unless ``q`` was created on the free store and assigned to a pointer of the 
exact same type or simply an ``auto`` pointer. In the latter case, of course 
you'll simply have to do ``delete q;``.

.. code-block:: cpp

    IntQueue* q = new IntQueue {};
    ...
    delete q;       // GOOD: it works

Static Polymorphism
-------------------

Now, suppose you've created a queue on the free store and assigned it to a 
pointer to the "abstract" base class template.

.. code-block:: cpp

    IQueue<int, dsa::CircArrayQueue>* q = new dsa::CircArrayQueue<int> {};
    ...
    delete q;       // BAD: memory leak!

The last statement is the catch! When you're done with the queue, you need to 
**use the free function** ``destroy<Elem, Impl>()`` **to destroy the queue on 
the free store via a base pointer**. ``delete q`` will only trigger the base 
class destructor, skipping the derived class destructor that actually frees the
memory associated with the queue elements on the free store.

The typical use case of this situation is using a function that accepts a 
generic queue type via pointer.

.. code-block:: cpp

    // library code
    template <typename Elem, template <typename> typename Impl>
    void process(IQueue<Elem, Impl>* queue, ...);

    // client code
    IQueue<int, dsa::CircArrayQueue>* q = new dsa::CircArrayQueue<int> {};
    process(q);
    ...
    dsa::destroy(q);    // GOOD: no memory leak

So, if you're indeed a library developer writing such kind of functions, you're
advised to document the proper usage in your documentation.

Demo Program
------------

Wanna see a queue in action? No problem. Follow the installation instructions 
to build the project. You'll find a demo program in the ``bin/`` subdirectory.

|

Implementing Your Own Queue
===========================

By design, all queue types are subclasses of the same "abstract" class template 
``IQueue<Elem, Impl>``, which specifies the interface of a conventional queue
data structure. The class template definition of the :ref:`Circular Array 
Queue<circ_array_queue>` looks something like this:

.. code-block:: cpp 

    template <typename Elem>
    class CircArrayQueue : public IQueue<Elem, CircArrayQueue>;

Here, the template parameter ``Elem`` specifies the queue element type, and 
the implementation class template inherit from the "abstract" base class 
template using the *Curiously Recurring Template Pattern (CRTP)*, which is a 
key to achieving static inheritance and polymorphism.

Let's say you're going to define a class template ``MyQueue<Elem>`` to 
implement the Queue ADT. Here is a blueprint to get you started:

.. code-block:: cpp

    namespace dsa {

    template <typename Elem>
    class MyQueue : public IQueue<Elem, MyQueue> {
        friend class IQueue<Elem, MyQueue>;
    
    public:
        /* ctor, dtor, copy & move op= as appropriate */

        /* member functions specific to your implementation if any */

    private:
        /* data members */
        
        /* helper functions if any */

        /* ### MANDATORY INTERFACE MATCHERS ### */
    };

    }  // end namespace

The *mandatory* **interface matchers** are the private member functions that 
actually realize the functionality of their respective parent class members in
``IQueue<Elem, Impl>``. Let's zoom in to see what's expected there.

.. code-block:: cpp

    std::size_t size_() const noexcept;
    bool        empty_() const noexcept;
    void        iter_(std::function<void(Elem const&)>) const;
    Elem&       front_();
    Elem const& front_() const;

    void enqueue_(Elem const& elem);
    void enqueue_(Elem&& elem);
    void dequeue_();

    template <typename... Args>
    void emplace_(Args&&... args);

You're advised to follow the coding style of the ``cppdsa-*`` libraries to 
implement them all in a separate ``.inl`` file and then ``#include`` it at the
end of the header file for the ``MyQueue<Elem>`` class template.

This is it!