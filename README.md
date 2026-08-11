# Circular Linked List

A templated circular doubly linked list implementation in C++ with move semantics support and comprehensive operations.
Header-only: simply add `CircularList.h` to your project.

## Features

- **Cyclic Structure** – last element links back to the first
- **Template Design** – works with any data type
- **Complete API** – insertion, deletion, indexed access
- **Move Semantics** – efficient rvalue operations
- **Safety** – bounds checking and exceptions
- **STL-Compatible** – familiar method interface

## Quick Start

```cpp
#include <iostream>
#include "CircularList.h"

int main() {
    CircularList<int> list;

    // Add elements
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);

    std::cout << list << '\n';         // [0, 1, 2]
    std::cout << list.front() << '\n'; // 0
    std::cout << list.back() << '\n';  // 2

    list.pop_front();
    std::cout << list << '\n';         // [1, 2]

    return 0;
}
```

## Core Methods

### Insertion Operations

list.push_front(value);      // Add to front
list.push_back(value);       // Add to back
list.push_node(value, idx);  // Insert at index

### Deletion Operations

list.pop_front();   // Remove from front
list.pop_back();    // Remove from back
list.pop_node(idx); // Remove at index

### Access Operations

list.front();        // First element
list.back();         // Last element
list.get_node(idx);  // Element at index

### Information

list.size();   // Number of elements
list.empty();  // Check if empty

## Requirements

- C++11 or later compiler (C++17 recommended)
- C++ standard library
