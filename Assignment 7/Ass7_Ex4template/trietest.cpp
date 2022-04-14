//
//  trietest.cpp
//  
//
//  Created by KD on 20.03.21.
//  Modified on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie_template.cpp"
using std::cout;
using std::cin;

int main()
{
    trie<char> mytrie = trie<char>();
    AList<char> mylist1 = AList<char>(10);
    AList<char> mylist2 = AList<char>(10);
    AList<char> mylist3 = AList<char>(10);
    AList<char> mylist4 = AList<char>(10);
    AList<char> mylist5 = AList<char>(10);
    AList<char> mylist6 = AList<char>(10);
    AList<char> mylist7 = AList<char>(10);
    AList<char> mylist8 = AList<char>(10);
    AList<char> YayItsThunder = AList<char>(10);
    AList<char> YayItsThunder2 = AList<char>(10);
    AList<char> YayItsThunder3 = AList<char>(10);
    AList<char> laofu = AList<char>(10);
    AList<char> laofu2 = AList<char>(10);
    AList<char> laofu3 = AList<char>(10);
    AList<char> Chaoren = AList<char>(10);
    // Enter your dictionary words
    mylist1.append('e');
    mylist1.append('n');
    mylist1.append('t');
    mylist1.append('e');
    mylist1.append('r');
    mylist2.append('y');
    mylist2.append('o');
    mylist2.append('u');
    mylist2.append('r');
    mylist3.append('d');
    mylist3.append('i');
    mylist3.append('c');
    mylist3.append('t');
    mylist3.append('i');
    mylist3.append('o');
    mylist3.append('n');
    mylist3.append('a');
    mylist3.append('r');
    mylist3.append('y');
    mylist5.append('w');
    mylist5.append('o');
    mylist5.append('r');
    mylist5.append('d');
    mylist5.append('s');
    YayItsThunder.append('w');
    YayItsThunder.append('o');
    YayItsThunder.append('r');
    YayItsThunder.append('d');
    YayItsThunder.append('d');
    YayItsThunder2.append('w');
    YayItsThunder2.append('o');
    YayItsThunder2.append('r');
    YayItsThunder2.append('d');
    YayItsThunder2.append('d');
    YayItsThunder2.append('t');
    YayItsThunder3.append('w');
    YayItsThunder3.append('o');
    YayItsThunder3.append('r');
    YayItsThunder3.append('d');
    YayItsThunder3.append('p');
    YayItsThunder3.append('t');
    laofu.append('e');
    laofu.append('n');
    laofu.append('t');
    laofu.append('e');
    laofu.append('r');
    laofu.append('e');
    laofu2.append('e');
    laofu2.append('n');
    laofu2.append('t');
    laofu2.append('e');
    laofu2.append('r');
    laofu2.append('e');
    laofu2.append('d');
    laofu2.append('d');
    laofu3.append('e');
    laofu3.append('n');
    laofu3.append('t');
    laofu3.append('e');
    laofu3.append('r');
    laofu3.append('e');
    laofu3.append('e');
    laofu3.append('d');
    Chaoren.append('w');
    Chaoren.append('o');
    Chaoren.append('r');
    Chaoren.append('d');
    Chaoren.append('k');
    mytrie.insert(YayItsThunder);
    mytrie.insert(YayItsThunder2);
    mytrie.insert(YayItsThunder3);
    mytrie.insert(laofu);
    mytrie.insert(laofu2);
    mytrie.insert(laofu3);
    mytrie.insert(mylist1);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist1) << "\n";
    cout << mytrie.intrie(mylist2) << "\n\n";
    mytrie.insert(mylist2);
    mytrie.display();
    mytrie.insert(mylist3);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist5) << "\n";
    cout << mytrie.intrie(mylist3) << "\n\n";
    mytrie.insert(mylist5);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist5) << "\n";
    // Now test the correction functions
    mylist4.append('e');
    mylist4.append('n');
    mylist4.append('t');
    mylist4.append('e');
    mylist4.append('r');
    mylist4.append('e');
    mylist4.append('d');
    mytrie.correct2(mylist4); // We have cases : enter, entere, enteredd, entereed and only the previous two are printed.
    mylist6.append('w');
    mylist6.append('o');
    mylist6.append('r');
    mylist6.append('d');
    mytrie.correct1(mylist6); // We have cases : words, wordd, worddt, wordpt, and only the previous two are printed.
    mylist7.append('w');
    mylist7.append('o');
    mylist7.append('r');
    mylist7.append('m');
    mylist7.append('s');
    mylist8.append('l');
    mylist8.append('o');
    mylist8.append('r');
    mylist8.append('d');
    mylist8.append('s');
    mytrie.correct3(mylist7);
    mytrie.correct3(mylist8);
    mytrie.correct3(Chaoren);
    return 0;
}
