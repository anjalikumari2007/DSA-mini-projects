# DSA-mini-projects
Student Record Search System using Binary Search Tree (BST) and Campus Route Finder using Graphs with algorithms BFS (Breadth First Search) and DFS (Depth First Search).

# Student Record Search System Using Binary Search Tree (BST)

## Project Description

The Student Record Search System is a menu-driven C program that manages student records using a Binary Search Tree (BST). Each student record contains an enrolment ID, student name, and department.
The system allows users to insert, search, delete, and display student records. It uses the BST data structure to organize records according to enrolment IDs, making searching and sorting easier.

## Features

- **Insert Student:** Add a new student record with a unique enrolment ID, name, and department.
- **Search Student:** Search for a student using their enrolment ID.
- **Delete Student:** Remove a student record from the BST.
- **Inorder Traversal:** Display student records in ascending order of enrolment ID.
- **Preorder Traversal:** Display the tree in preorder sequence.
- **Postorder Traversal:** Display the tree in postorder sequence.
- **Duplicate Handling:** Prevent insertion of records with duplicate enrolment IDs.
- **Sample Records:** Load 10 predefined student records for testing.

## Technologies Used

- **Programming Language:** C
- **Libraries:**
  - `stdio.h` – Input and output operations.
  - `string.h` – String handling.
  - `stdlib.h` – Dynamic memory allocation and memory management.

## Data Structure Used

### Binary Search Tree (BST)

A Binary Search Tree is a non-linear data structure in which each node contains a key and two possible child nodes.

- The left child contains a smaller enrolment ID.
- The right child contains a greater enrolment ID.
- Duplicate enrolment IDs are not allowed.

Each node stores:
- Enrolment ID
- Student Name
- Department
- Pointer to the left child
- Pointer to the right child

## Time Complexity

| Operation | Average Case | Worst Case |
|---|---|---|
| Insertion | O(log n) | O(n) |
| Searching | O(log n) | O(n) |
| Deletion | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

A regular BST may become skewed if records are inserted in sorted order, resulting in O(n) operations. Self-balancing trees such as AVL trees help maintain efficient operations.

## How to Compile and Run

Dev-C++: open trees.c and press F11 Command line: gcc trees.c -o trees ./trees

## Concepts Covered

- Binary Trees and Binary Search Trees
- Structures and Pointers
- Dynamic Memory Allocation using `malloc()`
- Memory Deallocation using `free()`
- Recursion
- Insertion, Searching and Deletion
- Tree Traversals
- Time and Space Complexity

## Conclusion

The Student Record Search System demonstrates how a Binary Search Tree can be used to store and manage student information efficiently. It implements insertion, searching, deletion, and different traversal techniques while demonstrating important concepts of data structures, recursion, pointers, and dynamic memory management.

