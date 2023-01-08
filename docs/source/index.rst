The ``cppdsa-queue`` Library
****************************

``cppdsa-queue`` is a modern C++ library that provides generic implementations 
of the :ref:`Queue ADT<adt>` and related :ref:`algorithms<algos>`. It supports 
**static (compile-time) polymorphism** and is extensible by means of **template 
programming**.

.. code-block:: cpp

   ...
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

Two implementations of the Queue ADT are included in the project off the shelf:

* :ref:`dsa::CircArrayQueue<circ_array_queue>` : Circular array based implementation

* :ref:`dsa::SLListQueue<sllist_queue>` : Singly linked list based implementation


Contents
========
.. toctree::
   :maxdepth: 2

   intro
   install
   references
   API Index<genindex>
   license

|

Source Code
===========

Browse the source code on |github_link|. 

The ``cppdsa-queue`` project is licensed under the 
:ref:`BSD 3-Clause License<license>`.

.. |github_link| raw:: html

   <a href="https://github.com/KriztoferY/cppdsa-queue" target="_blank">Github</a>

|

Also Want It In Another Language?
=================================

* C : |c_repo| | |c_docs|

* Go : |go_repo| | |go_docs| [coming soon]

* Python : |py_repo| | |py_docs|

* TypeScript : |ts_repo| | |ts_docs|

.. |c_repo| raw:: html

   <a href="https://github.com/KriztoferY/cdsa-queue" target="_blank">Repository</a>

.. |c_docs| raw:: html

   <a href="https://KriztoferY.github.io/cdsa-queue" target="_blank">Documentation</a>

.. |go_repo| raw:: html

   <a href="https://github.com/KriztoferY/godsa-queue" target="_blank">Repository</a>

.. |go_docs| raw:: html

   <a href="https://KriztoferY.github.io/godsa-queue" target="_blank">Documentation</a>

.. |py_repo| raw:: html

   <a href="https://github.com/KriztoferY/pydsa-queue" target="_blank">Repository</a>

.. |py_docs| raw:: html

   <a href="https://KriztoferY.github.io/pydsa-queue" target="_blank">Documentation</a>

.. |ts_repo| raw:: html

   <a href="https://github.com/KriztoferY/tsdsa-queue" target="_blank">Repository</a>

.. |ts_docs| raw:: html

   <a href="https://KriztoferY.github.io/tsdsa-queue" target="_blank">Documentation</a>
     
The C language equivalent -- |c_eqv| -- is basically the procedural programming version of ``cppdsa-queue`` but without the compile-time polymorphism
capabilities.

.. |c_eqv| raw:: html

   <tt><a href="https://github.com/KriztoferY/cdsa-queue" target="_blank">cdsa-queue</a></tt>
