# C-Common-Memory-Errors

This project is my personal journey through the Udemy course "Fixing Memory Bugs
in C," serving as a hands-on companion to solidify the learnings. It delves deep
into the world of common memory errors encountered in C programming.

It serves as a learning resource to understand how these errors manifest, their
impact on program behavior, and how to identify and prevent them.

We'll explore a range of memory-related pitfalls C programmers face, including:

1. **Uninitialized Values:** Accessing memory that hasn't been assigned a value
   can lead to unpredictable behavior and crashes. We'll see how this happens
   and how to avoid it.
2. **Invalid Reads:** Reading from memory locations that are out of bounds or
   not allocated can corrupt data and cause program instability. We'll
   demonstrate this scenario and explore techniques to prevent it.
3. **Invalid Writes:** Writing to unintended memory locations can overwrite
   critical data and cause unexpected program behavior. We'll investigate this
   error and ways to mitigate it.
4. **Invalid Frees:** Attempting to free memory that hasn't been allocated or
   has already been freed can lead to crashes and memory corruption. We'll delve
   into this issue and proper memory management practices.
5. **Fishy Values:** Sometimes, seemingly valid values can indicate underlying
   memory issues. We'll explore how to identify these "fishy values" and
   diagnose potential memory problems.
6. **Memory Leaks:** Memory leaks occur when allocated memory isn't freed when
   it's no longer needed. Over time, this can lead to performance degradation
   and crashes. We'll learn how to detect and prevent memory leaks.

This repository serves as a valuable resource for C programmers of all levels,
from beginners to experienced developers, and especially for those following the
"Fixing Memory Bugs in C" course on Udemy.

Feel free to explore the code samples, experiment, and enhance your
understanding of memory management in C!

## Getting Started

To start using the code in this repository, follow these steps:

1. **Clone the Repository:** Clone this repository to your local machine using
   the following command:

    ``` shell
    git clone https://github.com/kurijlj/C-Common-Memory-Errors.git
    ```

2. **Navigate to a Project Tree:** Browse through the project tree and explore
   the provided examples and stusy cases.

3. **Compile the code:** Build as a regular CMake project:

   1. Create a build directory and `cd` into it.
   2. Create a directory structure and project makefiles using (optionally you
   can specify the generator by invoking with the -G switch):

       ``` shell
       cmake -G <Generator> -B . -S <project_source_tree> -DBUILD_SHARED_LIBS:BOOL=[ON|OFF] -DBUILD_TESTS:BOOL=[ON|OFF]
       ```

   3. Build executable using:

       ```shell
       cmake --build . --config [Debug|RelWithDebInfo|Release|MinSizeRel]
       ```

## Build Targets

- **uninitialized_values:** This code explores the reading from uninitialized
  memory. Specifically, we'll investigate what happens when you try to read
  from a pointer that points to a string that hasn't been assigned a value.
  The goal is to twofold:
  1. Observe compiler warnings: We'll compile the code and see what warnings the
  compiler generates for this practice.
  1. Explore memory profiling tool output: We'll use a memory profiling tool
  like DrMemory to see if it detects any issues.
- **all**: Build all abovementioned targets.

## License

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.
