#include<vector>
#include<iostream>
using namespace std;
//use adjacency matrix to memory the graph
const int INF = 0x3f3f3f3f; //to avoid overflow, this num can't be big
void dijkstra(vector<vector<int>> edges,vector<int>& distance,vector<int>& pre ,int n,int start){
    bool visited[n+1]; // to mark which dot is in first group
    for(int i = 1;i<=n;i++){
        visited[i] = false;
        distance[i] = INF;
        pre[i] = -1;
    }
    distance[start] = 0;
    for(int i = 1;i<=n;i++){
        int index = -1;
        int min = INT_MAX;
        for(int j = 1;j<=n;j++){ // to find the dot whose distance between first group is minimal
            if(!visited[j] && distance[j]<min){
                min = distance[j];
                index = j;
            }
        }
        if(index == -1){
            break;
        }
        visited[index] = true;
        for(int j = 1;j<=n;j++){ //update the remaining dot's distance between first group
            if(!visited[j] && distance[index]+edges[index][j] < distance[j]){
                distance[j] = distance[index]+edges[index][j];
                pre[j] = index;
            }
        }    
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges(n+1,vector<int>(n+1,INF));
    vector<int> distance(n+1,INF);
    vector<int> pre(n+1,-1);
    for(int i = 0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        edges[x][y]=w;
    }
    int start;
    cin>>start;
    dijkstra(edges,distance,pre,n,start);
    for(int i = 1;i<=n;i++){
        cout<<"distance:"<<distance[i]<<" ";
        cout<<"path:"<<i;
        int head = i;
        while(pre[head] != -1){
            cout<<"->"<<pre[head];
            head = pre[head];
        }
        cout<<endl;
    }
    return 0;
}