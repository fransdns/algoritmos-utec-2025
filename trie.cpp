#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }
};

int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hi");

    cout << "Buscar 'hello': " << (trie.search("hello") ? "Sí" : "No") << endl;
    cout << "Buscar 'hell': " << (trie.search("hell") ? "Sí" : "No") << endl;
    cout << "Prefijo 'wo': " << (trie.startsWith("wo") ? "Sí" : "No") << endl;
    cout << "Prefijo 'he': " << (trie.startsWith("he") ? "Sí" : "No") << endl;
    
    return 0;
}
