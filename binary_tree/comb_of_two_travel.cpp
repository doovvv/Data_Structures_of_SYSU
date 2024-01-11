#include<iostream>
#include<string>
using namespace std;
void pre_and_post(string pre,string post){ //已知前序后序求中序个数
    int count = 1;
    for(int i = 0;i<pre.length();i++){
        int j = post.find(pre[i]);
        if(i<pre.length()-1 && j>0 && pre[i+1] == post[j-1]){
            count *= 2;
        }
    }
    cout<<count;
}
void get_post(string pre,string mid,int root,int start, int end){ //已知前序中序求后序
    if(start>=end){
        return;
    }
    int root_in_mid = mid.find(pre[root]);
    get_post(pre,mid,root+1,start,root_in_mid); //递归左子树
    get_post(pre,mid,root+root_in_mid-start+1,root_in_mid+1,end);//递归右子树
    cout<<pre[root]; //访问根
}
//int pre_and_mid(string pre,string mid){
    //int root = mid.find(pre[0]);
    
//}
int main(){
    string pre,mid;
    cin>>pre>>mid;
    get_post(pre,mid,0,0,pre.size());
}