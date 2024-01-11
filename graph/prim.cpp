#include<iostream>
#include<vector>
using namespace std;
const int INF = 0x3f3f3f3f;
void prim(vector<vector<int>>& g,vector<int>& visited,vector<int> cost,int start,int n){
    int res = 0;
    cost[start] = 0;
    visited[start] = 1;
    for(int i = 1;i<=n;i++){
        cost[i] = min(cost[i],g[start][i]);
    }
    for(int i = 1;i<n;i++){
        int temp = INF;
        int index = -1;
        for(int j = 1;j<=n;j++){
            if(visited[j] == 0 && cost[j]< temp){
                temp = cost[j];
                index = j;
            }
        }
        if(index == -1){
            cout<<"not connected";
            return;
        }
        visited[index] =1;
        res += temp;
        for(int j = 1;j<=n;j++){ //update cost;
            cost[j] = min(cost[j],g[index][j]);
        }
    }
    cout<<res;
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1,vector<int>(n+1,INF));
    for(int i = 0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        g[x][y] = w;
        g[y][x] = w; //undirected graph
    }
    vector<int> visited(n+1,0);
    vector<int> cost(n+1,INF);
    prim(g,visited,cost,1,n);
}