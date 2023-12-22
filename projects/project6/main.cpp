#include"graph.h"
#include<cstdio>
int main(){
    GraphList* g= new GraphList;
    createGraph(g);
    TreeNode* root = dfs(g);
    int length_dfs = get_deepth(root);
    int width_bfs = 50;
    int width_dfs = 50;
    string graph_tree_dfs(MAXVEX,' ');
    string graph_tree_bfs(MAXVEX,' ');
    int height_dfs = 0;
    int height_bfs = 0;
    print_tree(root,0,height_dfs,width_dfs,graph_tree_dfs);
    for(int i = 0;i<length_dfs-1;i++){
        graph_tree_dfs[(i+1)*width_dfs-1] = '\n';
    }
    cout<<graph_tree_dfs<<endl;
    
    TreeNode* multi_root = multi_dfs(g);
    int length_multi_dfs = get_deepth(multi_root);
    int width_multi_bfs = 50;
    int width_multi_dfs = 50;
    string graph_tree_multi_dfs(MAXVEX,' ');
    string graph_tree_multi_bfs(MAXVEX,' ');
    int height_multi_dfs = 0;
    int height_multi_bfs = 0;
    print_tree(multi_root,0,height_multi_dfs,width_multi_dfs,graph_tree_multi_dfs);
    for(int i = 0;i<length_multi_dfs-1;i++){
        graph_tree_multi_dfs[(i+1)*width_multi_dfs-1] = '\n';
    }
    cout<<graph_tree_multi_dfs<<endl;

    TreeNode* bfs_root = bfs(g);
    int length_bfs = get_deepth(bfs_root);
     print_tree(bfs_root,0,height_bfs,width_bfs,graph_tree_bfs);
    for(int i = 0;i<length_bfs-1;i++){
        graph_tree_bfs[(i+1)*width_bfs-1] = '\n';
    }
    cout<<graph_tree_bfs<<endl;

    TreeNode* bfs_multi_root = multi_bfs(g);
    int length_multi_bfs = get_deepth(bfs_root);
     print_tree(bfs_multi_root,0,height_multi_bfs,width_multi_bfs,graph_tree_multi_bfs);
    for(int i = 0;i<length_multi_bfs-1;i++){
        graph_tree_multi_bfs[(i+1)*width_multi_bfs-1] = '\n';
    }
    cout<<graph_tree_multi_bfs<<endl;
    return 0;
}
