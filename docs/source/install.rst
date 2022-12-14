.. highlight:: shell

Installation
************

Requirements
============

``cppdsa-queue`` requires a C++20 compiler and CMake.

Instructions
============

Here is the simplest way to get you up and running.

Clone the source code from Github

.. code-block:: shell

    $ git clone https:://github.com/KriztoferY/cppdsa-queue

Download Google Test

.. code-block:: shell
    
    $ git submodule add --force https://github.com/google/googletest.git test/lib/googletest


Create Build Directory

.. code-block:: shell

    $ rm -rf build
    $ mkdir -p build/debug build/release

Build, Test, and Install 

.. code-block:: shell

    $ cd scripts
    $ ./clean-build.sh
    $ ./cmake-build-release.sh 

If everything goes smoothly,

- The header-only library is located in ``include/``.

- A demo program is located in ``bin/``.