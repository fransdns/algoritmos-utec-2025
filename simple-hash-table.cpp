#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class HashTable {
private:
    vector<list<pair<int, string>>> table; // Vector de listas enlazadas para encadenamiento
    int size; // Tamaño de la tabla hash

    // Función hash: calcula el índice para una clave
    int hashFunction(int key) const {
        return key % size;
    }

public:
    // Constructor
    HashTable(int tableSize) : size(tableSize) {
        table.resize(size); // Redimensiona el vector según el tamaño dado
    }

    // Insertar clave-valor en la tabla hash
    void insert(int key, const string& value) {
        int index = hashFunction(key); // Calcula el índice
        for (auto& pair : table[index]) {
            if (pair.first == key) { // Si la clave ya existe, actualiza el valor
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value); // Inserta el nuevo par clave-valor
    }

    // Buscar un valor dado su clave
    string search(int key) const {
        int index = hashFunction(key); // Calcula el índice
        for (const auto& pair : table[index]) {
            if (pair.first == key) { // Si encuentra la clave, retorna el valor
                return pair.second;
            }
        }
        return "No encontrado"; // Si no encuentra la clave
    }

    // Eliminar una clave de la tabla hash
    void remove(int key) {
        int index = hashFunction(key); // Calcula el índice
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) { // Si encuentra la clave, la elimina
                bucket.erase(it);
                return;
            }
        }
        cout << "Clave no encontrada: " << key << endl;
    }

    // Mostrar la tabla hash
    void display() const {
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Crear una tabla hash con 7 buckets
    HashTable hashTable(7);

    // Insertar elementos
    hashTable.insert(10, "Alice");
    hashTable.insert(20, "Bob");
    hashTable.insert(30, "Charlie");
    hashTable.insert(15, "Diana");

    // Mostrar la tabla
    cout << "Tabla hash después de las inserciones:" << endl;
    hashTable.display();

    // Buscar elementos
    cout << "\nBuscando claves:" << endl;
    cout << "Clave 20: " << hashTable.search(20) << endl;
    cout << "Clave 15: " << hashTable.search(15) << endl;
    cout << "Clave 25: " << hashTable.search(25) << endl;

    // Eliminar elementos
    cout << "\nEliminando claves:" << endl;
    hashTable.remove(20);
    hashTable.remove(25);

    // Mostrar la tabla después de eliminar
    cout << "\nTabla hash después de las eliminaciones:" << endl;
    hashTable.display();

    return 0;
}
