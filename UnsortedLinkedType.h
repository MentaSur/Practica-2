// (Lista desordenada con estructura vinculada) Implementa una lista desorde-
// nada con una estructura vinculada. Compila y prueba tu código creando un fichero main.
// Puedes partir de la implementación vista en clase de una lista desordenada (UnsortedType.h).

#include <cstddef> // for nullptr
#include <new>     // for bad_alloc
#include <iomanip>
#include <iostream>

template<class ItemType>
struct NodeType {
    NodeType* next;
    ItemType  info;
};

// Primero se declara la clase UnsortedLinkedType, donde se indicarán los métodos que luego crearemos

template<class ItemType>
class UnsortedLinkedType {

    public: // Declaramos los métodos (esto son los accesibles públicamente)
        UnsortedLinkedType();
        ~UnsortedLinkedType();
        bool IsFull() const;
        int  LengthIs() const;
        void RetrieveItem(ItemType& item, bool& found);
        void InsertItem(ItemType item);
        void DeleteItem(ItemType item);
        void ResetList();
        void MakeEmpty();
        void GetNextItem(ItemType& item);
        void Print(std::ostream& c);
        bool detectLoop(); // Este método es el nuevo, declarado para el Ejercicio 1

    private: // Y declaramos los atributos privados (solo son accesibles usando los métodos creados)
        int length;
        NodeType<ItemType> *headPtr;
        NodeType<ItemType> *currentPtr;
};

// A continuación, inicializamos cada método declarado previamente en la clase UnsortedLinkedType

template<class ItemType>
UnsortedLinkedType<ItemType>::UnsortedLinkedType(){
    headPtr = nullptr;
    length = 0;
}

template<class ItemType>
UnsortedLinkedType<ItemType>::~UnsortedLinkedType(){
    MakeEmpty();
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::MakeEmpty(){
    NodeType<ItemType>* tmp;
    while (headPtr != nullptr) {
        tmp = headPtr;
        headPtr = headPtr->next;
        delete tmp;
    }

    length = 0;
}


template<class ItemType>
bool UnsortedLinkedType<ItemType>::IsFull() const {
    NodeType<ItemType>* tmp;

    try {
        tmp = new NodeType<ItemType>;
        delete tmp;

        return false;
    } catch (std::bad_alloc exception) {
        return true;
    }

}

template<class ItemType>
int UnsortedLinkedType<ItemType>::LengthIs() const {
    return length;
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::RetrieveItem(ItemType& item, bool& found) {
    // Pre: Key member(s) of item is initialized.
    // Post: If found, item's key matches an element's key in the
    //       list and a copy of that element has been stored in item;
    //       otherwise, item is unchanged.
    bool moreToSearch;
    NodeType<ItemType>* location = headPtr;
    found = false;

    // More to search if there is a next node
    moreToSearch = (location != nullptr);
    
    while (moreToSearch && !found) {
        if (item == location->info) {
            found = true;
            item = location->info;
        } else {
            location = location->next;
            moreToSearch = (location != nullptr);
        }
    }
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::InsertItem(ItemType item) {
    // Post: item is in the list.
    NodeType<ItemType>* location = headPtr;

    if (location != nullptr)
        while (location->next != nullptr)
            location = location->next;

    NodeType<ItemType>* newNode = new NodeType<ItemType>;
    newNode->info = item;
    newNode->next = nullptr;

    if (location == nullptr)
        headPtr = newNode;
    else
        location->next = newNode;
    
    length++;
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::DeleteItem(ItemType item) {
    // Pre:  item's key has been initialized.
    //       An element in the list has a key that matches item's.
    // Post: No element in the list has a key that matches item's.
    NodeType<ItemType>* location = headPtr;
    NodeType<ItemType>* prev = headPtr;

    while (item != location->info) {
        prev = location;
        location = location->next;
    }

    //  ----- prev ----       ---   loc  ----       -- loc->next --
    //  | info | next | <---> | info | next | <---> | info | next | 
    //  ---------------       ---------------       ---------------
    
    if (location == headPtr)
        headPtr = location->next; // location es el primer elemento
    else
        prev->next = location->next;

    delete location;
        
    length--;
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::ResetList() {
    // Post: currentPos has been initialized.
    currentPtr = headPtr;
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::GetNextItem(ItemType& item) {
    // Pre:  No transformer has been executed since last call
    // Post: item is current item.
    //       Current position has been updated.
    item = currentPtr->info;
    currentPtr = currentPtr->next;
}

template<class ItemType>
void UnsortedLinkedType<ItemType>::Print(std::ostream& c) {
    ItemType tmp;
    c << "List length: " << length << std::endl;

    ResetList();
    for (int i=0; i < length; i++) {
        c << "- node: ";
        if (i==0 or i==length-1)
            c << std::setw(12);
        else
            c << std::setw(12);
        c << currentPtr;   
        GetNextItem(tmp);

        c << " -";
        if (i!=length-1)
            c << "       ";
        
    }
    c << std::endl;

    ResetList();
    for (int i=0; i < length; i++) {
        c << "| " << currentPtr->info << " | " << currentPtr->next << " |";
        GetNextItem(tmp);
        if (i!=length-1)
            c << " <---> ";
    }
    c << std::endl << std::endl;


}