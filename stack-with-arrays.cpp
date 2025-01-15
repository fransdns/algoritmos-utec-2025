#include <iostream>

using namespace std;


class stack {
private:
    int top = -1;
    int capacity = 0;
    int *arr;

public:
    stack(int capacity) {
        this->capacity = capacity;
        arr = new int[capacity];

    }
    void push(int value) {
        if ((top+1)>=capacity) {
            cout<<"el stack full"<<endl;
            return;
        }
        top++;
        arr[top]=value;
    }
    int pop() {
        if (isEmpty()) {
            cout<<"stack empty"<<endl;
            return -1;
        }
        return arr[top--];
    }
    void print() {
        for (int i=0;i<=top;i++) {
            cout<<arr[i]<<endl;
        }
    }
    bool isEmpty() {
        return top == -1;
    }

    ~stack() {
        delete[] arr;
    }

};


int main() {
    stack s(3);

    s.push(56);
    s.push(104);
    s.push(81);
    s.push(32);
    s.push(100);
    s.push(307);
    s.push(325);
    cout<<"pop: "<<s.pop()<<endl;
    cout<<"pop: "<<s.pop()<<endl;
    cout<<"pop: "<<s.pop()<<endl;
    cout<<"pop: "<<s.pop()<<endl;

    s.print();



    return 0;

}
