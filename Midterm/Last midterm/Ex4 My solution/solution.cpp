#include "alist_f.h"
/****************************************************************************/
/*********************************** TODO ***********************************/
/******************** Start your code in the following **********************/
/****************************************************************************/

/* Exercise 4, (i) */
template<class T> AList<T>*  AList<T>::select(T value){
    AList<T>* sublist;
    sublist = new AList<T>;
    for(int i = 1 ; i <= this->getlength() ; i++)
    {
        T compare_value = this->getitem(i);
        if(compare_value <= value)
        {
            sublist->append(compare_value);
        }
    }
    return sublist;
}

/* Exercise 4, (ii) */
template<class T> T AList<T>::median(void){
    this->bsort();
    T median_number;
    if(this->getlength() % 2 == 1) // Odd
    {
        median_number = getitem((getlength()+1)/2);
    }
    else // even
    {
        median_number = (getitem((getlength())/2)+getitem((getlength())/2 + 1)) / 2;
    }
    return median_number;

}
    
    
/* Exercise 4, (ii) */    
template<class T> AList<T>* AList<T>::select_low(void)
{
    T median_number = median();
    AList<T>* sublist;
    sublist = new AList<T>;
    sublist = select(median_number);
    return sublist;
}
