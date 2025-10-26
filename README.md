# Circular Linked List

A tamplated cyclic doubly linked list implementation in C++
with move semantics support and comprehensive operations.

## Features

- **Cylcic Structer** – Last element links back to the first
- **Template Design** – Works with any data type
- **Compplete API** – insertion, deletion, indexed access
- **Move Semantics** – Eddicient rvalue operations
- **Safety** – Bonds Checking and exceptions
- **STL-Compatible** – Familiar method interface

## Quick Start

```cpp
#inlcude "CircularList.h"

int main() {
	CircularList<int> list;

	// Add elements
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);

	// Iteration
	for (auto it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " "; // 0 1 2

	return 0;
}
```

## Core Methods

### Insertion Operations

```cpp
list.push_front(value);		// Add to front
list.push_back(value);		// Add to back
list.push_node(value, idx);	// Insert at index
```

### Deletion Operations

```cpp
list.pop_front();	// Remove from front
list.pop_back();	// Remove from back
list.pop_node(ixd);	// Remove at index
```

### Access Operations

```cpp
list.front();		// First element
list.back();		// Second element
list.get_node(idx);	// Element at index
```

### Information

```cpp
list.size();	// Number of elements
list.empty();	// Check if empty
```

## Requirements

- C++17 compiler
- Move semantics support
- STL standart library