#include "graphlist.h"
#include <vector>

void dfs(GraphList *g, int i, vector<int>& visited){
    visited[i] = 1;
    cout << i << " ";
    EdgeNode* e = g->adjList[i].firstedge;
    while(e != nullptr){
        if(visited[e->adjvex] == 0){
            //cout << e->tail << " ";
            dfs(g, e->adjvex, visited);// use reverse to dfs the unvisited vertex
        }
        e = e->next;
    }

}

void DFSTraverse(GraphList *g){
    vector<int> visited(g->numVertex);
    
    for(int i = 0; i < g->numVertex; i ++){
        visited[i] = 0;
    }

    for(int i = 0; i < g->numVertex; i ++){
        if(visited[i] == 0){
            dfs(g, i, visited); //if the vertex has not been visited yet, apply DFS to it
        }
    }
}