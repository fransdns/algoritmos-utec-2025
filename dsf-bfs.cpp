#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Definición de un nodo del árbol
struct TreeNode {
    int val;
    vector<TreeNode*> children;
    TreeNode(int x) : val(x) {}
};

// Clase que representa un árbol
class Tree {
public:
    TreeNode* root;

    Tree(int rootVal) {
        root = new TreeNode(rootVal);
    }

    // Recorrido en preorden (raíz - hijos izq a der)
    void preOrder(TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        for (TreeNode* child : node->children) {
            preOrder(child);
        }
    }

    // Recorrido en postorden (hijos izq a der - raíz)
    void postOrder(TreeNode* node) {
        if (!node) return;
        for (TreeNode* child : node->children) {
            postOrder(child);
        }
        cout << node->val << " ";
    }

    // BFS (recorrido por niveles)
    void bfs() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            cout << node->val << " ";
            for (TreeNode* child : node->children) {
                q.push(child);
            }
        }
    }

    // DFS iterativo usando una pila
    void dfs() {
        if (!root) return;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* node = s.top(); s.pop();
            cout << node->val << " ";
            for (int i = node->children.size() - 1; i >= 0; --i) {
                s.push(node->children[i]);
            }
        }
    }
};

int main() {
    Tree tree(1);
    tree.root->children.push_back(new TreeNode(2));
    tree.root->children.push_back(new TreeNode(3));
    tree.root->children.push_back(new TreeNode(4));
    tree.root->children[0]->children.push_back(new TreeNode(5));
    tree.root->children[0]->children.push_back(new TreeNode(6));
    tree.root->children[1]->children.push_back(new TreeNode(7));
    tree.root->children[2]->children.push_back(new TreeNode(8));
    
    cout << "Preorden: ";
    tree.preOrder(tree.root);
    cout << "\nPostorden: ";
    tree.postOrder(tree.root);
    cout << "\nBFS: ";
    tree.bfs();
    cout << "\nDFS: ";
    tree.dfs();
    
    return 0;
}
