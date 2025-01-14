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
        Node* tail = nullptr;  
        while(current){
            if(current->child){
                Node* next = current->next;
                current->next = current->child; 
                current->child = next; 
                current->next->prev = current; 

            }if(current->next == nullptr){
                tail = current; 
            }
            current = current->next; 
        }
        Node* temporal=tail;
        while(temporal){
            if(temporal->child){
                tail->next=temporal->child;
                temporal->child->prev = tail;
                while(tail->next){
                    tail=tail->next;
                }
                temporal->child = nullptr;
            }
            temporal = temporal->prev;
        }


            return head;
        }
        

};