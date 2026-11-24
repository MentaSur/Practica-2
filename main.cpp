// En este main.cpp se probará que el UnsortedLinkedType.h funciona correctamente

#include "UnsortedLinkedType.h"
#include <iostream>

int main(){
    UnsortedLinkedType<char> ulk;

    
    ulk.InsertItem('a');
    ulk.InsertItem('e');
    ulk.InsertItem('l');
    ulk.Print(std::cout);
    
    ulk.DeleteItem('e');

    ulk.Print(std::cout);

    return 0;
}