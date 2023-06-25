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

void print_the_vertices_from_the_subtree_rooted_in_n_in_postorder(Node* N)
{
    if (N->left != NULL)
    {
        print_the_vertices_from_the_subtree_rooted_in_n_in_postorder(N->left);
    }
    if (N->right != NULL)
    {
        print_the_vertices_from_the_subtree_rooted_in_n_in_postorder(N->right);
    }
    printf("%d ", N->key);
}

int main()
{
    char cmd;
    int key;
    Node* root = NULL, * out;

    while (scanf("%c %d", &cmd, &key) > 0)
    {
        if (cmd == 'I') {
            if (root != NULL)
                insert(root, key);
            else
                root = new Node(key);
        }
        else if (cmd == 'S') {
            out = search(root, key);
        }
        else if (cmd == 'T') {
            if (search(root, key) != NULL) {
                print_the_vertices_from_the_subtree_rooted_in_n_in_postorder(search(root, key));
                printf("\n");
            }
            else {
                printf("-\n");
            }
        }
    }
    return 0;
}