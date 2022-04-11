#include "assert.h" 
#include "dlist_f.h"

template<class T> void DList<T>::reverse(void){
    node<T>* temp;
    temp = this->last();
    node<T>* next = dummy->getnext();
    node<T>* previous = dummy->getprevious();
    dummy->setnext(previous);
    dummy->setprevious(next);
    while(temp != dummy)
    {
        node<T>* original_next = temp->getnext();
        node<T>* original_previous = temp->getprevious();
        temp->setnext(original_previous);
        temp->setprevious(original_next);
        temp=original_previous;
    }
    return;

}