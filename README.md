# Quix Compiler

QUIX is a high-level, statically typed, memory-safe, garbage-collected, high-performance, object-oriented, general-purpose systems programming language designed to be safe, expressive, and performant. QUIX supports runtime reflection, low-level memory access, namespaces, generics, type inference, packed data types, classes, operator overloading, coroutines, default initializers, arbitrary precision math, RAII, automatic memory management, and metaprogramming.
QUIX is especially well-suited for library development, game development, and systems programming. QUIX is designed to be a modern, safe, and expressive alternative to C++ and Rust.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Building](#building)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Quix offers a clean and intuitive syntax, making it suitable for a wide range of applications. It comes with a standard library that simplifies common programming tasks.

## Usage

To compile and run Quix programs, follow these steps:

1. **Install Dependencies**: Ensure you have all necessary dependencies installed on your system.
2. **Clone the Repository**: Clone the Quix compiler repository from GitHub.
3. **Build the Compiler**: Build the Quix compiler using the provided build instructions.
4. **Compile Your Program**: Use the Quix compiler to compile your Quix source code.
5. **Execute Your Program**: Run the compiled executable to execute your Quix program.

## Building

To build the Quix compiler from source, follow these steps:

1. **Install Dependencies**: Make sure you have all necessary dependencies installed on your system.
2. **Clone the Repository**: Clone the Quix compiler repository from GitHub using the following command:
   ```
   git clone https://github.com/Kracken256/quix
   ```
3. **Navigate to the Repository**: Change your current directory to the cloned repository directory:
   ```
   cd quix
   ```
4. **Build the Compiler**: Build the Quix compiler by running the `make.py --release` command. This will compile the compiler in release mode, which is optimized for performance:
   ```
   python make.py --release
   ```
   If you want to build the compiler in debug mode, which includes additional debugging information, run the following command instead:
   ```
   python make.py --debug
   ```
   The build process may take some time to complete, depending on your system's hardware and the size of the Quix compiler source code.
5. **Verify**: The pipeline will produce a `./bin` folder in the repository root. Inside this folder, you will find the `qpkg` executable, among other binaries. Congratulations! You have successfully built the Quix compiler.

## Contributing

This is my hobby project. I work on it in my free time. Until this project is more mature, if ever, I will not be accepting contributions. If you have any questions or suggestions, feel free to open an issue on GitHub. I may take an extremely long time to respond.

<!-- 
Contributions to the Quix compiler are welcome! If you'd like to contribute, please follow these guidelines:

- Fork the repository on GitHub.
- Make your changes in a new branch.
- Test your changes thoroughly.
- Submit a pull request with a clear description of your changes. -->

## License

The Quix compiler is free software released under the GNU Lesser General Public License 2.1 (LGPL 2.1). See the `LICENSE` file for more information.

---

**Author**: Wesley Jones  
**Date**: 2024-04-09
