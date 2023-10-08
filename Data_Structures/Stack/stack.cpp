#include"Stack.h"
Stack::Stack(int s,int t){
    size = s;
    top = t;
    data = new T[size];
}
T Stack:: get_top(){
    if(!is_empty()){
        return data[top-1];
    }
}
bool Stack::push(T t){
    if(top < size){
        data[top] = t;
        top++;
    }
    else{
        size *= 2;
        T* new_data;
    }
}