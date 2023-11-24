#include "graphlist.h"
#include <iostream>

void createGraph(GraphList* g){
   cin >> g->numVertex >> g->numEdges;
   
   for(int i = 0; i < g->numVertex; i ++){
    cin >> g->adjList[i].value;
    g->adjList[i].firstedge = nullptr;
   }

   for(int i = 0; i < g->numEdges; i ++){
     int head, tail, weight;
     cin >> head >> tail >> weight;
     EdgeNode* e = new EdgeNode();
     e->adjvex = tail;
     e->weight = weight;
     e->next = nullptr;

     if(g->adjList[head].firstedge == nullptr){
        g->adjList[head].firstedge = e;
     }
     else{
        EdgeNode* tmp = g->adjList[head].firstedge;
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = e;
     }
   }
}