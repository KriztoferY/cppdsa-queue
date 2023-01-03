Installation
************

Dependencies
============

To build the project, you will need

* g++ (version 8+) or equivalent compiler that supports C++20 and above

* CMake (version 3.15+)

* Make (or equivalent build tool)

* GoogleTest (to be installed as submodule of the project using git)

* Git

Installing googletest
---------------------

.. code-block:: sh
    
    $ git submodule add --force https://github.com/google/googletest.git test/lib/googletest

|

Building & Testing the Project
==============================

Several bash scripts are included in the ``scripts/`` subdirectory to simplify the build and test process, both debug and release, if you've CMake installed on the system. So you don't have to run neither ``ctest`` nor any executable test programs -- each successful build will have passed all the tests included.

For all of the following commands, it's assumed that you're in the ``scripts/`` dir. If not, ``cd`` into it like

.. code-block:: sh
    
    $ cd /path/to/project/root/scripts

or modify the commands with the right path accordingly.

Full build
----------

To make the first build or a clean build, run either:

.. code-block:: sh

    $ ./cmake-build-debug.sh        # debug build
    $ ./cmake-build-release.sh      # release build

On success, you'll see the success message at the end of the build and test processes on the terminal like so:

.. code-block:: sh

    ...         # build/test info...
    👍 Congrats! You are all set.
    $

In that case, you'll find three (or four) newly created subdirectories under the project root.

#. ``build/[debug|release]/`` --- contains all artifacts created during the build process

#. ``include/`` --- contains the header files of the library.

#. ``bin/`` --- contains the executable demo programs ``queue_demo`` and ``queue_merge_demo``.

#. ``lib/`` --- (if applicable) contains the static libraries (``*.a`` archive files), which you may copy into your system library folder or your project that depends on it, along with the ``include/`` folder.

If any errors arise during the build process or the test process, otherwise, you'll get the error message at the end like so:

.. code-block:: sh
    
    ...         # build/test info...
    👎 Oops! Something went wrong.
    $

Rebuild
-------

To build the whole project again after making changes to the source code, you may simply run either

.. code-block:: sh

    $ ./cmake-rebuild-debug.sh      # debug
    $ ./cmake-rebuild-release.sh    # release

Clean
-----

Alternatively, if you'd like to have a clean build starting from scratch, you may do so by first running the following before either one of two ``*-build-*.sh`` scripts.

.. code-block:: sh
    
    $ ./clean-build.sh
