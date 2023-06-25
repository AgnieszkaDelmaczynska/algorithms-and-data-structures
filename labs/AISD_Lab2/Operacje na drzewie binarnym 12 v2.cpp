#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
struct Node
{
    int key;
    Node* left, * right;
    Node();
    Node(int);
    Node* insert(Node*, int);
    Node* search(Node*, int);
    int function_to_count(Node*);
    int summing_function(Node*, int, int&);
};

Node::Node()
    : key(0), left(NULL), right(NULL){}
Node::Node(int keyy)
{
    key = keyy;
    left = right = NULL;
}
Node* Node::insert(Node* N, int key)
{
    if (!N)
    {
        return new Node(key);
    }
    if (key > N->key)
    {
        N->right = insert(N->right, key);
    }
    else
    {
        N->left = insert(N->left, key);
    }
    return N;
}

Node* Node::search(Node* N, int key)
{
    if (N == NULL)
        return NULL;
    if (N->key == key)
        return N;
    if (N->key < key)
        return search(N->right, key);
    return search(N->left, key);
}

int Node::summing_function(Node* N, int n, int& sum)
{
    sum = N->key + sum;
    if (N == NULL || N->key == n)
    {
        return sum;
    }
    else
    {
        if (N->key < n)
        {
            return summing_function(N->right, n, sum);
        }
        else
        {
            return summing_function(N->left, n, sum);
        }
    }
}
int main()
{
    char cmd;
    int key;
    Node node, * root = NULL, *out;
    Node* root_v2 = NULL;
    int counter = 0;
    int sum = 0;
    while (std::cin >> cmd)
    {
        if (cmd == 'I')
        {
            scanf_s("%d", &key);
            if (counter == 0)
            {
                root = node.insert(root, key);
                root_v2 = root;
                counter++;
            }
            else if (node.search(root, key) == NULL)
            {
                node.insert(root, key);
                counter++;
            }
        }
        else if (cmd == 'S')
        {
            scanf_s("%d", &key);
            out = node.search(root, key);
        }
        else if (cmd == 'Q')
        {
            scanf_s("%d", &key);
            if (counter > 0 && node.search(root, key) != NULL)
            {
                printf("%d\n", node.summing_function(root_v2, key, sum));
                sum = 0;
            }
            else if (counter == 0 || node.search(root, key) == NULL)      
                printf("-\n");
        }
    }
    return 0;
}