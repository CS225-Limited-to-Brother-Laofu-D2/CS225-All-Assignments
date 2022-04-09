// This file contains the class functions of CentralQueue and FibHeap

#include "FibHeap.h"
#include "Register.h"
// Following are the functions of FibHeap
// constructor
template <class T> FibHeap<T>::FibHeap() {
    keyNum = 0;
    withdraw_number = 0;
    maxDegree = 0;
    min = nullptr;
    cons = nullptr;
}

// destructor
template <class T> FibHeap<T>::~FibHeap() { }

// if node0 has higher priority return 0, else return 1
// assume that for every criterion, the smaaler number 
// means the higher priority
template <class T> int FibHeap<T>::comparePriority(FibNode<T> *node0, FibNode<T> *node1) {
    if (node0->loc->profession < node1->loc->profession) return 0;
    else if (node0->loc->profession > node1->loc->profession) return 1;
    else {
        if (node0->loc->age_group < node1->loc->age_group) return 0;
        else if (node0->loc->age_group > node1->loc->age_group) return 1;
        else {
            // id is the data of registration
            if (node0->loc->id < node1->loc->id) return 0;
            else if (node0->loc->id > node1->loc->id) return 1;
            else {
                if (node0->loc->register_day < node1->loc->register_day) return 0;
                else if (node0->loc->register_day > node1->loc->register_day) return 1;
                else return 0;
            }
        }
    }
}

// remove a node from the double link list
template <class T> void FibHeap<T>::removeNode(FibNode<T> *node) {
    node->right->left = node->left;
    node->left->right = node->right;
}

// add a node to the left of the root
template <class T> void FibHeap<T>::addNode(FibNode<T> *node, FibNode<T> *root) {
    node->left        = root->left;
    node->right       = root;
    root->left->right = node;
    root->left        = node;
}

// insert a node to the fibheap
template <class T> void FibHeap<T>::insert(FibNode<T> *node) {
    // if the node is null then just return
    if (node == nullptr) return;
    // check whether there is any node in the fibheap
    // if so then insert the first node
    if (keyNum == 0) min = node;
    else {
        addNode(node, min);
        if(comparePriority(min, node) == 1) min = node;
    }
    keyNum++;
}

// merge Other into the current heap
template <class T> void FibHeap<T>::combine(FibHeap<T> *other) {
    if (other==NULL)
        return ;

    if(other->maxDegree > this->maxDegree) swap(*this, *other);

    if((this->min) == NULL) 
    { // this has no "minimum node"
        this->min = other->min;
        this->keyNum = other->keyNum;
        free(other->cons);
        delete other;
    }
    else if((other->min) == NULL)           
    { // this has "minimum node" && other Has no "minimum node"
        free(other->cons);
        delete other;
    }                                       
    else
    { // this has "minimum node" && other has "minimum node"
        // add "other root list "to "this"
        catList(this->min, other->min);

        if (comparePriority(this->min, other->min) == 1) this->min = other->min;
        this->keyNum += other->keyNum;
        free(other->cons);
        delete other;
    }
}

// Update Fibonacci heap node node with key
template <class T> void FibHeap<T>::updateProfession(FibNode<T> *node, int profession) {
    if(profession < node->loc->profession) decreaseProfession(node, profession);
    else if(profession > node->loc->profession) increaseProfession(node, profession);
    else cout << "No need to update!!!" << endl;
}

// remove the min value node from the root list
template <class T> FibNode<T>* FibHeap<T>::extractMin() {
    // ptr is a temporary variable
    FibNode<T> *ptr = min;
    
    if (ptr == ptr->right) min = nullptr;
    else
    {
        removeNode(ptr);
        min = ptr->right;
    }
    ptr->left = ptr->right = ptr;

    return ptr;
}

// link node to the root list
template <class T> void FibHeap<T>::link(FibNode<T>* node, FibNode<T>* root) {
    // remove node from the double link list
    removeNode(node);
    // set node as root's child
    if (root->child == nullptr) root->child = node;
    else addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

// create the space required for consolidate
template <class T> void FibHeap<T>::makeCons() {
    int old = maxDegree;

    // calculate log2(keyNum), considering rounding up
    //maxDegree = (log(keyNum)/log(2.0)) + 1;
    maxDegree = keyNum;
    if (old >= maxDegree) return ;

    // because the degree is maxDegree may be merged, so to maxDegree+1
    cons = (FibNode<T> **)realloc(cons, sizeof(FibHeap<T> *) * (maxDegree + 1));
}

// Merge trees of the same degree left and right in the root-linked table of the Fibonacci heap
template <class T> void FibHeap<T>::consolidate() {
    int i, degree, big_degree;
    FibNode<T> *x, *y;

    makeCons(); // create the space for hashing
    big_degree = maxDegree + 1;

    for (i = 0; i < big_degree; i++) cons[i] = nullptr;

    // merge root nodes of the same degree so that the tree of each degree is unique
    while (min != nullptr)
    {
        x = extractMin();                // fetch the smallest tree in the heap
        degree = x->degree;                    // get the degree of the smallest tree
        // cons[d] != NULL, means there are two trees with the same degree
        while (cons[degree] != nullptr)
        {
            y = cons[degree];                // y is a tree which has the same degree as x
            if (comparePriority(x, y) == 1) swap(x, y);       // ensure that the key value of x is smaller than y

            link(y, x);    // link y to x
            cons[degree] = nullptr;
            degree++;
        }
        cons[degree] = x;
    }
    min = nullptr;
    
    // re-add the nodes in cons to the root table
    for (i = 0; i < big_degree; i++)
    {
        if (cons[i] != nullptr)
        {
            if (min == nullptr) min = cons[i];
            else
            {
                addNode(cons[i], min);
                if (comparePriority((cons[i]), min) == 0) min = cons[i];
            }
        }
    }
}

// remove the min node
template <class T> FibNode<T> *FibHeap<T>::popMin() {
    if (min==nullptr) return nullptr;

    FibNode<T> *child = nullptr;
    FibNode<T> *move = min;
    // add min's child and its brothers to the root list
    while (move->child != nullptr)
    {
        child = move->child;
        removeNode(child);
        if (child->right == child)
            move->child = nullptr;
        else
            move->child = child->right;

        addNode(child, min);
        child->parent = nullptr;
    }
    
    // remove m from the root list
    removeNode(move);
    
    // if m is the only node in the heap, set the smallest node of the heap to NULL
    // otherwise, set the smallest node of the heap to a non-empty node (m->right), and then adjust it.
    if (move->right == move)
        min = nullptr;
    
    else {
        min = move->right;
        consolidate();
    }
    keyNum--;

    return move;
}

// Get the minimum loc value in the Fibonacci heap and save it to the pkey; success returns true, otherwise returns false.
template <class T> bool FibHeap<T>::minimum(T *ptr) {
    if (min==nullptr || ptr==nullptr)
        return false;

    *ptr = min->loc;
    return true;
}

// update degrees
template <class T> void FibHeap<T>::renewDegree(FibNode<T> *parent, int degree) {
    if ((parent == nullptr) || (degree != parent->degree-1)) return;
    parent->degree -= degree;
    if (parent->parent != nullptr) renewDegree(parent->parent, degree);
    /*parent->degree -= degree;
    if (parent-> parent != NULL)
        renewDegree(parent->parent, degree);*/
}

// strips the node from the parent parent's child links, and make the node a member of the root list of the heap.
template <class T> void FibHeap<T>::cut(FibNode<T> *node, FibNode<T> *parent) {
    removeNode(node);
    if (node->degree == node->parent->degree-1) 
        renewDegree(parent, node->degree);
    // node has no brothers
    if (node == node->right)
        parent->child = nullptr;
    else
        parent->child = node->right;

    node->parent = nullptr;
    node->left = node->right = node;
    node->marked = false;
    // add the node tree to the root list
    addNode(node, min);
}


/*
 * do cascading cut to the node
 *
 * Cascade cut: If the reduced node breaks the minimal heap property
 * then it is cut down (i.e., removed from the bidirectional linked table it is in and
 * it is inserted into the two-way linked table formed by the root node of the minimum tree).
 * then recursively perform cascade pruning from the "parent node of the cut node" to the root node of the tree
 */
template <class T> void FibHeap<T>::cascadingCut(FibNode<T> *node) {
    FibNode<T> *parent = node->parent;
    if (parent != nullptr)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

// Add the Fibonacci heap node to key
template <class T> void FibHeap<T>::increaseProfession(FibNode<T> *node, int profession)
{
    FibNode<T> *child, *parent, *right;

    if (min==NULL ||node==NULL)
        return ;

    if (profession <= node->loc->profession)
    {
        cout << "increase failed: the new key(" << profession <<") "
             << "is no greater than current key(" << node->loc->profession <<")" << endl;
        return ;
    }

    // Will node every son (excluding grandchildren, great-grandchildren...) All added to the Fibonacci Heap root list
    while (node->child != NULL)
    {
        child = node->child;
        // Remove child from node's child list
        removeNode(child);               
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;
        // Add child to the root list
        addNode(child, min);       
        child->parent = NULL;
    }
    node->degree = 0;
    node->loc->profession = profession;

    // If node is not in the root list,
    // Remove node from child link of parent node.
    // And make node a member of the root list of the heap,
    // Then perform "cascading clipping"
    // Otherwise, determine whether the smallest node of the heap needs to be updated
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(comparePriority(node, right) == 1)
                min = right;
            right = right->right;
        }
    }
}

// Decrease the value of node node in the Fibonacci heap to key
template <class T> void FibHeap<T>::decreaseProfession(FibNode<T> *node, int profession) {
    FibNode<T> *parent;

    if (min == nullptr ||node == nullptr)
        return ;

    if ( profession>=node->loc->profession)
    {
        // cout << "new key is greater than current key" << endl;
        return ;
    }

    node->loc->profession = profession;
    parent = node->parent;
    if (parent != nullptr && (comparePriority(node, parent) == 0))
    {
        // strip the node from its parent parent and add the node to the root chain table
        cut(node, parent);
        cascadingCut(parent);
    }

    // update the min node
    if (comparePriority(node, min) == 0)
        min = node;
}

// search the exact person recursively, according to the key and ID; if not find, return NULL
template <class T> FibNode<T>* FibHeap<T>::id_search(FibNode<T> *root, person* loc, int ID) {
    FibNode<T> *tmp = root;    // temporary node
    FibNode<T> *p = nullptr;    // target node

    if (root == nullptr)
        return root; // protect the stability

    do
    {
        if ((tmp->loc == loc) && (tmp->loc->id == ID))
        {
            p = tmp;
            break;
        }
        else
        {
            if ((p = id_search(tmp->child, loc, ID)) != nullptr)
                break;
        }
        tmp = tmp->right;
    } while (tmp != root);

    return p;
}

// remove the node
template <class T> void FibHeap<T>::remove(FibNode<T> *node) {
    // set the key of the node to be the min
    int p = min->loc->profession-1;
    int original = node->loc->profession;
    decreaseProfession(node, p-1);
    popMin();
    node->loc->profession = original;
}

// if empty retun ture, else retun false
template <class T> bool FibHeap<T>::ifempty() {
    if (this->keyNum == 0) return true;
    else return false;
}

/*
* Print "Fibonacci heap"
*
* Parameter description:
* node -- the current node
* prev -- the previous node of the current node (parent or sibling)
* direction -- 1, indicating that the current node is a left child;
* 2: indicates that the current node is a sibling node.
*/
template <class T> void FibHeap<T>::print(FibNode<T> *node, FibNode<T> *prev, int direction, int day)
{
    FibNode<T> *start=node;

    if (node==NULL)
        return ;
    do
    {
        if (direction == 1){
            cout<<node->loc->name<<" "<<node->loc->id<<" "<<node->loc->profession<<" "<<node->loc->age<<" "<<node->loc->risk<<" "<<(day-node->loc->register_day)<<endl;}
        else{
            cout<<node->loc->name<<" "<<node->loc->id<<" "<<node->loc->profession<<" "<<node->loc->age<<" "<<node->loc->risk<<" "<<(day-node->loc->register_day)<<endl;}

        if (node->child != NULL)
            print(node->child, node, 1, day);

        // Brother nodes
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

template <class T> void FibHeap<T>::print(int day)
{
    int i=0;
    FibNode<T> *p;

    if (min==NULL)
        return ;

    cout<<"name"<<" "<<"ID"<<" "<<"profession"<<" "<<"age"<<" "<<"risk"<<" "<<"waiting-time-until-today"<<endl;
    p = min;
    do {
        cout<<p->loc->name<<" "<<p->loc->id<<" "<<p->loc->profession<<" "<<p->loc->age<<" "<<p->loc->risk<<" "<<(day-p->loc->register_day)<<endl;
        print(p->child, p, 1, day);
        p = p->right;
    } while (p != min);
    cout << endl;
}

// this function is used to find the person reaching ddl
// pop the ones reaching the ddl and have not been treated
template <class T> void FibHeap<T>::pop_ddl(FibNode<T> *node, FibNode<T> *prev, int direction, queue<person*>* ddl_queue, int day) {

    FibNode<T> *start=node;

    if (node==NULL)
        return ;
    do
    {
        if ((node->loc->ddl_day == day) && (node->loc->if_treated == false)) ddl_queue->push(node->loc);
        if (node->child != NULL) pop_ddl(node->child, node, 1, ddl_queue, day);

        // Brother nodes
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

template <class T> void FibHeap<T>::pop_ddl(queue<person*>* ddl_queue, int day) {

    int i=0;
    FibNode<T> *p;

    if (min==NULL)
        return ;

    p = min;
    do {
        if ((p->loc->ddl_day == day) && (p->loc->if_treated == false)) ddl_queue->push(p->loc);
        pop_ddl(p->child, p, 1, ddl_queue, day);
        p = p->right;
    } while (p != min);
    
}

/*template <class T> FibNode<T>* FibHeap<T>::pop_ddl(FibNode<T> *root, int day, queue<person*>* ddl_queue) {
    FibNode<T> *tmp = root;    // temporary node
    FibNode<T> *p = nullptr;    // target node
    if (root == nullptr)
        return root; // protect the stability

    do
    {
        if ((tmp->loc->ddl_day == day) && (tmp->loc->if_treated == false))
        {
            p = tmp;
            ddl_queue->push(p->loc);
            remove(p);
            break;
        }
        else
        {
            if ((p = pop_ddl(tmp->child, day, ddl_queue)) != nullptr) 
                break;
        }
        tmp = tmp->right;
    } while (tmp != root);
    return p;
}
*/

// following are functions of Centralized_Queue
// set the point from person to fib_node
template <class T> void Centralized_Queue<T>::set_in(person *person, FibNode<T> *fib_node){
    if (person == nullptr) return;
    fib_node->loc = person;
}

// transfer the data from local registry to center
// the input is *person. call this function will generate a node in the FibHeap
template <class T> void Centralized_Queue<T>::record_in(person *person) {
    if (person == nullptr) return;
    
    FibNode<T> *fib_node = new FibNode<T>(0);
    set_in(person, fib_node);
    this->fib_heap->insert(fib_node);
}

// pop a minimum node. it will return a pointer to the node.
// if there is no node, it will return a NULL pointer
template <class T> person *Centralized_Queue<T>::record_out() {
    FibNode<T> *fib_node = nullptr;
    // check if there is any node in the fibheap
    if (this->fib_heap->ifempty()) return fib_node->loc;
    else {
        fib_node = this->fib_heap->popMin();
        return fib_node->loc;
    }
}

// search the node with loc and ID in the fibheap. return a pointer to the node; if not find, return NULL
template <class T> void Centralized_Queue<T>::search_node(person *person, FibNode<T> **fib_node){
    FibNode<T> *root_node;
    int id = person->id;
    root_node = this->fib_heap->min;
    *fib_node = this->fib_heap->id_search(root_node, person, id);
    return;
}

// the priority change due to profession should be done after this function!!
template <class T> void Centralized_Queue<T>::change_profession(person *person, int profession){
    FibNode<T> *fib_node = nullptr;
    // search the node in the heap
    search_node(person, &fib_node);
    // not find
    if (fib_node == nullptr) 
    {
        cout<<"This person is not in the centralized queue."<<endl;
        return;
    }
    this->fib_heap->updateProfession(fib_node, profession);
    return;
}

template <class T> void Centralized_Queue<T>::withdraw_heap(person *person) {
    FibNode<T> *fib_node = nullptr;
    // search the node in the heap
    search_node(person, &fib_node);
    // not found
    if (fib_node == nullptr)
    {
        cout<<"This person is not in the centralized queue."<<endl;
        return;
    }
    
    
    // change the status to withdraw, and remove the node
    fib_node->loc->if_withdrawed = true;
    this->fib_heap->remove(fib_node);
    this->fib_heap->withdraw_number++;
    cout<<"Withdraw successful."<<endl;
    return;
}
/*
// this function is used to change node's risk
// if no/low risk convert to medium risk then pop
// if any risk convert to high risk and there are
// more than 15 person in the centralized queue
// then remove it. Otherwise, just return null
template <class T> person* Centralized_Queue<T>::change_risk(person *person, int risk){
    FibNode<T> * fib_node = nullptr;
    int original_risk;
    // search the node in the heap
    search_node(person, &fib_node);
    // not found
    if (fib_node == nullptr) return nullptr;

    original_risk = fib_node->loc->risk;
    if(((original_risk == 0) && (risk == 2)) || ((original_risk == 1) && (risk == 2) ))
    {
        fib_node->loc->risk = risk;
        this->fib_heap->remove(fib_node);
        return fib_node->loc;
    }
    else if((original_risk == 0 || original_risk == 1 || original_risk == 2) && (risk == 3) )
    {
        this->fib_heap->remove(fib_node);
        return nullptr;
    } 
    else
    {
        return nullptr;
    }

}*/

template <class T> void Centralized_Queue<T>::WeeklyReport(int day) {
    this->fib_heap->print(day);
}

template <class T> void Centralized_Queue<T>::MonthlyReport() {
    cout<<"The whole number of person in the Centralized Queue"<<" "<<this->fib_heap->keyNum<<endl;
    cout<<"The whole number of person who had withdrawed"<<" "<<this->fib_heap->withdraw_number<<endl;
}

template <class T> FibNode<T>* Centralized_Queue<T>::get_everyone_loc(FibNode<T> *root, queue<person*>* everyone_loc) {
    FibNode<T> *tmp = root;    // temporary node
    FibNode<T> *p = nullptr;    // target node
    if (root == nullptr)
        return root; // protect the stability

    do
    {
        p = tmp;
        everyone_loc->push(p->loc);
        if ((p = get_everyone_loc(tmp->child, everyone_loc)) != nullptr) break;
        tmp = tmp->right;
    } while (tmp != root);

    return p;
}