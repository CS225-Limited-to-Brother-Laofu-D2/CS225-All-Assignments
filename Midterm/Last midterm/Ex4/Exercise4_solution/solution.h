#include "alist_f.h"
/****************************************************************************/
/*********************************** TODO ***********************************/
/******************** Start your code in the following **********************/
/****************************************************************************/

/* Exercise 4, (i) */
template<class T> AList<T>*  AList<T>::select(T value){
    AList<T>* res = new AList<T>;      /* return sublist */

    for (int i = 1; i <= this->getlength(); i++){
        if (this->getitem(i) <= value){
            res->append(this->getitem(i));
        }
    }

    return res;
}

/* Exercise 4, (ii) */
template<class T> T AList<T>::median(void){
    this->bsort();
    int half_length = (1 + this->getlength()) >> 1;
    return getitem(half_length);
}
    
    
/* Exercise 4, (ii) */    
template<class T> AList<T>* AList<T>::select_low(void){
    return this->select(this->median());
}