# cppdsa-queue <!-- omit in toc -->

A modern C++ (header-only) library that provides generic implementations of the Queue ADT and related algorithms.

Different implementations of the Queue ADT are defined in separate header files.

```cpp
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
```

A collection of implementation-agnostic algorithms on the Queue ADT is included in a dedicated header file.

```cpp
...
#include "algos.hpp"    // merge<...>()
...
using IntQueue = dsa::CircArrayQueue<int>;

dsa::IQueue<int, dsa::CircArrayQueue>* q1 { new IntQueue {} };
for (int nums[] { 4, 7, 2, 10 }; auto const num : nums) {       // num = priority
    q1->enqueue(num);
}

dsa::IQueue<int, dsa::CircArrayQueue>* q2 { new IntQueue {} };
for (int nums[] { 3, 6, 8, 9, 5, 1 }; auto const num : nums) {  // num = priority
    q2->enqueue(num);
}

// larger the element value, higher the priority given when 
// two queues are stable-merged
auto* q = dsa::merge<int, dsa::CircArrayQueue, std::greater<int>>(q1, q2);
std::cout << q->to_string("q", ",") << std::endl;
// prints "q[4,7,3,6,8,9,5,2,10,1]"
...
// manual memory deallocation requires to support 100% static polymorphism
destroy(q1);
destroy(q2);
destroy(q);
```

It is designed to support **static (compile-time) polymorphism** and is extensible by means of **template programming**.

For more details, visit the [documentation site](https://kriztofery.github.io/cppdsa-queue).

Here's what you need to get started.

- [Dependencies](#dependencies)
- [Building \& Testing the Project](#building--testing-the-project)
- [For Developers \& Contributors](#for-developers--contributors)
- [License](#license)
- [Also Want It In Another Language?](#also-want-it-in-another-language)

## Dependencies

To build the project, you will need
- g++ (version 8+) or equivalent compiler that supports C++20 and above
- CMake (version 3.15+)
- Make (or equivalent build tool)
- GoogleTest (to be installed as submodule of the project using git)
- Git

### Installing googletest <!-- omit in toc -->

```bash
$ git submodule add --force https://github.com/google/googletest.git test/lib/googletest
```

## Building & Testing the Project

Several bash scripts are included in the `scripts/` subdirectory to simplify the build and test process, both debug and release, if you've CMake installed on the system. So you don't have to run neither `ctest` nor any executable test programs -- each successful build will have passed all the tests included.

For all of the following commands, it's assumed that you're in the `scripts/` dir. If not, `cd` into it like


```bash
$ cd /path/to/project/root/scripts
```

or modify the commands with the right path accordingly.

### Full build <!-- omit in toc -->

To make the first build or a clean build, run either:

```bash
$ ./cmake-build-debug.sh        # debug build
$ ./cmake-build-release.sh      # release build
```

On success, you'll see the success message at the end of the build and test processes on the terminal like so:

```bash
...         # build/test info...
👍 Congrats! You are all set.
$
```

In that case, you'll find three newly created subdirectories under the project root.
1. `build/[debug|release]/` --- contains all artifacts created during the build process
2. `include/` --- contains the header files of the library.
3. `bin/` --- contains the executable demo programs `queue_demo` and `queue_merge_demo`.


If any errors arise during the build process or the test process, otherwise, you'll get the error message at the end like so:

```bash
...         # build/test info...
👎 Oops! Something went wrong.
$
```
### Rebuild <!-- omit in toc -->

To build the whole project again after making changes to the source code, you may simply run either
```bash
$ ./cmake-rebuild-debug.sh      # debug
$ ./cmake-rebuild-release.sh    # release
```
### Clean <!-- omit in toc -->

Alternatively, if you'd like to have a clean build starting from scratch, you may do so by first running the following before either one of two `*-build-*.sh` scripts.

```bash
$ ./clean-build.sh
```

⚠️ **WARNING** : It permanently removes all three subdirectories created during a build process. So use it with caution if you choose to save any other files at those locations.

## For Developers & Contributors

### Project structure <!-- omit in toc -->

```bash
.
├── src/
├── test/
├── scripts/
├── docs/                   
├── build/                  # to be created in the first build
├── bin/                    # to be created in the first build
├── include/                # to be created in the first build
├── ProjectConfig.h.in 
├── CMakeLists.txt
├── Doxyfile
├── LICENSE
└── README.md
```
Header and source files for the library and demo program are located in the `src/` subdirectory, whereas those for unit tests are located in the `test/` subdirectory.

### Running tests <!-- omit in toc -->

Although tests are automated via the bash scripts included, you may also run the included tests independently, which is typically useful for debugging after failing builds.

To do so, first `cd` into the `build/[debug|release]` subdirectory under the project root. Then run

```bash
$ ctest --verbose --output-on-failure
```

For debugging a failed build, you may want to add also the `--rerun-failed` flag to run only the tests that failed previously.

To find out all available options, run `ctest -help`.

### Code formatting <!-- omit in toc -->

Install `clang-format` and run it with the included `.clang-format` config file at the project root.

If you use an IDE, you're strongly revised to configure it to automatically run `clang-format` on each save.

### Documentation <!-- omit in toc -->

#### Style <!-- omit in toc -->

All documentation text are written in the Javadoc style `/** ... */` with `@` as command marker. In the so-called "banner" form (typically for classes and functions), include aligned leading asterisks `*` in each sandwiched lines. For text that can fit in a single line not exceeding 80 characters (including the comment delimiting characters), use the inline form, either succeeding a statement or on the line preceding the code block to document.

#### Site generation <!-- omit in toc -->

To build the documentation site for the project, you will need
- Doxygen 1.9.2+
- Python 3.7+
- Sphinx
- Furo
- Breathe

## License

The project is licensed under the [BSD 3-Clause License](https://github.com/KriztoferY/cppdsa-queue/blob/main/LICENSE).

## Also Want It In Another Language?

- C : [Repository](https://github.com/KriztoferY/cdsa-queue) | [Documentation](https://KriztoferY.github.io/cdsa-queue)
- Go : [Repository](https://github.com/KriztoferY/godsa-queue) | [Documentation](https://KriztoferY.github.io/godsa-queue) [coming soon]
- Python : [Repository](https://github.com/KriztoferY/pydsa-queue) | [Documentation](https://KriztoferY.github.io/pydsa-queue)
- TypeScript : [Repository](https://github.com/KriztoferY/tsdsa-queue) | [Documentation](https://KriztoferY.github.io/tsdsa-queue)

## Acknowledgement <!-- omit in toc -->

This project is bootstrapped using [Cookiecutter](https://cookiecutter.io) with the [cpp-lib-cookiecutter](https://github.com/KriztoferY/cpp-lib-cookiecutter) template by the same author of this project.

Copyright &copy; 2022 [KriztoferY](https://github.com/KriztoferY). All rights reserved.
