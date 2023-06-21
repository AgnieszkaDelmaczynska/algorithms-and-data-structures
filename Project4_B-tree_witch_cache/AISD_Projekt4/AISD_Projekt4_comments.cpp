// B-tree_with_cache but without cache
#include<iostream>
#include<string>
using namespace std;

// A BTree node
class BNode
{
private:
    int T;              // Minimum degree (defines the range for number of keys)
    bool isLeaf;        // Is true when node is leaf. Otherwise false
    int num;            // Current number of keys
    int* keys;          // An array of keys
    BNode** Children;   // An array of child pointers
    int FULL;
    int MIN;
public:
    BNode(int _T, bool _isLeaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insert_in_non_full_node(int given_key);

    void insert_in_non_full_node_leaf(int given_key);
    void insert_in_non_full_node_non_leaf(int given_key);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void split_child_node(int i, BNode* y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse_the_tree();

    // A function to check a key in the subtree rooted with this node.
    bool check_if_value_in_tree(int given_key);   // returns false if k is not present.

// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
private:    
    int T;  // Minimum degree
    BNode* root; // Pointer to root node

    void allocate_memory_for_new_root(int given_key)
    {
        root = new BNode(T, true);
        root->keys[0] = given_key;  // Insert key
        root->num = 1;  // Update number of keys in root
    }
public:
    // Constructor (Initializes tree as empty)
    BTree(int given_T)
    {
        T = given_T;
        root = NULL;
    }

    bool tree_empty() const
    {
        if (root == NULL)
            return true;
        else return false;
    }

    bool root_full() const
    {
        if (root->num == 2 * T - 1)
            return true;
        else
            return false;
    }

    // function to check a key in this tree
    bool check_if_value_in_tree(int given_key)
    {
        if (tree_empty())
            return false;
        else
        {
            bool result = root->check_if_value_in_tree(given_key);
            return result;
        }
    }

    // function to traverse the tree
    void traverse_the_tree()
    {
        if (tree_empty())
            return;
        else
            root->traverse_the_tree();
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int given_key);
    void tree_grows_in_height(int given_key);
};

// Constructor for BNode class
BNode::BNode(int _T, bool _isLeaf)
{
    // Copy the given minimum degree and leaf property
    T = _T;
    isLeaf = _isLeaf;

    // Initialize the number of keys as 0
    num = 0;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2 * T - 1];
    Children = new BNode * [2 * T];

    FULL = 2 * T - 1;
    MIN = T - 1;
}

// Function to traverse all nodes in a subtree rooted with this node
void BNode::traverse_the_tree()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i = 0;
    while (i < num)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (isLeaf == false)
            Children[i]->traverse_the_tree();
        cout << keys[i] << " ";
        i++;
    }

    // Print the subtree rooted with last child
    if (isLeaf == false)
        Children[i]->traverse_the_tree();
}

// Function to check key k in subtree rooted with this node
bool BNode::check_if_value_in_tree(int given_key)
{
    // Find the first key greater than or equal to k
    int counter = 0;
    for (int i = 0; i < num; i++)
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

    // If the found key is equal to k, return this node
    if (keys[counter] == given_key)
        return true;

    // If key is not found here and this is a leaf node
    if (keys[counter] != given_key && isLeaf == true)
        return false;

    // Go to the appropriate child
    bool result = Children[counter]->check_if_value_in_tree(given_key);
        return result;
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int given_key)
{
    // If tree is not empty
    if (!tree_empty())
    {
        if (!root_full())  // If root is not full, call insert_in_non_full_node for root
            root->insert_in_non_full_node(given_key);
        // If root is full, then tree grows in height
        else
            tree_grows_in_height(given_key);
    }
    // If tree is empty
    else
        allocate_memory_for_new_root(given_key);
}

void BTree::tree_grows_in_height(int given_key)
{
    // Allocate memory for new root
    BNode* new_root = new BNode(T, false);

    // Make old root as child of new root
    new_root->Children[0] = root;

    // Split the old root and move 1 key to the new root
    new_root->split_child_node(0, root);

    // New root has two children now.  Decide which of the
    // two children is going to have new key

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

    // Change root
    root = new_root;
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
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
    // Initialize index as index of rightmost element
    int index = num - 1;
    
    // Find the child which is going to have the new key
    for (index = num - 1; index >= 0 && given_key < keys[index];)
        index--;

    // See if the found child is full
    if (Children[index + 1]->num == FULL)
    {
        // If the child is full, then split it
        split_child_node(index + 1, Children[index + 1]);

        // After split, the middle key of C[i] goes up and
        // C[i] is splitted into two.  See which of the two
        // is going to have the new key
        if (keys[index + 1] < given_key)
            index++;
    }
    Children[index + 1]->insert_in_non_full_node(given_key);
}

void BNode::insert_in_non_full_node_leaf(int given_key)
{
    // Initialize index as index of rightmost element
    int index = num - 1;

    // The following loop does two things
    // a) Finds the location of new key to be inserted
    // b) Moves all greater keys to one place ahead

    for (index = num - 1; index >= 0 && given_key < keys[index]; index--)
        keys[index + 1] = keys[index];

    // Insert the new key at found location
    keys[index + 1] = given_key;
    num++;
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BNode::split_child_node(int i, BNode* w)
{  
    // Create a new node which is going to store (t-1) keys
    // of y
    BNode* z = new BNode(w->T, w->isLeaf);
    z->num = MIN;
    // Reduce the number of keys in y
    w->num = MIN;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = num - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = num; j >= i; j--)
        Children[j + 1] = Children[j];

    // Copy the middle key of y to this node
    keys[i] = w->keys[MIN];
    // Link the new child to this node
    Children[i + 1] = z;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < MIN; j++)
    {
        z->keys[j] = w->keys[j + T];
    }

    // Copy the last t children of y to z
    for (int j = 0; j < T; j++)
    {
        z->Children[j] = w->Children[j + T];
    }
    // Increment count of keys in this node
    num++;
}

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
                printf("%d +\n",parameter);
            else 
                printf("%d -\n", parameter);
        }
        else if (function == "X")
            break;
    }
    return 0;
}