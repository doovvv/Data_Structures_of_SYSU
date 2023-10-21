#include "Binary_Tree.h"
#include "stack"
using namespace std;
//将根节点压栈
//如果有左节点压栈
//如果没有，访问根节点，进入右节点
void traveral_midorder(TreeNode* root) {
    stack<TreeNode*> ans;
    TreeNode* p = root;
    while(!ans.empty()||p){
        if(p){
            ans.push(p);
            p = p->left;//check leftchild
        }
        else{
            p = ans.top();//back to root
            ans.pop();
            //visit node
            p = p->right;//into rightchiled
        }

    }

}
//
// Created by doov on 2023/7/29.
//
