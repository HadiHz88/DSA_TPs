# 🧩 DSA_TPs

A comprehensive Data Structures and Algorithms (DSA) repository implemented in C. This project contains core data structure implementations (Linked Lists, Stacks, Queues, Binary Trees) alongside practical "Travaux Pratiques" (TPs) that demonstrate these structures in real-world applications.

> ## ⚠️ Disclaimer
>
> **Please Note:** The solutions provided in this repository come from various sources and may not be perfect.
>
> - Some solutions are my own implementations, while others come from professors or other students
> - There might be inconsistencies or errors in certain implementations
> - Some TPs may lack detailed explanations or may be missing entirely
> - This project was organized primarily to help fellow students have a centralized reference
>
> As a student myself, I put this together to help others navigate these concepts. If you find errors or have suggestions for improvements, please feel free to reach out. Remember, the goal is learning!

## 📋 Table of Contents

- [🧩 DSA\_TPs](#-dsa_tps)
  - [📋 Table of Contents](#-table-of-contents)
  - [📁 Project Structure](#-project-structure)
  - [🔢 Implemented Topics](#-implemented-topics)
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
├── src/                     # Core data structure implementations
│   ├── SinglyLinkedList/    # Singly linked list implementation
│   │   └── SLL.c
│   ├── Stack/               # Stack implementations
│   │   └── Dynamic/
│   │       └── STACK.c
│   ├── Queue/               # Queue implementations
│   │   └── Dynamic/
│   │       └── QUEUE.c
│   ├── BinaryTree/          # Binary tree implementation
│   │   └── BT.c
│   └── dsa.h                # Header file for all implementations
├── TP/                      # Practical exercises
│   ├── 1_LinkedList_I/      # First linked list exercise
│   │   ├── solution.c
│   │   └── helper.c
│   ├── 2_BinaryTree_I/      # First binary tree exercise
│   │   └── solution.c
│   ├── 3_Stack_I/           # Stack exercises
│   │   └── TP3.c
│   └── ...                  # Additional exercises
└── build/                   # Generated build files (not committed)
```

## 🔢 Implemented Topics

This project includes implementations of:

- Singly Linked Lists
- Stacks (Dynamic and Static)
- Queues (Dynamic and Static)
- Binary Trees
- Binary Search Trees
- Sorting & Searching Algorithms
- Heaps
- Hash Tables

Each structure comes with core operations like insertion, deletion, traversal, and more — all written in C and applied in practical TPs.

## 🛠️ Requirements

- **Compiler**: GCC or Clang with C23 support
- **Build system**: [CMake 3.10+](https://cmake.org/download/)
- **Operating System**: Linux, macOS, or Windows (with WSL)
- **Optional**: Make (for convenience)

## 🚀 Building & Running

### Initial Setup

```bash
# Clone the repository
git clone https://github.com/HadiHz88/DSA_TPs.git
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
