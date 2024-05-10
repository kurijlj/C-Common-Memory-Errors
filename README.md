# C-Cmake-CLI-Framework

The C-Cmake-CLI-Framework is a comprehensive CMake project template designed to
simplify the development process for C projects that utilize a command-line
interface (CLI) and integrate with third-party libraries. This framework offers
the following features:

- **Cross-Platform Support:** The framework is designed to work seamlessly
across various operating systems, including Windows and UNIX-like environments.
- **Multiple Generator and Compiler Compatibility:** The project aims to be
compatible with different CMake generators and compilers, allowing for
flexibility in your development environment.
- **Third-Paty Library Integration:** The framework supports integration of
third-party libraries either as git submodules or via CMake's FetchContent.
- **Simplified CLI Integration:** The framework offers mechanisms to simplify
the integration of CLI functionalities into your C++ project.

## Getting Started

To start using the framework in this repository, follow these steps:

1. **Clone the Repository:** Clone this repository to your local machine using
the following command:

    ``` shell
    git clone https://github.com/kurijlj/C-Cmake-CLI-Framework.git
    ```

2. **Navigate to a Project Tree:** Browse through the project tree and add
business logic and CMake build instructions required for your app.

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

## Third-party Library Integration

- **[argparse](https://github.com/cofyc/argparse):** The CLI argument parsing
  library in C.
- **[GSL - GNU Scientific Library](https://github.com/ampl/gsl):** The GNU
  Scientific Library (GSL) is a numerical library for C and C++ programmers.
- **[munit](https://nemequ.github.io/munit):** Unit testing framework for C.

## Build Targets

- **app:** The main application target. This is the target that is built
  from the framework source code.
- **dummy:** A dummy target that does nothing. This is useful for testing
  the build tool. And also for buidling the tests.
- **dummy_test:** A dummy test target that uses the `munit' framework to test
  the basic functionality of the framework.
- **all**: Build all abovementioned targets.

## License

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.
