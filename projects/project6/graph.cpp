#include"graph.h"
vector<pair<int,int>> edges_set1;
vector<pair<int,int>> edges_set2;
void createGraph(GraphList* g){
   cin >> g->numVertex >> g->numEdges;
   
   for(int i = 1; i <= g->numVertex; i ++){
     g->adjList[i].value = i;
    g->adjList[i].firstedge = nullptr;
    g->adjList[i].firstmultiedge = nullptr;
   }

   for(int i = 0; i < g->numEdges; i ++){
     int head, tail;
     cin >> head >> tail;
     EdgeNode* e = new EdgeNode();
     EdgeNode* e_reverse = new EdgeNode();
     MultilistNode* m = new MultilistNode();
     m->vertex1 = head;
     m->vertex2 = tail;
     m->path1 = nullptr;
     m->path2 = nullptr;
     e->adjvex = tail;
     e->next = nullptr;
     e_reverse->adjvex = head;
     e_reverse->next = nullptr;
    
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
     if(g->adjList[tail].firstedge == nullptr){
        g->adjList[tail].firstedge = e_reverse;
     }
     else{
        EdgeNode* tmp = g->adjList[tail].firstedge;
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = e_reverse;
     }

    //邻接多重表
    if(g->adjList[head].firstmultiedge == nullptr){
        g->adjList[head].firstmultiedge = m;
     }
    else{
      MultilistNode* tmp = g->adjList[head].firstmultiedge;
      while((tmp->vertex2==head && tmp->path2 != nullptr) || (tmp->vertex1 == head&& tmp->path1 != nullptr)){
        if(tmp->vertex1 == tail){
          tmp = tmp->path1;
        }
        else{
          tmp = tmp->path2;
        }
      }
    if(tmp->vertex1 == head){
      tmp->path1 = m;
    }
    else{
        tmp->path2 = m;
      }
    } 
    if(g->adjList[tail].firstmultiedge == nullptr){
        g->adjList[tail].firstmultiedge = m;
     }
    else{
      MultilistNode* tmp = g->adjList[tail].firstmultiedge;
      while((tmp->vertex2==tail&& tmp->path2 != nullptr) ||(tmp->vertex1 == tail&& tmp->path1 != nullptr)){
        if(tmp->vertex1 == tail){
          tmp = tmp->path1;
        }
        else{
          tmp = tmp->path2;
        }
      }
    if(tmp->vertex1 == tail){
      tmp->path1 = m;
    }
    else{
        tmp->path2 = m;
      }
    }    
   }
}
TreeNode* multi_dfs(GraphList* g){
    cout<<"muliti_DFS:"<<endl;
    int start;
    cout<<"input the start node: ";
    cin>>start;
    int node = start;
    TreeNode* root = new TreeNode(start);
    TreeNode* treenode = root;
    vector<int> visited(g->numVertex+1,0);
    stack<int> s;
    stack<TreeNode*> ans;
    visited[start] =1;
    ans.push(root);
    s.push(start);
    cout<<start;
    while(!s.empty()){
        int flag = 0;
        auto i = g->adjList[node].firstmultiedge;
        while(i){
            if(visited[i->vertex1] == 0 && i->vertex1 != node){
            node = i->vertex1;
            flag = 1;
            s.push(node);
            break;
            }
          else if(visited[i->vertex2] == 0 && i->vertex2 != node){
            node = i->vertex2;
            flag = 1;
            s.push(node);
            break;
          }
          else{
            if(i->vertex1 == node){
              i = i->path1;
            }
            else{
              i = i->path2;
            }
          }
        }
        if(flag == 0){
          s.pop();
          if(s.empty()){
            break;
          }
          node = s.top();
          ans.pop();
          treenode = ans.top();
        }
        else{
          cout<<"->"<<node;
          treenode->children.push_back(new TreeNode(node));
          edges_set1.push_back(make_pair(treenode->val,treenode->children.back()->val));
          ans.push(treenode->children.back());
          treenode = treenode->children.back();
          visited[node] = 1;
        }        
    }
    cout<<endl;
    for(int i = 0;i<edges_set1.size();i++){
      cout<<"("<<edges_set1[i].first<<","<<edges_set1[i].second<<") ";
    }
    cout<<endl;
    return root;
}
TreeNode* dfs(GraphList* g){
  cout<<"DFS:"<<endl;
    int start;
    cout<<"input the start node: ";
    cin>>start;
    int node = start;
    TreeNode* root = new TreeNode(start);
    TreeNode* treenode = root;
    vector<int> visited(g->numVertex+1,0);
    stack<int> s;
    stack<TreeNode*> ans;
    visited[start] =1;
    ans.push(root);
    s.push(start);
    cout<<start;
    while(!s.empty()){
        int flag = 0;
        for(auto i = g->adjList[node].firstedge;i;i = i->next){
          if(visited[i->adjvex] == 0){
            node = i->adjvex;
            flag = 1;
            s.push(node);
            break;
          }
        }
        if(flag == 0){
          s.pop();
          if(s.empty()){
            break;
          }
          node = s.top();
          ans.pop();
          treenode = ans.top();
        }
        else{
          cout<<"->"<<node;
          treenode->children.push_back(new TreeNode(node));
          edges_set1.push_back(make_pair(treenode->val,treenode->children.back()->val));
          ans.push(treenode->children.back());
          treenode = treenode->children.back();
          visited[node] = 1;
        }        
    }
    cout<<endl;
    for(int i = 0;i<edges_set1.size();i++){
      cout<<"("<<edges_set1[i].first<<","<<edges_set1[i].second<<") ";
    }
    cout<<endl;
    return root;
}
TreeNode* multi_bfs(GraphList* g){
  cout<<"multi_BFS:"<<endl;
  int start;
  cout<<"input the start node:";
  cin>>start;
  vector<int> visited(g->numVertex+1,0);
  TreeNode* root = new TreeNode(start);
  TreeNode* treenode = root;
  int node = start;
  queue<int> q;
  queue<TreeNode*> ans;
  q.push(start);
  ans.push(root);
  visited[start] = 1;
  cout<<start;
  while(!q.empty()){
    node = q.front();
    if(node != start){
      cout<<"->"<<node;
    }
    q.pop();
    treenode = ans.front(); 
    ans.pop();
    auto i = g->adjList[node].firstmultiedge;
    while(i){
      int flag = 0;
      if(visited[i->vertex1] == 0 && i->vertex1 != node){
        q.push(i->vertex1);
        treenode->children.push_back(new TreeNode(i->vertex1));
        edges_set2.push_back(make_pair(treenode->val,treenode->children.back()->val));
        ans.push(treenode->children.back());
        visited[i->vertex1] = 1;
        i = i->path2;
        flag = 1;
      }
      else if(visited[i->vertex2] == 0 && i->vertex2 != node){
        q.push(i->vertex2);
        treenode->children.push_back(new TreeNode(i->vertex2));
        edges_set2.push_back(make_pair(treenode->val,treenode->children.back()->val));
        ans.push(treenode->children.back());
        visited[i->vertex2] = 1;
        i = i->path1;
        flag = 1;
      }
      if(flag == 0){
        break;
      }
    }
  }
  cout<<endl;
  for(int i = 0;i<edges_set2.size();i++){
    cout<<"("<<edges_set2[i].first<<","<<edges_set2[i].second<<") ";
  }
  cout<<endl;
  return root;
}
TreeNode* bfs(GraphList* g){
  cout<<"BFS:"<<endl;
  int start;
  cout<<"input the start node:";
  cin>>start;
  vector<int> visited(g->numVertex+1,0);
  TreeNode* root = new TreeNode(start);
  TreeNode* treenode = root;
  int node = start;
  queue<int> q;
  queue<TreeNode*> ans;
  q.push(start);
  ans.push(root);
  visited[start] = 1;
  cout<<start;
  while(!q.empty()){
    node = q.front();
    if(node != start){
      cout<<"->"<<node;
    }
    q.pop();
    treenode = ans.front(); 
    ans.pop();
    for(auto i = g->adjList[node].firstedge;i;i = i->next){
      if(visited[i->adjvex] == 0){
        q.push(i->adjvex);
        treenode->children.push_back(new TreeNode(i->adjvex));
        edges_set2.push_back(make_pair(treenode->val,treenode->children.back()->val));
        ans.push(treenode->children.back());
        visited[i->adjvex] = 1;
      }
    }
  }
  cout<<endl;
  for(int i = 0;i<edges_set2.size();i++){
    cout<<"("<<edges_set2[i].first<<","<<edges_set2[i].second<<") ";
  }
  cout<<endl;
  return root;

}
int get_deepth(TreeNode* root){
    if(root == nullptr){
      return 0;
    }
    int max = 0;
    for(int i = 0;i<root->children.size();i++){
      max+= get_deepth(root->children[i]);
    }
    return max+1;
}
int get_width(TreeNode* root){
      if(root == nullptr){
      return 0;
    }
    if(root->children.empty()){
      return 1;
    }
    int max = 0;
    for(int i = 0;i<root->children.size();i++){
      max = get_width(root->children[i])>max?get_width(root->children[i]):max;
    }
    return max+3;
}
void print_tree(TreeNode* root,int depth,int& height,int width,string& graph_tree){
  if(root == nullptr){
    return;
  }
  if(height*(width)+depth-1>=0){
    graph_tree[height*(width)+depth-1] = '-';
    graph_tree[height*(width)+depth-2] = '-';
  }
  if(root->val>=10){
    graph_tree[height*(width)+depth+1] = (root->val%10+'0');
    graph_tree[height*(width)+depth] = ((root->val/10)%10+'0');
  }
  else{
    graph_tree[height*(width)+depth] = (root->val+'0');
  }
  int length = 0;
  if(!root->children.empty()) length = get_deepth(root)-get_deepth(root->children.back());

  for(int i = 0;i<length;i++){
    graph_tree[(width)*(height+i+1)+depth] = '|';
  }
  height++;
  for(auto child:root->children){
    print_tree(child,depth+3,height,width,graph_tree);
  }


}
