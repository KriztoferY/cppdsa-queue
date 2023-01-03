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

``cppdsa-queue`` is licensed under the :ref:`BSD 3-Clause License<license>`.

.. |github_link| raw:: html

   <a href="https://github.com/KriztoferY/cppdsa-queue" target="_blank">Github</a>