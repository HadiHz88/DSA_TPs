# Minimum required version for CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(DSA_TPs)

# Set the C standard
set(CMAKE_C_STANDARD 23)

# Specify the source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Include directories for header files (all source subdirectories)
include_directories(${SRC_DIR})

# Add all the source files for the data structures
set(SOURCE_FILES
    ${SRC_DIR}/SinglyLinkedList/SLL.c
    # ${SRC_DIR}/Stack/Static/STACK.c
    ${SRC_DIR}/Stack/Dynamic/STACK.c
    # ${SRC_DIR}/Queue/Static/QUEUE.c
    ${SRC_DIR}/Queue/Dynamic/QUEUE.c
    ${SRC_DIR}/BinaryTree/BT.c
)

add_executable(tp1
    TP/1_LinkedList_I/TP1.c
    ${SOURCE_FILES}
)

add_executable(tp4
    TP/4_BinaryTree_I/test.c
    ${SOURCE_FILES}
)
