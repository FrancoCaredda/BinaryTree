#include "binary_tree.h"
#include <iostream>
#include <vector>

int main(void)
{
	std::vector<int> array = { 15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18, 23 };

	BinaryTree<int> tree;

	for (int i = 0; i < array.size(); i++)
		tree.Insert(array[i]);

	
	tree.Bypass(tree.GetRoot(), [](Node<int>* node) { std::cout << node->Value << " "; });

	std::cout << std::endl;

	return 0;
}