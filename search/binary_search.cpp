#include<vector>
#include<iostream>
using namespace std;
int binary_search(vector<int> list, int key){
    int left = 0,right = list.size()-1;
    int mid = (left+right) /2;
    while(left<=right){
        mid = (left+right)/2;
        if(key == list[mid]){
            return mid;
        }
        else if(key < list[mid]){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return -1;
}
int main(){
    vector<int> list = {7,10,13,16,19,29,32,33,37,41,43};
    int address = binary_search(list,32);
    cout<<address;
}