#include <iostream>
#include <queue>
using namespace std;

// Definición de un nodo del BST
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Clase para el BST
class BST {
public:
    Node* root;
    
    BST() : root(nullptr) {}

    // Insertar un valor en el BST
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    // Recorrido inorder (LNR)
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    // Recorrido preorder (NLR)
    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    // Recorrido postorder (LRN)
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    // Recorrido por niveles (BFS)
    void levelOrder() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            cout << node->data << " ";
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
};

int main() {
    BST tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int val : values)
        tree.insert(val);

    cout << "Inorder: ";
    tree.inorder();

    cout << "Preorder: ";
    tree.preorder();

    cout << "Postorder: ";
    tree.postorder();

    cout << "Level Order: ";
    tree.levelOrder();

    return 0;
}
