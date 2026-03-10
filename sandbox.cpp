#include <iostream>
#include <string>
using namespace std;

/*

    Welcome to the messiest part of my repo
    This is where I try everything before changing it in main/cpp_backend
    Mad respect to this file honestly

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

    int cap(){
        return capacity;
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

    int find(T f){
        int i;
        for(i=0;i<=itop;i++){
            if(i!=(itop+1)&&arr[i]==f){return i;}
            }
        return -1;   
    }

    T give(int i){

        if(i<=itop){return arr[i];}
        
        return T();}//num array will never be searched so it's okay

    };

    

template<typename K, typename V>
class Dictionary{
    int dict_cap;
    bool resize;
    DynArr<K> keys;
    DynArr<V> values;

    public:

    Dictionary(int capacity=16, bool resize=true):dict_cap(capacity),resize(resize), keys(dict_cap,resize), values(dict_cap, resize){}

    void add(const K& key, const V& value){
        if(keys.find(key)==-1)
        {
            keys.add(key);
            values.add(value);
        }
        else{
            cout<<"Key already defined";
        }               
    }
    void remove(int i){
        if(i<keys.size()){
            keys.remove(i);
            values.remove(i);
        }
    }

    void key_remove(const K& k){
        int i=keys.find(k);
        if(i!=-1){remove(i);}
        
    }

    V give(K& k){
        int index=keys.find(k);
        if(index!=-1){return values.give(index);}
        else{cout<<k<<"?";return nullptr;}//forth style error   
    }

    int size(){
        return keys.size();
    }

    void info(){
        int i;
        cout<<"\n\n";
        for(i=0;i<size();i++){
            cout<<keys.give(i)<<" : "<<values.give(i)<<"\n";
        }
        string r=(resize==1)?"true":"false";
        cout<<"\ncapacity: "<<keys.cap();
        cout<<"\nsize: "<<size();
        cout<<"\nresizable: "<<r<<endl;
    }


};


//Had my midsems >:(

class Word{
    
}; //Master word class, new classes to be derived from it

class Forth{

    bool is_num(string s){
        try{
            stof(s);
            return true;
        }
        catch(...){
            return false;
        }
    }
    void allocate(string& tok){
        if(is_num(tok)){
            main_stack.add(stof(tok));
        }
        else {
            words.give(tok);
        }
    }
    //dis my interpreter
    DynArr<float> main_stack{256, false};       //program stack
    Dictionary<string, Word> words {22, true};  //Command map
    public:
    void parse(string inp){
        char delim=' ';
        while(inp.empty()==0){
            int pos=inp.find(delim);
            if(pos==string::npos){
                allocate(inp);
                break;
            }
            string token=inp.substr(0, pos);
            allocate(token);
            inp=inp.erase(0, pos+1);
        }
        
    }
};



int main(){
    
    Forth f;
    f.parse("1.25 6.3 2.22 8.29 , ,");
    
}


    