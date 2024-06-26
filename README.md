# Tree Data Structure with SFML Visualization
## Overview
This project implements a tree data structure in C++ that can handle a variable number of children per node. It also provides visualization capabilities using the Simple and Fast Multimedia Library (SFML). The code supports both generic trees and binary trees, with different traversal iterators and methods to add nodes and visualize the tree.

## Features
**Generic Tree Structure**: The Tree class can handle any type of data and can have any number of children per node, specified by a template parameter k.

**Binary Tree Specialization**: The Tree class is specialized for binary trees (i.e., trees with k=2), offering tailored functionality for binary tree operations.

**Tree Visualization**: Uses SFML to visualize the tree structure in a graphical window. Each node is represented by a circle, and edges are drawn between parent and child nodes.

 **Iterators**: Provides depth-first search (DFS), breadth-first search (BFS), and specific tree traversal iterators (in-order, pre-order, post-order).
 
 **Customizable Precision**: Allows formatting node data with a specific precision for display.
## Requirements
**C++ Compiler**: Support for C++11 or later.
**SFML**: Ensure SFML is installed and linked correctly. The font used for visualization is RobotoFlex-Regular.ttf, which should be located in the guiResources directory.
## Files
 `Tree.hpp`: Contains the implementation of the Tree class and its binary specialization.
 
 `Node.hpp`: Defines the Node class used for the tree nodes.
 
 `Iterators.hpp`: Defines iterator classes for traversing the tree in different orders.

 `Complex.hpp/cpp`: A class for complex numbers. The class overloads operators needed such as ==, > etc.

 `Test.cpp, TestCounter.cpp, doctest.h`: Test file using doctest.

 `Demo.cpp, ComplexDemo.cpp`: Demo files for the project.
## Tree Class Template
The Tree class template allows for the creation of a tree with a specified type T and a maximum number of children k.

`Tree()` - constructor for the Tree. Initialize the root pointer to nullptr.

`void add_root(Node<T> &root)` - Adds a root to the tree. Throws a std::runtime_error if the root already exists.

`void add_sub_node(Node<T>& parent, Node<T> child)` - Adds the child to the parent. If the parent already has k children an runtime error is thrown.

**Iterators**
The Tree class provides various iterator methods to traverse the tree, notice that for k!=2, all binary tree traversers return DFSIterator:


`DFSIterator<T> begin_in_order()` - Returns a DFSIterator to the start of the tree

`DFSIterator<T> end_in_order()`  - Returns a DFSIterator to the end of the tree

`DFSIterator<T> begin_pre_order()`  - Returns a DFSIterator to the start of the tree

`DFSIterator<T> end_pre_order()`  - Returns a DFSIterator to the end of the tree

`DFSIterator<T> begin_post_order()`  - Returns a DFSIterator to the start of the tree

`DFSIterator<T> end_post_order()`  - Returns a DFSIterator to the end of the tree

`BFSIterator<T> begin_bfs()`  - Returns a BFSIterator to the start of the tree

`BFSIterator<T> end_bfs()`  - Returns a BFSIterator to the end of the tree

`DFSIterator<T> begin_dfs()`  - Returns a DFSIterator to the start of the tree

`DFSIterator<T> end_dfs()`  - Returns a DFSIterator to the end of the tree

`BFSIterator<T> begin()`  - Returns a BFSIterator to the start of the tree, used as default

`BFSIterator<T> end()`  - Returns a BFSIterator to the end of the tree, used as defautl

`DFSIterator<T> make_heap_begin()`  - Returns a DFSIterator to the start of the tree

`DFSIterator<T> make_heap_end()`  - Returns a DFSIterator to the end of the tree

`~Tree()` - A destructor that clears all child nodes from the parent nodes and sets the root to nullptr.

**Visualization**
The Tree class includes a draw method that uses SFML to visualize the tree.


`void draw()` - Creates the window and handeld the drawing. It's a public method.

**Helper Functions(Private methods)**:
`formatData`: Formats node data with a specified precision.

`truncateText`: Truncates text and adds ellipsis if necessary.

`calculateSubtreeWidth`: Calculates the width of a subtree to prevent node overlapping.

`drawTree`: Recursively draws the tree nodes and edges.

## Binary Tree Specialization
The binary tree specialization of the Tree class provides more specific methods for trees with k=2.

**Iterators**

Provides in-order, pre-order, post-order, BFS, DFS, and heap traversal iterators similar to the generic tree class. 
It's differ from the general template, as the general template returns only DFSIterator for the binary Iterators, in the specialize case it return the requried iterator.

**Visualization for Binary Tree**

The binary tree visualization does not require calculateSubtreeWidth as binary trees do not overlap nodes.

## Usage
Use `make` to compile the program.

Run the Program: The draw method opens an SFML window to visualize the tree. You can run `test` or `demo` or `ComplexDemo`.

Example Code:

```#include "Tree.hpp"
int main()
{
    Tree<int, 3> tree;  // Creates a tree that allows up to 3 children per node.

    Node<int> root(1);
    tree.add_root(root);

    Node<int> child1(2);
    Node<int> child2(3);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    tree.draw();  // Opens a window to visualize the tree.

    return 0;
}
```

**Notes**
Ensure that SFML is installed and the paths are correctly set for linking.

Modify guiResources/RobotoFlex-Regular.ttf path if the font is located elsewhere.

The visualization requires a graphical environment.
