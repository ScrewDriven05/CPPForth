#include <iostream>
#include <string>

/*
#include <vector>
#include <map>
#include <sstream>          <- Use these in the STM32 version
#include <charconv>
#include <functional>
*/
using namespace std;

/*

1. Implement Stack                                  Done
2. Implement Dictionary                             Done
3. Implement Forth Class
4. Initialise Program Dictionary and Stack
5. Implement Corresponding Forth Words
6. Create C++ Qt UI

Made with love, madness, and sleep deprivation.

*/

template <typename T>
class DynArr
{
    T *arr;         // array of dynamic type and size
    int capacity;   // initial capacity
    bool resizable; // boolean to control resizability

public:
    int itop;       // top index
    DynArr(int c = 5, bool dynamic = true) : capacity(c), resizable(dynamic), itop(-1) { arr = new T[capacity]; }
    ~DynArr() { delete[] arr; }

    void add(T x) // since I'll only need to add to the top of the list I've skipped index-specific adding
    {
        if (itop == (capacity - 1) && resizable == false)
        {
            cout << "Overflow";
            return;
        }
        else if (itop == (capacity - 1) && resizable == true)
        {
            resize();
        }
        ++itop;
        arr[itop] = x;
    }

    T remove(int i)
    {
        if (itop == -1)
        {
            cout << "Underflow";
            return T();
        }
        T elem = arr[i];
        --itop;
        T *tempArr = new T[capacity]; // be super careful of capacity, it can break the destructor.
        int j;
        for (j = 0; j < i; j++)
        {
            tempArr[j] = arr[j];
        }
        ++i;
        for (j = i; j <= itop; j++)
        {
            tempArr[j] = arr[j];
        }

        /*
        arr=tempArr;
        delete[] tempArr;

        ^This'll cause arr to point to an empty memory location, don't do this.
        */

        delete[] arr;
        arr = tempArr;
        return elem;
    }

    T pop()
    {
        return;
    }

    void resize()
    {
        T *tempArr = new T[2 * capacity];
        int j;
        for (j = 0; j < capacity; j++)
        {
            tempArr[j] = arr[j];
        }
        capacity = 2 * capacity;

        /*
        arr=tempArr;
        delete[] tempArr;

        ^This'll cause arr to point to an empty memory location, don't do this.
        */

        delete[] arr;
        arr = tempArr;
    }

    int size()
    {

        return itop + 1;
    }

    int cap()
    {
        return capacity;
    }

    void info()
    {
        int i;
        cout << "\n[";
        for (i = 0; i < itop; i++)
        {
            cout << arr[i] << ", ";
        }
        string r = (resizable == 1) ? "true" : "false";
        cout << arr[itop] << "]";
        cout << "\ncapacity: " << capacity;
        cout << "\nsize: " << size();
        cout << "\nresizable: " << r << endl;
    }

    int find(T f)
    {
        int i;
        for (i = 0; i <= itop; i++)
        {
            if (i != (itop + 1) && arr[i] == f)
            {
                return i;
            }
        }
        return -1;
    }

    T give(int i)
    {

        if (i <= itop)
        {
            return arr[i];
        }

        return T();
    } // num array will never be searched so it's okay
};

template <typename K, typename V>
class Dictionary
{
    int dict_cap;
    bool resize;
    DynArr<K> keys;
    DynArr<V> values;

    public:
    Dictionary(int capacity = 16, bool resize = true) : dict_cap(capacity), resize(resize), keys(dict_cap, resize), values(dict_cap, resize) {}

    void add(K key, V value)
    {
        if (keys.find(key) == -1)
        {
            keys.add(key);
            values.add(value);
        }
    }
    void remove(int i)
    {
        if (i < keys.size())
        {
            keys.remove(i);
            values.remove(i);
        }
    }
    void key_remove(K k)
    {
        int i = keys.find(k);
        if (i != -1)
        {
            remove(i);
        }
    }

    bool find_key(K k){

        if(keys.find(k)){return true;}
        else{false;}

    }

    V give(K k)
    {
        if (keys.find(k) != -1)
        {
            return values.give(keys.find(k));
        }
        else
        {
            return V();
        }
    }

    int size()
    {
        return keys.size();
    }

    void info()
    {
        int i;
        cout << "\n\n";
        for (i = 0; i < size(); i++)
        {
            cout << keys.give(i) << " : " << values.give(i) << "\n";
        }
        string r = (resize == 1) ? "true" : "false";
        cout << "\ncapacity: " << keys.cap();
        cout << "\nsize: " << size();
        cout << "\nresizable: " << r << endl;
    }
};

/*
template<typname T>
void to_DynArr()
template<typename K, typename V>
void to_dict()
*/

bool is_num(string s){
    try{
        stof(s);
        return true;
    }
    catch(...){
        return false;
    }
}


//Had my midsems >:(

class Word{

    public:
        virtual void exec(DynArr<float>& stack)=0;

}; //Master word class, new classes to be derived from it

class PrintWord:public Word{

    public:
        void exec(DynArr<float>& stack) override{
            if(stack.size()==0){
                cout<<"Empty Stack";
            }
            else{
                cout<<stack.give(stack.itop);
                stack.remove(stack.itop);
            }
        }

};

class AddWord:public Word{
    public:
        void exec(DynArr<float>& stack) override{
            if(stack.size()<=2){
                cout<<"Insufficient Args";
            }
            else{
                float a=stack.give(stack.itop);
                stack.remove(stack.itop);

                float b=stack.give(stack.itop);
                stack.remove(stack.itop);

                float sum=a+b;
                stack.add(sum);
            }
        }
};

class DumpWord:public Word{
    public:
        void exec(DynArr<float>& stack) override{
            int i=0;
            while(i<stack.size()){
                cout<<stack.give(i)<<"  ";
                i++;
            }
        }
};

class SubWord:public Word{
    public:
        void exec(DynArr<float>& stack) override{
            if(stack.size()<=2){
                cout<<"Insufficient Args";
            }
            else{
                float a=stack.give(stack.itop);
                stack.remove(stack.itop);

                float b=stack.give(stack.itop);
                stack.remove(stack.itop);

                float diff=a-b;
                stack.add(diff);
            }
        }
};

class DivWord:public Word{
    public:
        void exec(DynArr<float>& stack) override{
            if(stack.size()<=2){
                cout<<"Insufficient Args";
            }
            else{
                float a=stack.give(stack.itop);
                stack.remove(stack.itop);

                float b=stack.give(stack.itop);
                stack.remove(stack.itop);

                float quot=a/b;
                stack.add(quot);
            }
        }
};

class MultWord:public Word{
    public:
        void exec(DynArr<float>& stack) override{
            if(stack.size()<=2){
                cout<<"Insufficient Args";
            }
            else{
                float a=stack.give(stack.itop);
                stack.remove(stack.itop);

                float b=stack.give(stack.itop);
                stack.remove(stack.itop);

                float prod=a-b;
                stack.add(prod);
            }
        }
};

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
            Word* w=words.give(tok);
            w->exec(main_stack);
        }


    }
    
    //dis my interpreter
    DynArr<float> main_stack{256, false};       //program stack
    Dictionary<string, Word*> words {22, true};  //Command map

    public:

    Forth(){
        words.add(",", new PrintWord());
        words.add("+", new AddWord());
        words.add(".", new DumpWord());
        words.add("/", new DivWord());
        words.add("-", new SubWord());
        words.add("*", new MultWord);
    }

    void parse(string inp){
    char delim=' ';
    int t_start=0;
    int t_end=0;
    while(!inp.empty()){
        while(inp[t_start]==delim){
            ++t_start;
            }        
        t_end=t_start;        
        while(inp[t_end]!=delim){
            ++t_end;
            }
        string token=inp.substr(t_start, (t_end-t_start));        
        allocate(token);
        inp=inp.erase(0, t_end);
        t_start=0;
        t_end=0;
        }             
    }

};

int main()
{
    Forth f;
    f.parse("2.29 8.825 3.62 3.14 4.42 + + ."); //IT WORKS
    return 0;
}

// GOOD LORD THIS IS A LOT TO DO
