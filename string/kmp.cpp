#include<iostream>
#include<vector>
#include<string>
using namespace std;
void get_next(string s,vector<int>& next){
    int i = 1,j = 0;
    next[i] = 0;
    while(i<s.length()){
        if(j==0||s[i] == s[i]){
            i++;
            j++;
            next[i] = j;
        }
        else{
            j = next[j];
        }
    }
}
void get_nextval(string s,vector<int>& nextval){
    int i = 1;
    int j = 0;
    nextval[1] = 0;
    while(i< s.length()){
        if(j == 0 || s[i] == s[j]){
            i++;
            j++;
            if(s[i] != s[j]){
                nextval[i] = j;
            }
            else{
                nextval[i] = nextval[j];
            }
        }
        else{
            j = nextval[j];
        }
    }
}
int Index_KMP(string s,string t,vector<int>& next){
    int i=1,j=1;
    while(i<=s.length() && j<=t.length()){
        if(j == 0 || s[i-1] == t[j-1]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j > t.length()){
        return i-j+1;
    }
    return 0;
}
int main(){
    string s,t;
    cin>>s>>t;
    vector<int> next(t.length()+1);
    get_nextval(t,next);
    cout<<Index_KMP(s,t,next);
}