#include"Stack.h"
template<typename T>
 Stack<T>::Stack(int s){
    size = s;
    top = 0;
    data = new T[size];
}
template<typename T>
T Stack<T>::get_top(){
    return data[top-1];
}
template<typename T>
bool Stack<T>::push(T t){
    if(top<size){
        data[top] = t;
        top++;
    }
    else{
        T* new_data = new T[size*2];
        for(int i = 0;i<size;i++){
            new_data[i] = data[i];
        }
        size *= 2;
        delete[] data;
        data = new_data;
        data[top] = t;
        top++;
    }
    return true;
}
template<typename T>
bool Stack<T>::pop(){
    if(!isempty()){
        top--;
        return true;
    }
    return false;
}
template<typename T>
bool Stack<T>::isempty(){
    return top == 0;
}
template<typename T>
Stack<T>::~Stack(){
    delete[] data;
}/*
#include<iostream>
 int main(){
    Stack<int> s;
    for(int i = 0;i<5;i++){
        s.push(i);
    }
    for(int i = 0;i<5;i++){
        std::cout<<s.get_top();
        s.pop();
    }
    //for(int i = 0;i<5;i++){
       // s.pop();
    //}
    std::cout<<s.pop();
    std::cout<<s.isempty();

 }*/
