#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAXVEX 1000
// 边表节点
class EdgeNode {
 public:
	int adjvex; //边指向哪个顶点的索引
	int weight;
	EdgeNode* next;
};
// 顶点表结构
class VertexNode {
 public:
	int value; //顶点的值，为了简化与序号相同，第一个是0
	EdgeNode *firstedge;
};
// 图结构
class GraphList {
 public:
	VertexNode adjList[MAXVEX];
	int numVertex;
	int numEdges;
};