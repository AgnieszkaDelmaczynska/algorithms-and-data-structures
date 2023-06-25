#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

class Node
{
public:
    Node* left, * right, * parent;
    int key;
    Node(int key) : left(NULL), right(NULL), key(key)
    { }
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

int get_the_number_of_leaves_in_the_subtree_rooted_in_n(Node* N) // N to node
{
    if (N == NULL)
        return 0;
    if (N->left == NULL && N->right == NULL)
        return 1;
    else
        return get_the_number_of_leaves_in_the_subtree_rooted_in_n(N->left) + get_the_number_of_leaves_in_the_subtree_rooted_in_n(N->right);
}

int main()
{
    char cmd;
    int key;
    Node* root = NULL, * out;

    while (scanf("%c %d", &cmd, &key) > 0)
    {
        if (cmd == 'I')
        {
            if (root != NULL)
                insert(root, key);
            else
                root = new Node(key);
        }
        else if (cmd == 'S')
        {
            out = search(root, key);
        }
        else if (cmd == 'C')
        {
            if (search(root, key) != NULL)
            {
                printf("%d\n", get_the_number_of_leaves_in_the_subtree_rooted_in_n(search(root, key)));
            }
            else
            {
                printf("-\n");
            }
        }
    }
    return 0;
}