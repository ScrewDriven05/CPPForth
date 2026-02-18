#include <iostream>
using namespace std;

/*

1. Implement Stack
2. Implement Dictionary
3. Implement Forth Class
4. Initialise Program Dictionary and Stack
5. Implement Corresponding Forth Words
6. Create Python UI

Made with love, madness, and sleep deprivation.

*/

template<typename T>
class DynArr{
    T* arr; //array of dynamic type and size
    int capacity;//initial capacity
    bool resizable;//boolean to control resizability
    int itop;//top index

    public:
    DynArr(int c=5, bool dynamic=true):capacity(c), resizable(dynamic),itop(-1){arr=new T[capacity];}
    ~DynArr(){delete[] arr;}

    void add(T x)//since I'll only need to add to the top of the list I've skipped index-specific adding
    {
        if(itop==(capacity-1)&&resizable==false){
            cout<<"Overflow";return;
        }
        else if(itop==(capacity-1)&&resizable==true){
            resize();
        }
        ++itop;arr[itop]=x;
    }
    void remove(int i){
        if(itop==-1){cout<<"Underflow";return;}
        --itop;
        T* tempArr=new T[capacity];//be super careful of capacity, it can break the destructor.
        int j;
        for(j=0;j<i;j++){
            tempArr[j]=arr[j];
        }
        ++i;
        for(j=i;j<=itop;j++){
            tempArr[j]=arr[j];
        }

        /*
        arr=tempArr;
        delete[] tempArr;

        ^This'll cause arr to point to an empty memory location, don't do this.
        */

        delete[] arr;
        arr=tempArr;
    }
    void resize(){
        T* tempArr=new T[2*capacity];
        int j;
        for(j=0;j<capacity;j++){
            tempArr[j]=arr[j];
        }
        capacity=2*capacity;

        /*
        arr=tempArr;
        delete[] tempArr;

        ^This'll cause arr to point to an empty memory location, don't do this.
        */

        delete[] arr;
        arr=tempArr;
    }
    
    int size(){
    
        return itop+1;
    
    }

    void info(){
        int i;
        cout<<"\n[";
        for(i=0;i<itop;i++){
            cout<<arr[i]<<", ";
        }
        string r=(resizable==1)?"true":"false";
        cout<<arr[itop]<<"]";
        cout<<"\ncapacity: "<<capacity;
        cout<<"\nsize: "<<size();
        cout<<"\nresizable: "<<r<<endl;
    }
};


class Dictionary{

    //I guess I'll just use a pair of coupled DynArrs for now

};

class Forth{
    DynArr<float> main{256, true};//program's numeric stack

};

void parse(){
    //parse input string... eventually...
}

int main() {

    return 0;

}

//GOOD LORD THIS IS A LOT TO DO
