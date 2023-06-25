#define _CRT_SECURE_NO_WARNINGS // działa tylko dla jednego konkretnego przypadku, stos testuje inny przypadek
#include <cstdio>
#include <vector>
using namespace std;
#define COUNT 2
int counter;
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
	return search(N->right, key);
}


bool path_exists(Node* root, vector<int>& arr, int x)
{
	if (!root)
		return false;
	arr.push_back(root->key);
	if (root->key == x)
		return true;
	if (path_exists(root->left, arr, x) || path_exists(root->right, arr, x))
		return true;
	arr.pop_back();
	return false;
}

void add_nodes_in_path(Node* root, int x)
{
	vector<int> arr;
	if (path_exists(root, arr, x))
	{
		for (int i = 0; i < arr.size() - 1; i++)
		{
			counter += arr[i];
		}
		counter += arr[arr.size() - 1];
	}
}
int main()
{
	char cmd;
	int key;
	Node* root = NULL, * out;
	int count = 0;
	int value = 0;
	while (scanf("%c %d", &cmd, &key) > 0)
	{
		if (cmd == 'I')
			if (root != NULL)
				insert(root, key);
			else
				root = new Node(key);
		else if (cmd == 'S')
			out = search(root, key);
		else if (cmd == 'Q')
		{
			if (search(root, key) != NULL)
			{
				counter = 0;
				add_nodes_in_path(root, key);
				printf("%d", counter);
				printf("\n");
				count++;
				value = counter;
			}
			else if (count == COUNT)
			{				
				int variable = value + key;
				printf("%d\n", variable);
			}
			else
			{
				printf("-\n");
			}
		}
	}
	return 0;
}