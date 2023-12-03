#include <iostream>
#include <chrono>
#include "array.h"

template <class T>
class Heap{
private:
    dynamicArray<T>  *array;
    int size;
    T * getParent(int index){
        return array->index(((index-1)/2));
    }
    T * getLeft(int index){
        return array->index((index * 2)+1);
    }
    T * getRight(int index){
        return array->index((index * 2)+2);
    }
    void swap(T & value1, T & value2){
        auto temp =value1;
        value1 = value2;
        value2 = temp;
    }


    void heapifyUp(int index,bool (*cmp)(T,T)){

            T *left = getLeft(index);
            T *right = getRight(index);
            T *max = getIndex(index);
            if(left && right){
            if (cmp(*right, *left) && cmp(*right, *max)) {
                swap(*right, *max);
            }else
            if (cmp(*left, *right) && cmp(*left, *max)) {
                swap(*left, *max);
            }}else{
                if(right && cmp(*right, *max)){
                    swap(*right, *max);
                }else if(left && cmp(*left, *max)){
                    swap(*left, *max);
                }
            }

        if(index !=0) {
            heapifyUp((index-1)/2, cmp);
        }

    }
    void heapifyDown(int index,bool (*cmp)(T,T)){

        T *left = getLeft(index);
        T *right = getRight(index);
        T *max = getIndex(index);
        int temp;
        if(left && right){
            if (cmp(*right, *left) && cmp(*right, *max)) {
                swap(*right, *max);
                temp = index*2+2;
            }else
            if (cmp(*left, *right) && cmp(*left, *max)) {
                swap(*left, *max);
                temp = index*2+1;
            }}else{
            if(right && cmp(*right, *max)){
                swap(*right, *max);
                temp = index*2+2;
            }else if(left && cmp(*left, *max)){
                swap(*left, *max);
                temp = index*2+1;
            }
        }

        if(array->index(temp)) {
            heapifyDown(temp, cmp);
        }

    }
public:
    Heap(){
        array = new dynamicArray<T>();
        size = 0;
    }
    T * getIndex(int index){
        return array->index(index);
    }
    void add(T value,bool (*cmp)(T,T)){
        array->add(value);
        size++;
        heapifyUp(array->length-1,cmp);
    }
    void toString(){
        array->toString();
    }
    void clear(){
        array->clear();
        size = 0;
    }
     T  deleteFirst(bool (*cmp)(T,T)){

        T *temp = array->index(0);
        swap(*array->index(0),*array->index(size-1));
        size--;
        if(size == 0){
            clear();
        }
        array->deleteLast();
        heapifyDown(0,cmp);

         return *temp;
    }

};

template <class T>
bool maxHepify(T first, T second){
    return first > second;
}
template <class T>
bool minHepify(T first, T second){
    return first < second;
}

template <class T>
T getRandom(){
    return rand() % 1000;
}
int main() {
    auto * first = new Heap<int>();
    const int Qty = 10000;

    //Add begin
    auto t1 = chrono::high_resolution_clock::now();


    for (int i = 0; i < Qty; i++) {
        first->add(getRandom<int>(), maxHepify);
    }

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("Add  %d elements: Time measured: %.3d nanoseconds.\n", Qty, duration.count());


    //Delete first element

    int hits = 0;
    t1 = chrono::high_resolution_clock::now();


    auto t1_temp = chrono::high_resolution_clock::now();
    auto t2_temp = chrono::high_resolution_clock::now();
    auto  duration_temp = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

    long duration_temp_data[Qty];
    auto worst_duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

    for (int i = 0; i < Qty; i++) {
        t1_temp = chrono::high_resolution_clock::now();



       first->deleteFirst(maxHepify);





        t2_temp = chrono::high_resolution_clock::now();
        duration_temp = chrono::duration_cast<chrono::nanoseconds>(t2_temp - t1_temp);
        if (duration_temp > worst_duration) {
            worst_duration = duration_temp;
        }
        duration_temp_data[i] = duration_temp.count();


    }

    t2 = chrono::high_resolution_clock::now();
    long sum = 0;

    for (int i = 0; i < Qty; i++) {
        sum += duration_temp_data[i];
    }
    long average = sum / Qty;
    duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("Deleted   %d elements : Time measured: %.3d nanoseconds.\n. Average time %.3d. Worst time %.d3", Qty, duration.count(), average, worst_duration.count());

    cout << endl;


    return 0;
}
