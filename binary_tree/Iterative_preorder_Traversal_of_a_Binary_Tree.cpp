#include "Binary_Tree.h"
#include "stack"
using namespace std;
//访问根节点
//右节点压栈，保存下右节点
//访问左节点
void travel_prooredr(TreeNode* root){
    stack<TreeNode*> ans;
    root->val = 0;
    ans.push(root);
    TreeNode*p = root;
    while(!ans.empty()){
        p = ans.top();
        //visit p
        ans.pop();
        if(p->right){
            ans.push(p->right);
        }
        if(p->left){         //push leftchild into stack temporarily, next cycle will get it and visit it;
            ans.push(p->left);
        }

    }
}
//
// Created by doov on 2023/7/29.
//
