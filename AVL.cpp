#include <iostream>
using namespace std;

// Nodo del árbol AVL
struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(int valor) : dato(valor), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

// Clase para el Árbol AVL
class AVL {
public:
    Nodo* raiz;

    AVL() : raiz(nullptr) {}

    int obtenerAltura(Nodo* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int obtenerBalance(Nodo* nodo) {
        return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
    }

    Nodo* rotacionDerecha(Nodo* y) {
        Nodo* x = y->izquierda;
        Nodo* T2 = x->derecha;
        x->derecha = y;
        y->izquierda = T2;
        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        return x;
    }

    Nodo* rotacionIzquierda(Nodo* x) {
        Nodo* y = x->derecha;
        Nodo* T2 = y->izquierda;
        y->izquierda = x;
        x->derecha = T2;
        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        return y;
    }

    Nodo* insertar(Nodo* nodo, int valor) {
        if (!nodo) return new Nodo(valor);
        if (valor < nodo->dato)
            nodo->izquierda = insertar(nodo->izquierda, valor);
        else if (valor > nodo->dato)
            nodo->derecha = insertar(nodo->derecha, valor);
        else
            return nodo; // No se permiten valores duplicados

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && valor < nodo->izquierda->dato)
            return rotacionDerecha(nodo);
        if (balance < -1 && valor > nodo->derecha->dato)
            return rotacionIzquierda(nodo);
        if (balance > 1 && valor > nodo->izquierda->dato) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && valor < nodo->derecha->dato) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    Nodo* nodoMinimo(Nodo* nodo) {
        while (nodo->izquierda)
            nodo = nodo->izquierda;
        return nodo;
    }

    Nodo* eliminar(Nodo* nodo, int valor) {
        if (!nodo) return nodo;
        if (valor < nodo->dato)
            nodo->izquierda = eliminar(nodo->izquierda, valor);
        else if (valor > nodo->dato)
            nodo->derecha = eliminar(nodo->derecha, valor);
        else {
            if (!nodo->izquierda || !nodo->derecha) {
                Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
                if (!temp) {
                    temp = nodo;
                    nodo = nullptr;
                } else
                    *nodo = *temp;
                delete temp;
            } else {
                Nodo* temp = nodoMinimo(nodo->derecha);
                nodo->dato = temp->dato;
                nodo->derecha = eliminar(nodo->derecha, temp->dato);
            }
        }

        if (!nodo) return nodo;

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0)
            return rotacionDerecha(nodo);
        if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecha) <= 0)
            return rotacionIzquierda(nodo);
        if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }
        return nodo;
    }

    void recorridoEnOrden(Nodo* nodo) {
        if (!nodo) return;
        recorridoEnOrden(nodo->izquierda);
        cout << nodo->dato << " ";
        recorridoEnOrden(nodo->derecha);
    }
};

int main() {
    AVL arbol;
    arbol.raiz = arbol.insertar(arbol.raiz, 10);
    arbol.raiz = arbol.insertar(arbol.raiz, 20);
    arbol.raiz = arbol.insertar(arbol.raiz, 30);
    arbol.raiz = arbol.insertar(arbol.raiz, 40);
    arbol.raiz = arbol.insertar(arbol.raiz, 50);
    arbol.raiz = arbol.insertar(arbol.raiz, 25);

    cout << "Recorrido en orden del árbol AVL: ";
    arbol.recorridoEnOrden(arbol.raiz);
    cout << endl;

    arbol.raiz = arbol.eliminar(arbol.raiz, 30);
    cout << "Después de eliminar 30: ";
    arbol.recorridoEnOrden(arbol.raiz);
    cout << endl;

    return 0;
}
