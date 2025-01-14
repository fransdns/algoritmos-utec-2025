/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if(!head) return nullptr;
        Node* current = head; 
        while(current){
            if(current->child){
                Node* next =current->next;
                Node* child = flatten(current->child);
                current->next = child;
                child->prev = current;
                current->child = nullptr; 
                while(current->next){
                    current = current->next; 
                }
                if(next){
                    current->next = next; 
                    next->prev = current; 
                }
            }
            current = current->next; 
        }
            return head;
        }
        

};