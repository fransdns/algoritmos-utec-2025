/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        int size=0;
        if (head==nullptr){
            return false;
        }else{
            ListNode* temp = head;
            while(temp->next!=nullptr){
                temp=temp->next;
                size++;
                //cout<<"el size es:"<<size; 
            }
        }
        int mitad=0;
        if(size%2!=0){
            mitad=(size/2)+1;
        }else{
            mitad=size/2;
        }
        //int mitad=(size/2);
        //cout<<"mitad: "<<mitad;
        //avazamos hasta la mitad
        ListNode* temp = head; 
        for(int i=0; i<mitad;i++){ 
            temp=temp->next;
        }//cout<<"el temporal es: "<<temp->val<<endl;

        //invertimos la mitad
        ListNode* head_2 = temp; 

        ListNode* prev = nullptr;
        ListNode* current = head_2;
        ListNode* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head_2 = prev;

        //comparamos las mitades
        for(int i=0;i<mitad;i++){
            //cout<<"head 2: "<<head_2<<endl;
            if(head_2->val==head->val){
                //cout<<"head 2: "<<head_2<<endl;
                //cout<<"head 1: "<<head<<endl;
                head_2=head_2->next;
                head=head->next; 
            }else{
                return false; 
            }
        }
        return true;
    }
};