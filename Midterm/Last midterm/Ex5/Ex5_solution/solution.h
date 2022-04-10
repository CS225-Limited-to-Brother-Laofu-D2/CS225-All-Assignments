#include "assert.h" 
#include "dlist_f.h"

template<class T> void DList<T>::reverse(void){
    node<T> *cur;
    node<T> *next;
    node<T> *prev;
    cur = dummy;
    
    do{
        next = cur->getnext();
        prev = cur->getprevious();

        cur->setnext(prev);
        cur->setprevious(next);

        cur = next;
    }while (cur != dummy);

    return ;

}