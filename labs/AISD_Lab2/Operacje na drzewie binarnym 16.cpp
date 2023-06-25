#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

class Node
{
public:
	Node* left, * right, * parent;
	int key;
	Node(int key) : left(NULL), right(NULL), key(key)
	{
		this->parent = NULL;
	}
};

void insert(Node* N, int key)
{
	if (N->key == key)
		return;
	if (N->key < key)
		if (N->right)
			insert(N->right, key);
		else
		{
			N->right = new Node(key);
			N->right->parent = N;
		}
	else
		if (N->left)
			insert(N->left, key);
		else
		{
			N->left = new Node(key);
			N->left->parent = N;
		}
}

Node* search(Node* N, int key)
{
	if (N == NULL)
		return NULL;
	if (N->key == key)
		return N;
	if (N->key < key)
		return search(N->right, key);
	return search(N->left, key);
}
Node* find_max_node(Node* N)
{
	while (N->right != NULL)
		N = N->right;
	return N;
}
Node* find_predecessor(Node* N)
{
	if (N->left != NULL)
		return find_max_node(N->left);
	Node* node_temp = N->parent;
	while (node_temp != NULL and node_temp->right != N)
	{
		N = node_temp;
		node_temp = node_temp->parent;
	}
	return node_temp;
}

int main()
{
	int counter = 0;
	char cmd;
	int key;
	Node* root = NULL;
	while (scanf("%c %d", &cmd, &key) > 0)
	{
		if (cmd == 'I')
		{
			if (root != NULL)
			{
				insert(root, key);
				counter++;
			}
			else
			{
				root = new Node(key);
				counter++;
			}
		}
		else if (cmd == 'B')
		{
			if (counter > 0 && search(root, key) != NULL)
			{
				if (find_predecessor(search(root, key)) == NULL)
				{
					printf("-\n");
				}
				else
					printf("%d\n", find_predecessor(search(root, key))->key);
			}
			else if (counter == 0 || search(root, key) == NULL)
			{
				printf("-\n");
			}
		}
	}
	return 0;
}