# 🧩 DSA_TPs

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language](https://img.shields.io/badge/language-C23-blue.svg)](https://en.cppreference.com/w/c/23)
[![CMake](https://img.shields.io/badge/build-CMake-brightgreen.svg)](https://cmake.org/)

A comprehensive Data Structures and Algorithms (DSA) repository implemented in C. This project contains core data structure implementations (Linked Lists, Stacks, Queues, Binary Trees) alongside practical "Travaux Pratiques" (TPs) that demonstrate these structures in real-world applications.

## 📋 Table of Contents

- [🧩 DSA\_TPs](#-dsa_tps)
  - [📋 Table of Contents](#-table-of-contents)
  - [📁 Project Structure](#-project-structure)
  - [🔢 Implemented Data Structures](#-implemented-data-structures)
  - [🛠️ Requirements](#️-requirements)
  - [🚀 Building \& Running](#-building--running)
    - [Initial Setup](#initial-setup)
    - [Running a Specific TP](#running-a-specific-tp)
    - [Rebuilding After Code Changes](#rebuilding-after-code-changes)
  - [📝 Adding New Content](#-adding-new-content)
    - [Adding a New Data Structure](#adding-a-new-data-structure)
    - [Adding a New TP](#adding-a-new-tp)
  - [💼 Best Practices](#-best-practices)
  - [👨‍💻 Author](#-author)
  - [📄 License](#-license)

## 📁 Project Structure

```
DSA_TPs/
├── CMakeLists.txt           # Main build configuration
├── include/                 # Header files
├── src/                     # Core data structure implementations
│   ├── SinglyLinkedList/    # Singly linked list implementation
│   │   └── SLL.c
│   ├── Stack/               # Stack implementations
│   │   └── Dynamic/
│   │       └── STACK.c
│   ├── Queue/               # Queue implementations  
│   │   └── Dynamic/
│   │       └── QUEUE.c
│   └── BinaryTree/          # Binary tree implementation
│       └── BT.c
├── TP/                      # Practical exercises
│   ├── 1_LinkedList_I/      # First linked list exercise
│   │   ├── solution.c
│   │   └── helper.c
│   ├── 2_BinaryTree_I/      # First binary tree exercise
│   │   └── solution.c
│   └── ...                  # Additional exercises
└── build/                   # Generated build files (not committed)
```

## 🔢 Implemented Data Structures

| Structure   | Implementation | Features                                |
| ----------- | -------------- | --------------------------------------- |
| Linked List | Singly-linked  | Insertion, deletion, traversal          |
| Stack       | Dynamic array  | Push, pop, peek operations              |
| Queue       | Dynamic array  | Enqueue, dequeue operations             |
| Binary Tree | Pointer-based  | Traversals, search, insertion, deletion |

## 🛠️ Requirements

- **Compiler**: GCC or Clang with C23 support
- **Build system**: [CMake 3.10+](https://cmake.org/download/)
- **Operating System**: Linux, macOS, or Windows (with WSL)
- **Optional**: Make (for convenience)

## 🚀 Building & Running

### Initial Setup

```bash
# Clone the repository
git clone https://github.com/username/DSA_TPs.git
cd DSA_TPs

# Configure with CMake
cmake -S . -B build

# Build all targets
cmake --build build
```

### Running a Specific TP

After building, executables for each TP will be available in the `build/` directory:

```bash
# Run the first linked list TP
./build/1_LinkedList_I # Or cmake -G "MinGW Makefiles" -S . -B build

# Run the binary tree TP
./build/2_BinaryTree_I
```

### Rebuilding After Code Changes

```bash
# Only needed when source files change
cmake --build build
```

> 💡 **Tip**: You only need to rerun the initial `cmake -S . -B build` command if you modify the `CMakeLists.txt` file or add new source files.

## 📝 Adding New Content

### Adding a New Data Structure

1. Create appropriate directories in `src/`
2. Implement your `.c` and `.h` files
3. Add the files to `SOURCE_FILES` in `CMakeLists.txt`

### Adding a New TP

1. Create a new directory under `TP/`, e.g., `TP/3_Queue_I/`
2. Add your implementation files (e.g., `solution.c`, `helper.c`)
3. Update `CMakeLists.txt` to build your new TP:

```cmake
add_executable(3_Queue_I
    TP/3_Queue_I/solution.c
    TP/3_Queue_I/helper.c    # optional
    ${SOURCE_FILES}          # shared data structures
)
```

4. Rebuild the project

## 💼 Best Practices

This project follows these best practices:

- **Modularity**: Each data structure is independently implemented
- **Reusability**: Core implementations shared across TPs
- **Standard compliance**: Follows C23 standards
- **Documentation**: Code is commented and documented
- **Error handling**: Robust error checking and handling

## 👨‍💻 Author

**Hadi Hijazi**  
Computer Science Student at Lebanese University  
Passionate about clean code, data structures, and building useful tools.

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

**Star ⭐ this repository if you find it useful!**
