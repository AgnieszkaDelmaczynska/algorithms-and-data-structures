// Lab2.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

class Node
{
public:
    Node *left, *right, *parent;
    int key;
    Node(int key) : left(NULL), right(NULL), key(key)
    { }
};

void insert(Node *N, int key)
{
    if(N->key == key)
        return;
    if(N->key < key)
        if(N->right)
            insert(N->right, key);
        else
        {
            N->right = new Node(key);
            N->right->parent = N;
        }
        else
            if(N->left)
                insert(N->left, key);
            else
            {
                N->left = new Node(key);
                N->left->parent = N;
            }
}

Node* search(Node* N, int key)
{
    if(N == NULL)
        return NULL;
    if(N->key == key)
        return N;
    if(N->key < key)
        return search(N->right, key);
    return search(N->left, key);
}

int height(Node* N, int h) {
    if (N->left == NULL && N->right == NULL) {
        return h;
    }
    int t = 0;
    if (N->left) {
        t = height(N->left, h+1);
    }
    if (N->right) {
        if (t < height(N->right, h+1)) {
            t = height(N->right, h+1);
        }
    }
    return t;
}

int main()
{
    char cmd;
    int key;
    Node *root = NULL, *out;
    
    while(scanf("%c %d", &cmd, &key) > 0)
    {
        if(cmd == 'I')
        {
            if(root != NULL)
                insert(root, key);
            else
                root = new Node(key);
        }
        else if (cmd == 'S')
        {
            out = search(root, key);
        }
        else if (cmd == 'H')
        {
            if (search(root, key) != NULL)
            {
                printf("%d\n", height(search(root, key), 0));
            }
            else
            {
                printf("-\n");
            }
        }
    }
    return 0;
}
