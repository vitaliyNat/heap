#include <iostream>

using namespace std;

template <class T>
class dynamicArray{
private:
    int size;
    T * head;
    float grow = 1.5;
public:
    int length;

    dynamicArray(){
        head = new T[5];
        size = 5;
        length = 0;
    }


    bool checkSize(){
        return size*0.8 < length;
    }

    void add(T value){
        if(checkSize()) growSize();
        head[length]= value;
        length++;
    }

    void growSize(){
        size= size*grow;
        auto *newHead = new T[size];

        for(int i = 0; i<length;i++){
            newHead[i] = head[i];
        }
        delete [] head;
        head = newHead;
    }


    void clear(){
        delete [] head;
        length = 0;
        size = 5;
        head = new T[size];
    }

    T  operator [] (int index) {

        if(length<= index){
          //  cout<<"Index out of range!";
            return -1;
        }
        return head[index];

    }

    T *  index(int index){
        if(length<= index){
          //  cout<<"Index out of range!";
            return nullptr;
        }
        return &head[index];
    }

    void change(int index, T *newValue){
        if(length<= index){
            cout<<"Index out of range!";
            return;
        }
        head[index] = &newValue;

    }
    void deleteLast(){
        if(length){
            length--;
        }else{
            clear();
        };
    }


    void toString(){
        cout<<"Size: "<< size<< ". Length: "<<length<<endl;
        for(int i = 0; i<length; i++){
            cout<<"Value: "<< head[i]<<endl;
        }
    }
    void toStringShort(){
        cout<<"Size: "<< size<< ". Length: "<<length<<endl;
        cout << "First element: "<< head[0]<< ". Last element: " << head[length-1]<<endl;
    }
    int getSize(){
        return this->size;
    }

    void sort(bool (*cmp)(T,T)){
        for(int i = 0; i<length;i++){
            for(int j = 0; j<length-i-1; j++){
                if(cmp(head[j],head[j+1])){
                    int temp = head[j];
                    head[j] =  head[j+1];
                    head[j+1] = temp;
                }
            }
        }
    }
};