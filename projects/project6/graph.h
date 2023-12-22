#include <iostream>
#include <vector>
#include <queue>
#include<cmath>
#include<string>
using namespace std;
#define MAXVEX 1000
template<typename T>
class StackNode{
    public:
        T data; //栈顶元素的值
        StackNode *next;
        StackNode(T t){
            data = T(t); //初始化t
            next = nullptr;
        }
        StackNode(){
            data = T(); //初始化栈顶元素默认值
            next = nullptr;
        }
};
template<typename T>
class stack{
    public:
        StackNode<T>* root;
        StackNode<T>* top_node;
        stack(){
            root = new StackNode<T>();
            top_node = root;
        }
        void push(T t){
            if(root == nullptr){
                root->next =  new StackNode<T>(t);
                top_node = root->next;
            }
            else{
                top_node->next = new StackNode<T>(t);
                top_node = top_node->next;
            }
        }
        void pop(){
            if(root == nullptr){
                return;
            }
            else{
                StackNode<T>* node = root;
                for(;node->next!= top_node;node = node->next){
                }
                top_node = node;
            }
        }
        bool empty(){
            return root == top_node;
        }
        T top(){
            return top_node->data;
        }
        
};
class EdgeNode {
 public:
	int adjvex; //边指向哪个顶点的索引
	int weight;
	EdgeNode* next;
};
class MultilistNode{
    public:
        int vertex1,vertex2;
        MultilistNode* path1;
        MultilistNode* path2;
};
// 顶点表结构
class VertexNode {
 public:
	int value; //顶点的值，为了简化与序号相同，第一个是0
	EdgeNode *firstedge;
    MultilistNode* firstmultiedge;
};
// 图结构
class GraphList {
 public:
	VertexNode adjList[MAXVEX];
	int numVertex;
	int numEdges;
    
};
struct TreeNode {
        int val;
        vector<TreeNode*> children;
        //TreeNode *left;
        //TreeNode *right;
        //TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x) {}
        //TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
        };
void createGraph(GraphList* g);
TreeNode* dfs(GraphList* g);
TreeNode* bfs(GraphList* g);
TreeNode* multi_dfs(GraphList* g);
TreeNode* multi_bfs(GraphList* g);
void print_tree(TreeNode* root,int depth,int& height,int width,string& graph_tree);
int get_deepth(TreeNode* root);
int get_width(TreeNode* root);