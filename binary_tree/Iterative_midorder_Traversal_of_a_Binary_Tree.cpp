#include "Binary_Tree.h"
#include "stack"
using namespace std;
void traveral_midorder(TreeNode* root) {
    stack<TreeNode*> ans;
    TreeNode* p = root;
    while(!ans.empty()||p){
        if(p){
            ans.push(p);
            p = p->left;
        }
        else{
            p = ans.top();
            ans.pop();
            //visit node
            p = p->right;
        }

    }

}
//
// Created by doov on 2023/7/29.
//
