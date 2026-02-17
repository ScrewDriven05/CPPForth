#include <iostream>
using namespace std;

/*

1. Implement Stack
2. Implement Dictionary
3. Implement Forth Class
4. Initialise Program Dictionary and Stack
5. Implement Corresponding Forth Words
6. Create Python UI

*/

class Stack{
    public:
    float a[128];
    int itop;
    Stack(){itop=-1;}//initialised empty stack
    bool isEmpty(){return itop==-1;}//return true if stack is empty
    bool isFull(){return itop==127;}//return true is stack is full
    void push(float x){
        if(isFull()==true){cout<<"Stack Overflow";}
        else{++itop; a[itop]=x;}
    }
    float pop(){
        if(isEmpty()==true){"Stack Underflow";}
        else{return a[itop--];}}
    
};

class Dictionary{



};

class Forth{



};

int main() {
    Stack main;
    return 0;

}
