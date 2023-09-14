#include<iostream>
#include"Linked_List.h"
using namespace std;
int main(){
    Linked_List<int>  list(0);
    for(int i = 0;i<5;i++){
        list.append(i);
    }
    for(int i = 0;i<5;i++){
        cout<<list.getValue(i);
    }
    list.detele(1);
    for(int i = 0;i<list.length();i++){
        cout<<list.getValue(i);
    }
    list.clear();
    cout<<list.isempty();
    return 0;
}
