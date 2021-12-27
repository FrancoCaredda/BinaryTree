#ifndef BINARY_TREE
#define BINARY_TREE

#include <cmath>

#define EPSILON 0.00000001
#define DOUBLES_EQUAL(X, Y) fabs((X) - (Y)) < EPSILON
#define DOUBLE_EQUAL_ZERO(X) fabs((X)) < EPSILON

// The Node of BinaryTree
template<typename T>
struct Node
{
	Node<T>* Left = nullptr;
	Node<T>* Right = nullptr;
	Node<T>* Parent = nullptr;

	T Value;

	Node() = default;
	Node(const T& value)
		: Value(value) { }
	Node(const T& value, Node<T>* left, Node<T>* right, Node<T>* parent)
		: Value(value), Left(left), Right(right), Parent(parent) { }
};

// Implementation of Binary search tree data structure
template<typename T>
class BinaryTree
{
public:
	typedef void (*NodeCall)(Node<T>* node);
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree<T>& tree) = delete;
	BinaryTree(BinaryTree&& tree);

	// Recursivly inserts new node with value
	void Insert(const T& value) noexcept;
	void Erase(const T& value) noexcept;

	// Recursivly finds node with value
	inline Node<T>* Find(const T& value) noexcept { return FindInternal(m_Root, value); }
	
	inline Node<T>* GetRoot() noexcept { return m_Root; }
	inline bool Contains(const T& value) const noexcept { return const_cast<BinaryTree<T>*>(this)->Find(value) != nullptr; }
	inline bool IsEmpty() const noexcept { return m_Root == nullptr; }

	void Bypass(Node<T>* root, NodeCall call);

	~BinaryTree();
private:
	// Recursive implementetion of insertion
	void InsertInternal(Node<T>* node, Node<T>* root) noexcept;
	// Recursive implementetion of finding 
	Node<T>* FindInternal(Node<T>* root, const T& value) noexcept;
	Node<T>* FindMin(Node<T>* root) noexcept;
private:
	Node<T>* m_Root = 0;
};

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree&& tree)
{
	m_Root = tree.m_Root;
	tree.m_Root = nullptr;
}

template<typename T>
void BinaryTree<T>::Insert(const T& value) noexcept
{
	Node<T>* newNode = new Node<int>(value);

	if (m_Root == nullptr)
	{
		m_Root = newNode;
		return;
	}

	InsertInternal(newNode, m_Root);
}

template<typename T>
void BinaryTree<T>::Erase(const T& value) noexcept
{
	Node<T>* element = Find(value);

	if (element != nullptr)
	{
		if (element->Left == nullptr && element->Right == nullptr) // Element doesn't have children
		{
			if (element->Parent->Value > element->Value)
				element->Parent->Left = nullptr;
			else
				element->Parent->Right = nullptr;

			delete element;
		}
		else if (element->Left != nullptr && element->Right != nullptr) // Element has two children
		{
			Node<T>* min = FindMin(element->Right);

			if (min->Right != nullptr)
			{
				min->Parent->Left = min->Right;
				min->Right->Parent = min->Parent->Left;
			}

			element->Value = min->Value;
			delete min;
		}
		else if ((element->Left != nullptr || element->Right != nullptr) && 
			     !(element->Left != nullptr && element->Right != nullptr))  // Element has a child
		{
			if (element->Parent->Value > element->Value)
			{
				if (element->Left != nullptr)
				{
					element->Parent->Left = element->Right;
					element->Right->Parent = element->Parent;
				}
				else
				{
					element->Parent->Left = element->Left;
					element->Left->Parent = element->Parent;
				}
			}
			else
			{
				if (element->Right != nullptr)
				{
					element->Parent->Right = element->Right;
					element->Right->Parent = element->Parent;
				}
				else
				{
					element->Parent->Right = element->Left;
					element->Left->Parent = element->Parent;
				}
			}

			delete element;
		}
	}
}

template<typename T>
void BinaryTree<T>::Bypass(Node<T>* root, NodeCall call)
{
	if (root == nullptr)
		return;

	Node<T>* left = root->Left;
	Node<T>* right = root->Right;

	Bypass(left, call);
	call(root);
	Bypass(right, call);
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	if (m_Root != nullptr)
		Bypass(m_Root, [](Node<T>* node) { delete node; });
}

template<typename T>
void BinaryTree<T>::InsertInternal(Node<T>* node, Node<T>* root) noexcept
{
	if (node->Value <= root->Value)
	{
		if (root->Left == nullptr)
		{
			root->Left = node;
			node->Parent = root;

			return;
		}
	
		InsertInternal(node, root->Left);
	}
	else
	{
		if (root->Right == nullptr)
		{
			root->Right = node;
			node->Parent = root;

			return;
		}

		InsertInternal(node, root->Right);
	}
}

template<typename T>
Node<T>* BinaryTree<T>::FindInternal(Node<T>* root, const T& value) noexcept
{
	Node<T>* result = nullptr;

	if (root == nullptr)
		return nullptr;

	if (value < root->Value)
		result = FindInternal(root->Left, value);
	else if (value > root->Value)
		result = FindInternal(root->Right, value);
	else
		result = root;

	return result;
}

template<typename T>
Node<T>* BinaryTree<T>::FindMin(Node<T>* root) noexcept
{
	Node<T>* currentNode = root;

	while (currentNode->Left != nullptr)
		currentNode = currentNode->Left;

	return currentNode;
}

// Template specialization for floats and doubles

template<>
void BinaryTree<double>::InsertInternal(Node<double>* node, Node<double>* root) noexcept
{
	if (node->Value < root->Value || DOUBLES_EQUAL(node->Value, root->Value))
	{
		if (root->Left == nullptr)
		{
			root->Left = node;
			node->Parent = root;

			return;
		}

		InsertInternal(node, root->Left);
	}
	else
	{
		if (root->Right == nullptr)
		{
			root->Right = node;
			node->Parent = root;

			return;
		}

		InsertInternal(node, root->Right);
	}
}

template<>
void BinaryTree<float>::InsertInternal(Node<float>* node, Node<float>* root) noexcept
{
	if (node->Value < root->Value || DOUBLES_EQUAL(node->Value, root->Value))
	{
		if (root->Left == nullptr)
		{
			root->Left = node;
			node->Parent = root;

			return;
		}

		InsertInternal(node, root->Left);
	}
	else
	{
		if (root->Right == nullptr)
		{
			root->Right = node;
			node->Parent = root;

			return;
		}

		InsertInternal(node, root->Right);
	}
}

#endif // !BINARY_TREE