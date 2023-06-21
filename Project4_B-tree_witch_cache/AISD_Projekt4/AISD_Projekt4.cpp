// B-tree_with_cache but without cache
#include<iostream>
#include<string>
using namespace std;

class BNode
{
private:
    int T;              // Minimum degree of B-Tree
    bool isLeaf;
    int num;            // Current number of keys
    int* keys;          // An array of keys
    BNode** Children;   // An array of child pointers
    int FULL;           // Maximum number of keys 
    int MIN;            // Minimum number of keys 
public:
    BNode(int _T, bool _isLeaf);
    void insert_in_non_full_node(int given_key);
    void insert_in_non_full_node_leaf(int given_key);
    void insert_in_non_full_node_non_leaf(int given_key);
    void split_child_node(int i, BNode* w);     // Function to split the child w of this node. i is index of w in child array Children[]. 
    bool check_if_value_in_tree(int given_key);
    void traverse_the_tree();
    friend class BTree;
};

class BTree
{
private:
    int T;              // Minimum degree
    BNode* root;        // Pointer to root node
    void allocate_memory_for_new_root(int given_key);
public:
    BTree(int given_T);
    bool tree_empty() const;
    bool root_full() const;
    bool check_if_value_in_tree(int given_key);
    void traverse_the_tree();
    void insert(int given_key);
    void tree_grows_in_height(int given_key);
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    string function;
    cin >> function;    // I

    int parameter;
    cin >> parameter;   // T

    BTree b_tree(parameter);

    while (std::cin >> function)
    {
        if (function == "A")
        {
            std::cin >> parameter;
            b_tree.insert(parameter);
        }
        else if (function == "P")
        {
            b_tree.traverse_the_tree();
            printf("\n");
        }
        else if (function == "?")
        {
            std::cin >> parameter;
            if (b_tree.check_if_value_in_tree(parameter))
                printf("%d +\n", parameter);
            else
                printf("%d -\n", parameter);
        }
        else if (function == "X")
            break;
    }
    return 0;
}

void BTree::allocate_memory_for_new_root(int given_key)
{
    root = new BNode(T, true);
    root->keys[0] = given_key;
    root->num = 1;
}

BTree::BTree(int given_T)
{
    T = given_T;
    root = NULL;
}

bool BTree::tree_empty() const
{
    if (root == NULL)
        return true;
    else return false;
}

bool BTree::root_full() const
{
    if (root->num == 2 * T - 1)
        return true;
    else
        return false;
}

bool BTree::check_if_value_in_tree(int given_key)
{
    if (tree_empty())
        return false;
    else
    {
        bool result = root->check_if_value_in_tree(given_key);
        return result;
    }
}

void BTree::traverse_the_tree()
{
    if (tree_empty())
        return;
    else
        root->traverse_the_tree();
}

void BTree::insert(int given_key)
{
    if (!tree_empty())
    {
        if (!root_full())
            root->insert_in_non_full_node(given_key);
        else
            tree_grows_in_height(given_key);
    }
    else
        allocate_memory_for_new_root(given_key);
}

void BTree::tree_grows_in_height(int given_key)
{
    BNode* new_root = new BNode(T, false);
    new_root->Children[0] = root;
    new_root->split_child_node(0, root); // Split the old root and move one key to the new root

    enum Choice
    {
        left,
        right
    };

    int child_that_is_going_to_have_new_key = Choice::left;
    while (new_root->keys[0] < given_key)
    {
        child_that_is_going_to_have_new_key = Choice::right;
        break;
    }
    new_root->Children[child_that_is_going_to_have_new_key]->insert_in_non_full_node(given_key);
    root = new_root;
}

BNode::BNode(int _T, bool _isLeaf)
{
    T = _T;
    isLeaf = _isLeaf;
    num = 0;
    keys = new int[2 * T - 1];
    Children = new BNode * [2 * T];
    FULL = 2 * T - 1;
    MIN = T - 1;
}

void BNode::traverse_the_tree()
{
    int i = 0;
    while (i < num)
    {
        if (isLeaf == false)
            Children[i]->traverse_the_tree();
        cout << keys[i] << " ";
        i++;
    }
    if (isLeaf == false)
        Children[i]->traverse_the_tree();
}

bool BNode::check_if_value_in_tree(int given_key)
{
    int counter = 0;
    for (int i = 0; i < num; i++)   // Find the first key greater than or equal to k
    {
        counter = i;
        if (given_key > keys[i])
        {
            counter++;
            continue;
        }
        else
            break;
    }

    if (keys[counter] == given_key)
        return true;

    if (keys[counter] != given_key && isLeaf == true)
        return false;

    bool result = Children[counter]->check_if_value_in_tree(given_key);     // Go to the appropriate child
    return result;
}

void BNode::insert_in_non_full_node(int given_key)
{
    switch (isLeaf)
    {
        case false:
        {
            this->insert_in_non_full_node_non_leaf(given_key);
            break;
        }
        case true:
        {
            this->insert_in_non_full_node_leaf(given_key);
            break;
        }
    }
}

void BNode::insert_in_non_full_node_non_leaf(int given_key)
{
    int index = num - 1;
    
    // Find the child which is going to have the new key
    for (index = num - 1; index >= 0 && given_key < keys[index];)
        index--;

    if (Children[index + 1]->num == FULL)
    {
        split_child_node(index + 1, Children[index + 1]);

        if (keys[index + 1] < given_key) // Decide where to add a new key
            index++;
    }
    Children[index + 1]->insert_in_non_full_node(given_key);
}

void BNode::insert_in_non_full_node_leaf(int given_key)
{
    int index = num - 1;

    for (index = num - 1; index >= 0 && given_key < keys[index]; index--)
        keys[index + 1] = keys[index];

    keys[index + 1] = given_key;
    num++;
}

void BNode::split_child_node(int i, BNode* w)
{  
    BNode* z = new BNode(w->T, w->isLeaf);
    z->num = MIN;
    w->num = MIN;

    for (int j = num - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    for (int j = num; j >= i; j--)      // Since this node is going to have a new child, create space of new child
        Children[j + 1] = Children[j];

    keys[i] = w->keys[MIN];             // Copy the middle key of w to this node
    Children[i + 1] = z;                // Link the new child to this node

    for (int j = 0; j < MIN; j++)       // Copy the last (t-1) keys of w to z
        z->keys[j] = w->keys[j + T];

    for (int j = 0; j < T; j++)         // Copy the last t children of w to z
        z->Children[j] = w->Children[j + T];
    num++;
}