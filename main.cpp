// En este main.cpp se probará que el UnsortedLinkedType.h funciona correctamente

#include "UnsortedLinkedType.h"
#include <iostream>
using namespace std;

int main(){
    UnsortedLinkedType<char> ulk;
    ulk.InsertItem('a');
    ulk.InsertItem('e');
    ulk.InsertItem('l');

    // He borrado las pruebas del método "Print" y el "DeleteItem" para poder probar bien estos 2 métodos
    // En la primera ejecución, pon "posicion = 0", y "k = 2"
    // Y en la segunda ejecución, pon "posicion = 1", y "k = 3"

// ===========================================================================================================
    // Primero, probaremos el ejercicio 1, el método detectLoop()
    int opcion; // debemos saber la posicion donde apunta el puntero al bucle (por eso usamos int &pos)

    cout << "introduce una posicion, 0 o 1: ";
    cin >> opcion; // Con 0 seguro que no detectará bucles, con 1 si habrá bucle

    if (opcion == 1){  // si le ponemos 1, forzaremos un bucle en donde 'l' apunta a la posicon 1 'e'
        ulk.createLoop(1); // usamos el método auxiliar para provocar un bucle
    }
    // Si no le ponemos 1, pues no forzaremos ningun bucle

    int posicion;
    bool ExisteUnBucle = ulk.detectLoop(posicion);

    if (ExisteUnBucle){ // Si el método devuelve True, imprime que SI HAY BUCLE y el dónde está
        cout << "Existe un bucle en la posicion " << posicion << endl << endl;
    } else { // y si devuelve False, imprime que NO HAY BUCLE
        cout << "No existe ningun bucle, que pena" << endl << endl;
    }

// ===========================================================================================================
    // y Segundo, probaremos el ejercicio 2, el método reverseKGroup()

    // Vamos a probar con otra lista aparte
    UnsortedLinkedType<char> listaRevertir;
    listaRevertir.InsertItem('A');
    listaRevertir.InsertItem('E');
    listaRevertir.InsertItem('C');
    listaRevertir.InsertItem('L');  // En teoría, el orden actual de la lista es (A, E, C , L)

    int k;
    cout << "introduce un valor de k, 2 o 3: ";
    cin >> k; // Vamos a probar con 2 y con 3 elementos (en 1 ejecucion ponemos 2, y en la otra 3)

    listaRevertir.reverseKGroup(k); // le pasamos de k que hayamos metido

    listaRevertir.Print(cout); // Y comprobamos a ver que tal salío (espero que bien)

    return 0; // Si todo salío como es debido, genial, y si no, pues que faena
}