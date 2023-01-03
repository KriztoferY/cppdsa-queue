.. _adt:

The Interface 
*************

The central piece of the library is the class template ``IQueue<Elem, Impl>`` 
that specifies the interface of the Queue ADT. It is an abstract class template
in the sense that client code cannot instantiate any queue classes from it. 
All generic implementations of the Queue ADT must statically inherit from it 
using the Curiously Recurring Template Pattern (CRTP) and fully implement the
specified interface via private member functions, so as to become an
instantiable class template.

At the topmost level of the library, a free function is defined to destroy a 
queue on the free store via a base pointer. Although memory (de)allocation of 
the queue elements is handled automatically by all baked-in implementations, 
things get complicated when client code take advantage of static polymorphism 
using pointers of the base type ``IQueue<Elem, Impl>``, which at run time 
actually points to some derived type (a concrete implementation of the queue 
ADT). Having divorced from ``virtual``,  a ``delete`` expression with a base 
pointer does not invoke the derived class destructor as desired. Here comes the 
support function to avoid such pitfall. 

In addition, there is also a custom exception class that indicates invalid 
operations on an empty queue.

|

Abstract Data Type (ADT)
========================

.. doxygenclass:: dsa::IQueue
   :project: cppdsa-queue
   :members:

|

Supporting Function
===================

.. doxygenfunction:: dsa::destroy
   :project: cppdsa-queue

NOTE: Client code that does not adopt static polymorphism will never need to 
call the `destroy()` function.

|

.. doxygenfunction:: dsa::operator<<
   :project: cppdsa-queue

|

Concepts
========

To make the member function ``dsa::IQueue::to_string()`` available, the 
element type ``Elem`` must satisfy the ``dsa::Insertable`` constraint, so that 
the insertion operator ``<<`` can be operated on the queue elements.

.. doxygenconcept:: dsa::Insertable
   :project: cppdsa-queue

|

Exception
=========

.. doxygenclass:: dsa::EmptyQueueError
   :project: cppdsa-queue
   :members: