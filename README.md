
Hello World Project

A CMake-based C/C++ project with basic and advanced examples.

Overview

This project contains example programs demonstrating different levels of complexity:
- `hello_world` - A basic "Hello World" program
- `real_world` - A more complex real-world example

Prerequisites

- CMake 3.28 or higher
- C/C++ compiler
- Make build system

Building the Project

1. Create and navigate to build directory
```bash
mkdir build
cd build
```

2. Generate build files
```bash
cmake ..
```

3. Build the project
```bash
make
```

Available Targets

Main Targets
- `make all` (default) - Build all targets
- `make hello_world` - Build the basic hello world program
- `make real_world` - Build the advanced example program

Utility Targets
- `make clean` - Remove built files
- `make rebuild_cache` - Regenerate CMake cache
- `make help` - Show available targets

Usage

After building, you can run the executables:

```bash
# Run hello world example
./hello_world

# Run real world example  
./real_world
```

Development

To rebuild after making changes:
```bash
make
```

To clean and rebuild everything:
```bash
make clean
make
```

Project Structure
```
.
├── CMakeLists.txt
├── examples/
│   └── basic/
├── build/          # Generated build files
└── README.md
```
```

This README provides a clear overview of the project, build instructions, available targets, and usage information based on what I could infer from your Makefile.
