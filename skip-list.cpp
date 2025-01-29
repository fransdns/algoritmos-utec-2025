#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

// Definimos la estructura de un nodo en la Skip List
struct Node {
    int key; // Clave del nodo
    Node **forward; // Arreglo de punteros a los niveles del nodo
    Node(int key, int level) {
        this->key = key;
        forward = new Node*[level + 1]; // Creamos los punteros para cada nivel
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr; // Inicializamos los punteros a nullptr
        }
    }
};

// Clase de la Skip List
class SkipList {
    int maxLevel; // Nivel máximo permitido en la lista
    float probability; // Probabilidad usada para determinar el nivel del nodo
    int currentLevel; // Nivel actual de la lista
    Node *header; // Nodo cabeza de la lista

public:
    SkipList(int maxLevel, float probability) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        header = new Node(-1, maxLevel); // Nodo cabeza con clave -1
    }

    // Función para generar un nivel aleatorio basado en la probabilidad
    int randomLevel() {
        int level = 0;
        while ((rand() / (float)RAND_MAX) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

    // Insertar un elemento en la Skip List
    void insert(int key) {
        Node *current = header;
        Node *update[maxLevel + 1]; // Array para actualizar los punteros
        
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        int newLevel = randomLevel(); // Determinar el nivel del nuevo nodo
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }
        
        Node *newNode = new Node(key, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // Buscar un elemento en la Skip List
    bool search(int key) {
        Node *current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return (current != nullptr && current->key == key);
    }

    // Eliminar un elemento de la Skip List
    void remove(int key) {
        Node *current = header;
        Node *update[maxLevel + 1];
        
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        if (current != nullptr && current->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
        }
    }

    // Imprimir la Skip List
    void display() {
        for (int i = currentLevel; i >= 0; i--) {
            Node *current = header->forward[i];
            cout << "Level " << i << ": ";
            while (current != nullptr) {
                cout << current->key << " ";
                current = current->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand(time(nullptr)); // Inicializar la semilla aleatoria
    SkipList skiplist(5, 0.5); // Crear una Skip List con nivel máximo 5 y probabilidad 0.5
    
    skiplist.insert(3);
    skiplist.insert(6);
    skiplist.insert(7);
    skiplist.insert(9);
    skiplist.insert(12);
    skiplist.insert(19);
    skiplist.insert(17);
    skiplist.insert(26);
    skiplist.insert(21);
    skiplist.insert(25);
    
    cout << "Skip List después de insertar elementos:" << endl;
    skiplist.display();
    
    cout << "Buscando el elemento 19: " << (skiplist.search(19) ? "Encontrado" : "No encontrado") << endl;
    
    skiplist.remove(19);
    cout << "Skip List después de eliminar el elemento 19:" << endl;
    skiplist.display();
    
    return 0;
}
