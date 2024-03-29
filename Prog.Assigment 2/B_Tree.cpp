#pragma once
#include "B_Tree.h"
using namespace std;

template <typename T>
BTree<T>::BTree(int x)
{
    min_degree = x;
    key_num = 0;
    root = createEmptyNode();
}

template <typename T>
BTree<T>::~BTree()
{
    freeAll(root);
}

template <typename T>
bool BTree<T>::contain(T key) const
{
    return nullptr != search(root, key);
}

template <typename T>
T *BTree<T>::getHandle(T key) const
{
    return search(root, key);
}

template <typename T>
void BTree<T>::display() const
{

    cout <<  "Display the B-Tree as follows" << endl
         << endl;

    cout << "B-Tree root node at left most:" << endl;

    display_weekly(root);

    cout <<  "B-Tree has " << key_num << " keys. " << endl;

    cout << "*************END DISPLAY*******************" << endl
         << endl;
}

template <typename T>
void BTree<T>::display_weekly(int week) const
{

    cout <<  "Display the B-Tree as follows" << endl
         << endl;

    cout << "B-Tree root node at left most:" << endl;

    string week_string = to_string(week);
    string filename = "week " + week_string + " B-Tree report.csv";
    ofstream outfile;
    outfile.open(filename,ios::app);

    cout<<"profession"<<" "<<"ID"<<endl;
    outfile<<"profession"<<","<<"ID"<<endl;

    display_weekly(root,week);

    cout <<  "B-Tree has " << key_num << " keys. " << endl;

    cout << "*************END DISPLAY*******************" << endl
         << endl;
}

template <typename T>
void BTree<T>::display_monthly(int month) const
{

    cout <<  "Display the B-Tree as follows" << endl
         << endl;

    cout << "B-Tree root node at left most:" << endl;

    string month_string = to_string(month);
    string filename = "month " + month_string + " B-Tree report.csv";
    ofstream outfile;
    outfile.open(filename,ios::app);

    cout<<"profession"<<" "<<"ID"<<endl;
    outfile<<"profession"<<","<<"ID"<<endl;

    display_monthly(root,month);

    cout <<  "B-Tree has " << key_num << " keys. " << endl;

    cout << "*************END DISPLAY*******************" << endl
         << endl;
}

template <typename T>
bool BTree<T>::insert(T key)
{
    if (contain(key))
        return false;

    if (root == nullptr)
        root = createEmptyNode();

    // while searching for the position along the tree, splitting the full node if it is
    // when every time we need to split a full node, we should make sure that its parent node is not full.
    if (root->size == 2 * min_degree - 1)
    {
        BTreeNode<T> *new_root = createEmptyNode();
        new_root->is_leaf = false;
        new_root->children[0] = root;
        splitChild(new_root, 0);
        root = new_root;

        updateDepth(root);
    }

    bool ret = insertNonFull_recursively(root, key);
    if (ret)
        key_num++;
    return ret;
}

template <typename T>
bool BTree<T>::remove(T key)
{
    if (key_num == 0)
        return false;
    bool ret = remove(root, key);
    if (ret)
        key_num--;
    return ret;
}

template <typename T>
void BTree<T>::printNodeInfo(BTreeNode<T> *p_node) const
{
    cout << endl;
    cout << "*******NODE INFORMATION********" << endl;
    cout << "is leaf: " << p_node->is_leaf << endl;
    cout << "depth : " << p_node->depth << endl;
    cout << "key array : ";
    for (int i = 0; i < p_node->size; i++)
        cout << p_node->keys[i] << " ";
    cout << endl;

    for (int i = 0; i <= p_node->size; i++)
    {
        cout << " sNumber "<< i << " child contains: ";
        for (int j = 0; j < p_node->children[i]->size; j++)
            cout << p_node->children[i]->keys[j] << " ";
        cout << endl;
    }
    cout << endl;
}

template <typename T>
BTreeNode<T> *BTree<T>::createEmptyNode()
{
    BTreeNode<T> *ret = new BTreeNode<T>;

    ret->is_leaf = true;
    ret->size = 0;
    ret->depth = 0;
    ret->keys = new T[2 * min_degree - 1];
    ret->children = new BTreeNode<T> *[2 * min_degree];

    return ret;
}

template <typename T>
void BTree<T>::freeAll(BTreeNode<T> *root_node)
{
    if (!root_node->is_leaf)
    {
        for (int i = 0; i <= root_node->size; i++)
            freeAll(root_node->children[i]);
    }

    delete[] root_node->keys;
    delete[] root_node->children;
    delete root_node;
}

template <typename T>
int BTree<T>::findFirstNotSmaller(BTreeNode<T> *p_node, T a_key, int *temp) const
{
    int i = 0;
    for (; i < p_node->size && p_node->keys[i] < a_key; i++)
        {
            if (p_node->keys[i] > a_key && p_node->keys[i] < *temp) *temp = p_node->keys[i];
        }
    return i;
}

template <typename T>
T *BTree<T>::search(BTreeNode<T> *p_node, T key_to_search) const
{
    if (p_node == nullptr)
        return nullptr;

    int key_arr_size = p_node->size;
    int pos = 0;
    for (; pos < p_node->size && p_node->keys[pos] < key_to_search; pos++)
        ;
    if (pos < key_arr_size && key_to_search == p_node->keys[pos])
        return &(p_node->keys[pos]);
    else
    {
        if (p_node->is_leaf)
            return nullptr;
        else
            return search(p_node->children[pos], key_to_search);
    }
}

template <typename T>
T BTree<T>::search_range(BTreeNode<T> *p_node, T key_to_search, int *tempo) const
{
    int key_arr_size = p_node->size;
    int pos = findFirstNotSmaller(p_node, key_to_search,tempo);
    if (pos < key_arr_size && key_to_search == p_node->keys[pos])
        return p_node->keys[pos];
    else
    {
        if (p_node->is_leaf)
        {
            if (pos==p_node->size) return *tempo;
            return p_node->keys[pos];
        }
        else
            return search_range(p_node->children[pos], key_to_search, tempo);
    }
}

template <typename T>
void BTree<T>::display(BTreeNode<T> *p_node) const
{
    if (p_node == nullptr)
        return;

    if (p_node->is_leaf)
    {
        for (int i = 0; i < p_node->size; ++i)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            cout << (p_node->keys[i]%10000) << endl;
        }
        return;
    }

    for (int i = 0; i <= p_node->size; ++i)
    {
        display(p_node->children[i]);
        if (i != p_node->size)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            cout << (p_node->keys[i]%10000) << endl;
        }
    }

}

template <typename T>
void BTree<T>::display_weekly(BTreeNode<T> *p_node, int week) const
{
    string week_string = to_string(week);
    string filename = "week " + week_string + " B-Tree report.csv";
    ofstream outfile;
    outfile.open(filename,ios::app);

    if (p_node == nullptr)
        return;

    if (p_node->is_leaf)
    {
        for (int i = 0; i < p_node->size; ++i)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            outfile<<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< "," ;
            cout << (p_node->keys[i]%10000) << endl;
            outfile<<(p_node->keys[i]%10000) << endl;
        }
        return;
    }

    for (int i = 0; i <= p_node->size; ++i)
    {
        display_weekly(p_node->children[i],week);
        if (i != p_node->size)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            outfile<<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< "," ;
            cout << (p_node->keys[i]%10000) << endl;
            outfile<<(p_node->keys[i]%10000) << endl;
        }
    }

}

template <typename T>
void BTree<T>::display_monthly(BTreeNode<T> *p_node, int month) const
{
    string month_string = to_string(month);
    string filename = "month " + month_string + " B-Tree report.csv";
    ofstream outfile;
    outfile.open(filename,ios::app);
    if (p_node == nullptr)
        return;

    if (p_node->is_leaf)
    {
        for (int i = 0; i < p_node->size; ++i)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            outfile<<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< "," ;
            cout << (p_node->keys[i]%10000) << endl;
            outfile<<(p_node->keys[i]%10000) << endl;
        }
        return;
    }

    for (int i = 0; i <= p_node->size; ++i)
    {
        display_monthly(p_node->children[i],month);
        if (i != p_node->size)
        {
            int height = root->depth - p_node->depth;
            for (int j = 0; j < height; j++)
                ;
            cout <<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< " " ;
            outfile<<((p_node->keys[i])-(p_node->keys[i]%10000))/10000<< "," ;
            cout << (p_node->keys[i]%10000) << endl;
            outfile<<(p_node->keys[i]%10000) << endl;
        }
    }

}

template <typename T>
void BTree<T>::updateDepth(BTreeNode<T> *p_node)
{
    if (p_node == nullptr || p_node->is_leaf)
        return;

    int max_depth = -1;
    for (int i = 0; i <= p_node->size; i++)
    {
        if (p_node->children[i]->depth > max_depth)
            max_depth = p_node->children[i]->depth;
    }

    p_node->depth = max_depth + 1;
}

template <typename T>
T BTree<T>::getPred(BTreeNode<T> *p_node, int index) const
{
    BTreeNode<T> *cursor = p_node->children[index];
    while (!cursor->is_leaf)
        cursor = cursor->children[cursor->size];
    return cursor->keys[cursor->size - 1];
}

template <typename T>
T BTree<T>::getSucc(BTreeNode<T> *p_node, int index) const
{
    BTreeNode<T> *cursor = p_node->children[index + 1];
    while (!cursor->is_leaf)
        cursor = cursor->children[0];
    return cursor->keys[0];
}

template <typename T>
bool BTree<T>::insertToNode(BTreeNode<T> *p_node, T new_key)
{

// Find the first key greater than or equal to k
    int n = p_node->size;
    int i = 0;
    while (i < n && new_key > p_node->keys[i])
    {
        i++;
    }

    if (new_key == p_node->keys[i])
        return false; // repeated key is not allowed

    for (int j = p_node->size; j > i; j--)
    {
        p_node->keys[j] = p_node->keys[j - 1];
        if (!p_node->is_leaf)
        {
            p_node->children[j + 1] = p_node->children[j];
        }
    }

    p_node->keys[i] = new_key;
    p_node->size++;
    return true;
}

template <typename T>
void BTree<T>::splitChild(BTreeNode<T> *parent, int full_child_index)
{

    BTreeNode<T> *full_child = parent->children[full_child_index];


    // create a new node
    BTreeNode<T> *sibling = createEmptyNode();
    sibling->is_leaf = full_child->is_leaf;

    // copy node data
    for (int i = 0; i <= min_degree - 1; i++)
    {
        if (i < min_degree - 1)
        {
            sibling->keys[i] = full_child->keys[i + min_degree];
        }
        if (!full_child->is_leaf)
            sibling->children[i] = full_child->children[i + min_degree];
    }

    full_child->size = sibling->size = min_degree - 1;
    updateDepth(sibling);

    // insert middle key to parent
    insertToNode(parent, full_child->keys[min_degree - 1]);

    // connect sibling to parent
    parent->children[full_child_index + 1] = sibling;


}

template <typename T>
void BTree<T>::mergeChildren(BTreeNode<T> *parent, int merge_index)
{
    BTreeNode<T> *left_child = parent->children[merge_index];
    BTreeNode<T> *right_child = parent->children[merge_index + 1];

    // drag down the middle key from parent
    left_child->keys[left_child->size] = parent->keys[merge_index];
    left_child->size++;

    // copy node data
    for (int i = 0; i <= right_child->size; i++)
    {
        if (i < right_child->size)
            left_child->keys[i + left_child->size] = right_child->keys[i];
        if (!left_child->is_leaf)
            left_child->children[i + left_child->size] = right_child->children[i];
    }
    left_child->size += right_child->size;

    // free right child
    ///freeNode(right_child);
    delete[] right_child->keys;
    delete[] right_child->children;
    delete right_child;

    // update parent
    int i = merge_index;
    while (i < parent->size - 1)
    {
        parent->keys[i] = parent->keys[i + 1];
        if (!parent->is_leaf)
            parent->children[i + 1] = parent->children[i + 2];
        i++;
    }
    parent->size--;
}

template <typename T>
bool BTree<T>::removeFromLeaf(BTreeNode<T> *p_node, int remove_index)
{
    if (remove_index > p_node->size - 1)
        return false;

    int i = remove_index;
    while (i < p_node->size - 1)
    {
        p_node->keys[i] = p_node->keys[i + 1];
        i++;
    }

    p_node->size--;

    if (p_node->size == 0){
        ///freeNode(p_node);
    delete[] p_node->keys;
    delete[] p_node->children;
    delete p_node;
    }
    return true;
}

template <typename T>
bool BTree<T>::removeFromNonLeaf(BTreeNode<T> *&p_node, int remove_index) // reference or not???
{
    T remove_key = p_node->keys[remove_index];
    BTreeNode<T> *left_child = p_node->children[remove_index];
    BTreeNode<T> *right_child = p_node->children[remove_index + 1];

    if (left_child->size >= min_degree)
    {
        T pred = getPred(p_node, remove_index);
        p_node->keys[remove_index] = pred;
        return remove(p_node->children[remove_index], pred);
    }
    else if (right_child->size >= min_degree)
    {
        T succ = getSucc(p_node, remove_index);
        p_node->keys[remove_index] = succ;
        return remove(p_node->children[remove_index + 1], succ);
    }
    else
    {
        mergeChildren(p_node, remove_index);
        if (p_node->size == 0)
        {
            BTreeNode<T> *temp = p_node;
            p_node = p_node->children[0];
            delete[] temp->keys;
            delete[] temp->children;
            delete temp;
        }
        return remove(p_node, remove_key);
    }
}

template <typename T>
void BTree<T>::borrowFromLeftC(BTreeNode<T> *parent, int borrowed_child)
{
    BTreeNode<T> *Lchild = parent->children[borrowed_child];
    BTreeNode<T> *left_sibling = parent->children[borrowed_child - 1];

    // shift that child
    for (int i = Lchild->size; i >= 0; i--)
    {
        if (i > 0)
            Lchild->keys[i] = Lchild->keys[i - 1];
        if (!Lchild->is_leaf)
            Lchild->children[i + 1] = Lchild->children[i];
    }

    // taht child drag key from parent
    Lchild->keys[0] = parent->keys[borrowed_child - 1];

    // that child drag child from sibling
    if (!Lchild->is_leaf)
        Lchild->children[0] = left_sibling->children[left_sibling->size];

    Lchild->size++;

    // parent drag from sibling
    parent->keys[borrowed_child - 1] = left_sibling->keys[left_sibling->size - 1];
    left_sibling->size--;
}

template <typename T>
void BTree<T>::borrowFromRightC(BTreeNode<T> *parent, int borrowed_child)
{
    BTreeNode<T> *Rchild = parent->children[borrowed_child];
    BTreeNode<T> *right_sibling = parent->children[borrowed_child + 1];

    // that child drag key from parent
    Rchild->keys[Rchild->size] = parent->keys[borrowed_child];
    Rchild->size++;

    // that child drag child from sibling
    if (!Rchild->is_leaf)
        Rchild->children[Rchild->size] = right_sibling->children[0];

    // parent drag key from sibling
    parent->keys[borrowed_child] = right_sibling->keys[0];

    // shift sibling
    for (int i = 0; i <= right_sibling->size - 1; i++)
    {
        if (i <= right_sibling->size - 2)
            right_sibling->keys[i] = right_sibling->keys[i + 1];
        if (!right_sibling->is_leaf)
            right_sibling->children[i] = right_sibling->children[i + 1];
    }
    right_sibling->size--;
}

template <typename T>
void BTree<T>::fillChild(BTreeNode<T> *parent, int fill_child)
{
    if (fill_child > 0 && parent->children[fill_child - 1]->size >= min_degree)
        borrowFromLeftC(parent, fill_child);
    else if (fill_child < parent->size && parent->children[fill_child + 1]->size >= min_degree)
        borrowFromRightC(parent, fill_child);
    else
    {
        if (fill_child != parent->size)
            mergeChildren(parent, fill_child);
        else
            mergeChildren(parent, fill_child - 1);
    }
}

template <typename T>
bool BTree<T>::remove(BTreeNode<T> *&p_node, T remove_key) // when to update depth???
{
    bool ret;
    if (p_node->size == 0)
        p_node = p_node->children[0];

// Find the first key greater than or equal to k
    int n = p_node->size;
    int i = 0;
    while (i < n && remove_key > p_node->keys[i])
    {
        i++;
    }

    if (i < p_node->size && remove_key == p_node->keys[i])
    {
        if (p_node->is_leaf)
            ret = removeFromLeaf(p_node, i);
        else
            ret = removeFromNonLeaf(p_node, i);
    }
    else
    {
        if (p_node->is_leaf)
            return false;

        bool pos_at_end = i == p_node->size;
        if (p_node->children[i]->size < min_degree)
            fillChild(p_node, i);
        if (pos_at_end && i > p_node->size)
            ret = remove(p_node->children[i - 1], remove_key);
        else
            ret = remove(p_node->children[i], remove_key);
    }

    updateDepth(p_node);
    return ret;
}

template <typename T>
bool BTree<T>::insertNonFull_recursively(BTreeNode<T> *p_node, T insert_key)
{
    if (p_node->is_leaf)
        return insertToNode(p_node, insert_key);

// Find the first key greater than or equal to k
    int n = p_node->size;
    int i = 0;
    while (i < n && insert_key > p_node->keys[i])
    {
        i++;
    }

    if (i < p_node->size && insert_key == p_node->keys[i])
        return false;

    BTreeNode<T> *target_child = p_node->children[i];

    // cout << "point 2" << endl;

    if (target_child->size == 2 * min_degree - 1)
    {
        splitChild(p_node, i);
        if (insert_key == p_node->keys[i])
            return false;
        if (insert_key > p_node->keys[i])
            target_child = p_node->children[i + 1];
    }

    // cout << "point 3" << endl;

    return insertNonFull_recursively(target_child, insert_key);
}