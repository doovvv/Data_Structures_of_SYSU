#include "graphlist.h"
#include <queue>
#include <vector>

void BFSTraverse(GraphList* g){
    queue<int> Q;
    vector<int> visited(g->numVertex);

    for(int i = 0; i < g->numVertex; i ++){
        visited[i] = 0;
    }

    for(int i = 0; i < g->numVertex; i ++){ //traverse the adjaency list
        if(visited[i] == 0){
            visited[i] = 1;
            Q.push(i);
            while(!Q.empty()){
                int w = Q.front();
                cout << w << " ";
                Q.pop();
                EdgeNode* e = g->adjList[w].firstedge;
                while(e != nullptr){
                    if(visited[e->adjvex] == 0){
                        visited[e->adjvex] = 1; //being visited
                        Q.push(e->adjvex);
                    }
                    e = e->next;
                }
            }
        }
    }
}
