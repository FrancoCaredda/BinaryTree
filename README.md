# BinaryTree
Implementation of binary search tree data structure as an template class in C++.
```C++
#include "binary_tree.h" // Includes the binary search tree data structure
```
Most alghorithms are recursive.
If you want to add new element to tree than use `Insert` method. 
If tree doesn't have any nodes, than inserted node will be the root of this tree.
```C++
// in main
BinaryTree<int> tree;
tree.Insert(5);
```
If you want to remove node from tree, than use `Erase` method.
```C++
// in main
tree.Erase(5);
```
Use `Find` method if you want to find node in tree.

The most powerfull method in this data structure is `Bypass` method. This method bypasses your tree and for each node it calls special function with signature `NodeCall`.
NodeCall type is a pointer on function that looks like:
```C++
void (*NodeCall)(Node<T>* node);
```
NodeCall type is defined inside BinaryTree class. Use `BinaryTree::NodeCall` to create a pointer on function.

Simple example of sorting an array of integers using `Bypass` method.

```C++
#include "binary_tree.h"
#include <iostream>
#include <vector>

int main(void)
{
	std::vector<int> array = { 15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18, 23 };

	BinaryTree<int> tree;

	for (int i = 0; i < array.size(); i++)
		tree.Insert(array[i]);

	tree.Bypass(tree.GetRoot(), [](Node<int>* node) {std::cout << node->Value << " ";});

	std::cout << std::endl;

	return 0;
}
```
