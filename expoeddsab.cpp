#include <iostream>
#include <malloc.h>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
};

// Insertar en el árbol
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->dato = valor;
        nuevo->izq = nuevo->der = NULL;
        return nuevo;
    }
    if (valor < raiz->dato)
        raiz->izq = insertar(raiz->izq, valor);
    else
        raiz->der = insertar(raiz->der, valor);
    return raiz;
}

// Recorrido in-orden para guardar en arreglo
void guardarInOrden(Nodo* raiz, int arr[], int* i) {
    if (raiz == NULL) return;
    guardarInOrden(raiz->izq, arr, i);
    arr[(*i)++] = raiz->dato;
    guardarInOrden(raiz->der, arr, i);
}

// Crear árbol balanceado desde arreglo
Nodo* construirBalanceado(int arr[], int inicio, int fin) {
    if (inicio > fin) return NULL;
    int mid = (inicio + fin) / 2;
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = arr[mid];
    nodo->izq = construirBalanceado(arr, inicio, mid - 1);
    nodo->der = construirBalanceado(arr, mid + 1, fin);
    return nodo;
}

// Mostrar in-orden
void inOrden(Nodo* raiz) {
    if (raiz == NULL) return;
    inOrden(raiz->izq);
    cout << raiz->dato << " ";
    inOrden(raiz->der);
}

int contarNodos(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

int main() {
    Nodo* raiz = NULL;

    // Árbol desbalanceado (orden creciente)
    raiz = insertar(raiz, 1);
    raiz = insertar(raiz, 2);
    raiz = insertar(raiz, 3);
    raiz = insertar(raiz, 4);
    raiz = insertar(raiz, 5);

    cout << "Arbol original (in-orden): ";
    inOrden(raiz);
    cout << endl;

    // Rebalancear
    int n = contarNodos(raiz);
    int* arr = (int*)malloc(n * sizeof(int));
    int i = 0;
    guardarInOrden(raiz, arr, &i);

    Nodo* raizBalanceada = construirBalanceado(arr, 0, n - 1);

    cout << "Arbol balanceado (in-orden): ";
    inOrden(raizBalanceada);
    cout << endl;

    return 0;
}
