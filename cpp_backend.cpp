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
    int itop;       // top index

public:
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

class Forth
{
        
    //Sometimes, the best thing to do is (partially) start over
    
};

/*
class Word{
    virtual void execute(Forth f)=0;
    ~Word()=default;
};
*/

int main()
{

    return 0;
}

// GOOD LORD THIS IS A LOT TO DO
