#include <iostream>
using namespace std;

// Nodo de la lista enlazada
struct Node {
    int data;       // Dato almacenado en el nodo
    Node* next;     // Puntero al siguiente nodo

    // Constructor para facilitar la creación de nodos
    Node(int value) : data(value), next(nullptr) {}
};

// Clase para manejar la lista enlazada
class LinkedList {
private:
    Node* head;  // Puntero al primer nodo de la lista

public:
    // Constructor: inicializa la lista vacía
    LinkedList() : head(nullptr) {}

    // Destruir todos los nodos al final
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insertar un nodo al inicio de la lista
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insertar un nodo al final de la lista
    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Insertar un nodo en una posición específica
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "La posición debe ser mayor o igual a 1.\n";
            return;
        }

        if (position == 1) {
            insertAtHead(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* current = head;

        for (int i = 1; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "La posición es mayor que la longitud de la lista.\n";
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Borrar un nodo en una posición específica
    void deleteAtPosition(int position) {
        if (position < 1 || head == nullptr) {
            cout << "Posición inválida o lista vacía.\n";
            return;
        }

        if (position == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        for (int i = 1; i < position - 1 && current->next != nullptr; i++) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "La posición es mayor que la longitud de la lista.\n";
            return;
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    // Buscar un valor en la lista
    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Invertir la lista enlazada
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    // Encontrar el valor medio de la lista enlazada
    int findMiddle() {
        if (head == nullptr) {
            throw runtime_error("La lista está vacía.");
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    // Detectar si hay un ciclo en la lista enlazada
    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }

    // Imprimir todos los elementos de la lista
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }
};

// Ejemplo de uso
int main() {
    LinkedList list;

    // Insertar elementos
    list.insertAtHead(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtPosition(15, 2); // Insertar 15 en la posición 2

    // Imprimir lista
    cout << "Lista inicial: ";
    list.printList();

    // Borrar un elemento
    list.deleteAtPosition(3); // Eliminar el elemento en la posición 3
    cout << "Después de borrar en posición 3: ";
    list.printList();

    // Buscar un elemento
    int valueToSearch = 15;
    if (list.search(valueToSearch)) {
        cout << valueToSearch << " encontrado en la lista.\n";
    } else {
        cout << valueToSearch << " no encontrado en la lista.\n";
    }

    // Invertir la lista
    list.reverse();
    cout << "Lista invertida: ";
    list.printList();

    // Encontrar el valor medio
    try {
        int middle = list.findMiddle();
        cout << "Valor medio: " << middle << "\n";
    } catch (runtime_error& e) {
        cout << e.what() << "\n";
    }

    // Detectar ciclo
    cout << (list.hasCycle() ? "La lista tiene un ciclo." : "La lista no tiene un ciclo.") << "\n";

    return 0;
}
