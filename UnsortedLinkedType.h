// (Lista desordenada con estructura vinculada) Implementa una lista desorde-
// nada con una estructura vinculada. Compila y prueba tu código creando un fichero main.
// Puedes partir de la implementación vista en clase de una lista desordenada (UnsortedType.h).

#include <cstddef> // for nullptr
#include <new>     // for bad_alloc
#include <iomanip>
#include <iostream>
using namespace std;

// Primero, se define una Plantilla, formada por nodos enlazados en sólo una dirección
template<class ItemType>
struct NodeType { // Creamos una estructura NodeType que contendrá 2 atributos distintos para cada uno
    NodeType* next; // guarda la dirección del siguiente dato que hay tras el actual
    ItemType  info; // guarda el dato actual con el que trabajamos
};

//
// Primero se declara la clase UnsortedLinkedType, donde se indicarán los métodos que luego crearemos
//
template<class ItemType>
class UnsortedLinkedType {

    public: // Declaramos los métodos (esto son los accesibles públicamente)
        UnsortedLinkedType(); // Este constructor sólo se ejecuta 1 vez al inicio del programa

        ~UnsortedLinkedType(); // Este destructor usa MakeEmpty para vaciar los nodos tras hacer un
                               // "return 0" en el main.cpp, vaciándolos con "delete" uno por uno
        bool IsFull() const;
        int  LengthIs() const;
        void RetrieveItem(ItemType& item, bool& found);
        void InsertItem(ItemType item);
        void DeleteItem(ItemType item);
        void ResetList();
        void MakeEmpty();
        void GetNextItem(ItemType& item);
        void Print(std::ostream& c);
        bool detectLoop(int& pos); // Este método es el nuevo, declarado para el Ejercicio 1

    private: // Y declaramos los atributos privados (solo son accesibles usando los métodos creados)
        int length;
        NodeType<ItemType> *headPtr;
        NodeType<ItemType> *currentPtr;
};

//
// A continuación, inicializamos cada método declarado previamente en la clase UnsortedLinkedType
//
//=====================================================================================================================
template<class ItemType> // Constructor de atributos privados, se ejecuta al crear una lista nueva
UnsortedLinkedType<ItemType>::UnsortedLinkedType(){
    headPtr = nullptr; // Inicializa el puntero apuntando a ningún nodo
    length = 0; // Como el programa se inicia, la longitud inicial de la lista es 0
}

//=====================================================================================================================
template<class ItemType> // Destructor para cuando la lista se elimina (tras acabar el main.cpp)
UnsortedLinkedType<ItemType>::~UnsortedLinkedType(){
    MakeEmpty(); // Llama al MakeEmpty para liberar la memoria reservada/ocupada por los nodos
}

//=====================================================================================================================
template<class ItemType> // Método para vaciar los nodos usados uno a uno
void UnsortedLinkedType<ItemType>::MakeEmpty(){
    NodeType<ItemType>* temporal; // Creamos un puntero temporal donde se vaciará el Primer Puntero
    while (headPtr != nullptr) { // Mientras que el Primer Puntero no sea nulo (no tenga direcciones)
        temporal = headPtr; // El puntero temporal guarda la dirección del Primer Nodo
        headPtr = headPtr->next; // Luego, mueve el Primer Nodo al siguiente nodo
        delete temporal; // Y la dirección donde estuvo el Primer Nodo, se borra
    }
    // Una vez que el Primer puntero queda vacío, se ajusta la longitud a 0 (ya que se vació todo)
    length = 0;
}

//=====================================================================================================================
template<class ItemType> // Método que indicará si la lista está llena o no, osea si hay memoria o no
bool UnsortedLinkedType<ItemType>::IsFull() const {
    NodeType<ItemType>* temporal;

    try { // Al ser memoria dinámica, tratará de reservar un nodo temporal
        temporal = new NodeType<ItemType>;
        delete temporal; // Para luego borrarlo inmediatamente, si se pudo hacer, devuelve False
                         // indicando que la lista NO está llena
        return false;

    } catch (std::bad_alloc exception) { // Pero si el programa lanza una excepción, es porque no pudo
                                         // reservar memoria, indicando que la lista está llena
        return true;   // al estar llena, devuelve True
    }
}

//=====================================================================================================================
template<class ItemType> // Método que devuelve la longitud de la lista
int UnsortedLinkedType<ItemType>::LengthIs() const {
    return length; // Simple, solo devuelve el valor de la longitud de la lista
}

//=====================================================================================================================
template<class ItemType> // Método que busca un item en la lista, y devuelve true si lo ha encontrado
void UnsortedLinkedType<ItemType>::RetrieveItem(ItemType& item, bool& found) {

    bool moreToSearch; // Creamos un booleano que indicará si debemos seguir buscando o no
    NodeType<ItemType>* location = headPtr; // Creamos un puntero que buscará el item, desde el 1º nodo
    found = false; // Inicializamos el booleano en False, ya que aún no se encontró el item

    // Si el puntero location no es nulo, es porque podemos seguir buscando el item por los nodos
    moreToSearch = (location != nullptr);
    
    while (moreToSearch && !found) { // Mientras que podamos seguir buscando y no se haya encontrado...
        if (item == location->info) { // Si el item a buscar es igual al item actual del nodo
            found = true; // cambiamos el booleano a True porque ya se encontró
            item = location->info; // Y guardamos el nodo actual en el item
        } else { // Si aún no se encontró...
            location = location->next; // Pasamos al siguiente nodo a revisar
            moreToSearch = (location != nullptr); // y comprobamos si podemos seguir buscando o no
        }
    }
}

//=====================================================================================================================
template<class ItemType> // Método que permite insertar en la lista un nuevo item
void UnsortedLinkedType<ItemType>::InsertItem(ItemType item) {

    // Iremos 1 por 1 mirando cada nodo hasta llegar a uno que esté vacío
    NodeType<ItemType>* location = headPtr; //Creamos un puntero que se inicia en el Primer nodo

    if (location != nullptr) // Si el nodo actual no está vacío...
        while (location->next != nullptr) // mientras que el siguiente nodo no esté vacío
            location = location->next; // iremos saltando de nodo en nodo hasta llegar a uno vacío

    // Una vez llegue al último nodo de la lista, reserva memoria para el nuevo eslabón
    NodeType<ItemType>* newNode = new NodeType<ItemType>;
    newNode->info = item; // dentro del eslabón, el nodo donde está actualmente será el item a meter
    newNode->next = nullptr; // y el siguiente nodo al actual estará vacío

    if (location == nullptr) // Si llegamos a un nodo que está vacío
        headPtr = newNode; // hacemos que el primer nodo apunte ahora al nuevo nodo

    else // Y si no está vacío, se engancha el último nodo al nuevo
        location->next = newNode;
    
    length++; // Por último, sumamos 1 a la longitud total de la lista
}

//=====================================================================================================================
template<class ItemType> // Método que permite borrar de la lista un item
void UnsortedLinkedType<ItemType>::DeleteItem(ItemType item) {

    NodeType<ItemType>* location = headPtr; // Creamos un puntero que se inicia en el Primer nodo
    NodeType<ItemType>* prev = headPtr; // Y otro que siempre apunte al anterior a location

    while (item != location->info) { // Mientras que el item sea distinto al actual en location
        prev = location; // movemos el puntero previo al actual
        location = location->next; // y el actual al siguiente, moviendo ambos punteros 1 vez
    }

    //  ----- prev ----       ---   loc  ----       -- loc->next --
    //  | info | next | <---> | info | next | <---> | info | next | 
    //  ---------------       ---------------       ---------------
    
    // Ahora, una vez encontrado el objeto, pasamos a ver 2 posibilidades
    if (location == headPtr){ // Si el nodo actual (a borrar) es igual al primer nodo
        headPtr = location->next; // hacemos que el primer nodo se desplace al siguiente del location
    }
        
    else { // Pero si es otro cualquiera, el nodo anterior pasará al que sigue del location
        prev->next = location->next;
    }

    delete location; // Por último, borramos el nodo location (donde está el item a borrar)
    length--; // Y acortamos la longitud a 1 menos
}

//=====================================================================================================================
template<class ItemType> // Reinicia el puntero cursor para que empieza de vuelta en el primer nodo
void UnsortedLinkedType<ItemType>::ResetList() {

    currentPtr = headPtr; // El cursor se reinicia al primer nodo de la lista
}

//=====================================================================================================================
template<class ItemType> // Método que guarda el siguiente item
void UnsortedLinkedType<ItemType>::GetNextItem(ItemType& item) {

    item = currentPtr->info; // Guarda el dato del nodo actual en item
    currentPtr = currentPtr->next; // Y pasa al siguiente nodo
}

//=====================================================================================================================
template<class ItemType> // Método que imprime por pantalla la lista completa
void UnsortedLinkedType<ItemType>::Print(ostream& c) {

    ItemType temporal; // Creamos a un temporal 
    // Y luego, mostramos por pantalla la longitud de la lista, antes de empezar con ella
    c << "La longitud de la lista es: " << length << endl;

    ResetList(); // Primero de todo, reiniciamos el cursor de la lista a la primera posición
    for (int i=0; i < length; i++) { // Abrimos un bucle que se repita hasta igualar la longitud
        c << "- node: "; // Indica que a partir de aquí, se imprimirán los nodos
        if (i==0 or i==length-1){ // Si i es igual a 0 ó igual a longitud - 1...
            c << setw(12); // Reserva 12 carácteres para el dato que se vaya a imprimir
        }
        else { // Si i no es ninguno, igualmente reservará 12 carácteres
            c << setw(12);
        }
        c << currentPtr;  // Imprimimos por pantalla el primer elemento de la lista 
        GetNextItem(temporal); // Y avanzamos al siguiente elemento

        c << " -";
        if (i!=length-1){ // Si i es distinto de longitud - 1
            c << "       "; // Imprime un espacio en pantalla, para separar los nodos visualmente
        }
        
    }
    c << endl;

    ResetList(); // Volvemos a reiniciar el cursos de vuelta al inicio
    for (int i=0; i < length; i++) { // Y abrimos otro bucle igual al anterior

        // Imprimimos por pantalla el elemento actual y el que le sigue en el cursor
        c << "| " << currentPtr->info << " | " << currentPtr->next << " |";
        GetNextItem(temporal); // Y movemos el cursor al siguiente item

        if (i!=length-1){ // Si i es distinto de longitud - 1
            c << " <---> "; // Dibujo por pantalla flechas que conectará ambos nodos visualmente
        }
    }
    c << endl << endl; // y acabamos cerrando las líneas


}

//=====================================================================================================================
// EJERCICIO 1: Diseñar un método para detectar un bucle en la lista. Tendrá un bucle si el puntero del
// último nodo apunta a cualquier otro nodo en la lista o a sí mismo

template<class ItemType> // Método que detecta si la lista contiene algún bucle o no
bool UnsortedLinkedType<ItemType>::detectLoop(int& pos){

    NodeType<ItemType>* location = headPtr; // Creamos un puntero para desplazarnos por los nodos
    
    for ( int i = 0; i < length && location != nullptr; i++){ // Hasta que no lleguemos al final...
        location = location->next; // Vamos a ir avanzando 1 por 1 por cada nodo hasta el último
    }

    if (location != nullptr){ // Si en el último nodo miramos al siguiente y no está vacío, es porque
                              // está vinculado a algún nodo por los que pasamos antes (o él mismo)
        NodeType<ItemType>* nodo_bucle = location; // Creamos un nodo que se quedará quieto en ese nodo

        pos = 0; // iniciamos el entero de posición a 0
        location = headPtr; // y reseteamos al inicio el puntero para desplazarse por nodos

        while (location != nodo_bucle && pos < length){ // Mientras que el puntero location sea distinto
                // sea distinto al nodo que se vincula con alguno...
                location = location->next; // Avanzaremos al siguiente nodo para comparar
                pos++; // Y sumamos 1 a la posición donde estamos
        }
        return true; // En principio, como el último nodo no era nulo, tarde o temprano encontrará
                     // al nodo con el que se vincula el último, por lo que seguro se será cierto

    } else { // Pero en el caso de que el último nodo apuntara al vacío, es porque no hay bucle
        pos = -1; // Indicamos que la posición es -1 (indicando que no hay bucle)
        return false; // Y devolvemos False (no hay ningún bucle detectado)
    }
}